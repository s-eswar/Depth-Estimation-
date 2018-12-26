#include "opencv2/core.hpp"
#include </home/eswar/softwares/opencv_contrib-3.2.0/modules/contrib_world/include/opencv2/contrib_world.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <opencv2/calib3d.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp"
#include <opencv2/xfeatures2d/nonfree.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int argc, char** argv)
{
Mat img1, img2, g1, g2,color;
Mat disp1, disp18,disp2,disp28,disparity,disparity1,falsemap;
Mat falseColorsMap, sfalseColorsMap;
img1 = imread(argv[1],IMREAD_COLOR);
img2 = imread(argv[2],IMREAD_COLOR);
//Size size(512,512);//the dst image size,e.g.100x100
//resize(img1,img1,size);//resize image
//resize(img2,img2,size);//resize image
flip(img1,g1,1);
flip(img2,g2,1);
int max_disp;
cout << "this is BM" << endl;
 int ndisparities = 96;   /**< Range of disparity */
 int SADWindowSize = 7; /**< Size of the block window. Must be odd */

 Ptr<StereoBM> sbm = StereoBM::create(ndisparities,SADWindowSize);
	
  //-- 3. Calculate the disparity image
  sbm->compute( g1, g2, disp1);

  //-- Check its extreme values
  double minVal; double maxVal;

  minMaxLoc( disp1, &minVal, &maxVal );

  printf("Min disp: %f Max value: %f for SBM\n", minVal, maxVal);

  //-- 4. Display it as a CV_8UC1 image
  disp1.convertTo( disp18, CV_8UC1, 255/(maxVal - minVal));

  //namedWindow( "windowDisparity", WINDOW_NORMAL );
  applyColorMap(disp18, falseColorsMap, cv::COLORMAP_JET);
  imshow( "BM", falseColorsMap);

  imshow( "windowDisparity", disp18);
  waitKey(0);

  //-- 5. Save the image
  imwrite("SBM_sample_mirror.png", disp18);
  imwrite("SBMdisparity_mirror.png", falseColorsMap);
  Ptr<StereoSGBM> sgbm = StereoSGBM::create(-5,    //int minDisparity
                                        112,     //int numDisparities
                                        7,      //int SADWindowSize
                                        600,    //int P1 = 0
                                        2400,   //int P2 = 0
                                        90,     //int disp12MaxDiff = 0
                                        16,     //int preFilterCap = 0
                                        2,      //int uniquenessRatio = 0
                                        100,    //int speckleWindowSize = 0
                                        20,     //int speckleRange = 0
                                        true);  //bool fullDP = false

  sgbm->compute(g1,g2, disp2);
  minMaxLoc( disp2, &minVal, &maxVal );
  printf("Min disp: %f Max value: %f for SGBM\n", minVal, maxVal);
  disp2.convertTo( disp28, CV_8UC1, 255/(maxVal - minVal));
  applyColorMap(disp28, sfalseColorsMap, cv::COLORMAP_JET);
  imshow( "SGBM",sfalseColorsMap);
  imshow( "sgbm", disp28);
  imwrite("SGBM_sample_mirror.png", disp28);
  imwrite("SGBMdisparity_mirror.png", sfalseColorsMap);
  waitKey(0);

int minHessian = 630;
Ptr<Feature2D> f2d = SIFT::create();
//Ptr<SURF> detector = SURF::create(minHessian);
std::vector<KeyPoint> keypoints_1, keypoints_2;
Mat descriptors_1, descriptors_2;
//detector->detect( img1, keypoints_1 );
//detector->detect( img2, keypoints_2 );
 
f2d->detectAndCompute(g1,Mat(),keypoints_1,descriptors_1);
f2d->detectAndCompute(g2,Mat(),keypoints_2,descriptors_2);

//-- Step 2: Calculate descriptors (feature vectors)
//Ptr<SURF> extractor= SURF::create();
//Ptr<Feature2D> fd = SIFT::create();
//extractor->compute( img1, keypoints_1, descriptors_1 );
//extractor->compute( img2, keypoints_2, descriptors_2 );
//fd->compute( img1, keypoints_1, descriptors_1 );
//fd->compute( img2, keypoints_2, descriptors_2 );
//-- Step 3: Matching descriptor vectors with a brute force matcher
//BFMatcher matcher(NORM_L2, true);   //BFMatcher matcher(NORM_L2);
FlannBasedMatcher matcher;
std::vector< DMatch> matches;
vector<vector<DMatch > > match_candidates;
matcher.knnMatch( descriptors_1, descriptors_2, match_candidates,2);
Mat img_matches;
drawMatches(g1, keypoints_1, g2, keypoints_2, match_candidates, img_matches);
imshow("matchesMirror", img_matches);
waitKey(0);

double max_dist = 0; 
double min_dist = 100;
//-- Quick calculation of max and min distances between keypoints
for( int i = 0; i < match_candidates.size(); i++ )
{ double dist = match_candidates[i][0].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
   if (match_candidates[i][0].distance < 0.8 * match_candidates[i][1].distance)
      matches.push_back(match_candidates[i][0]);
}

/*for (int i = 0; i < match_candidates.size(); i++)
{
   if (match_candidates[i][0].distance < 0.8 * match_candidates[i][1].distance)
      matches.push_back(match_candidates[i][0]);
}*/
std::vector< DMatch > good_matches;
vector<Point2f>imgpts1,imgpts2;
for( int i = 0; i < matches.size(); i++ )
{
    if( matches[i].distance <= max(5*min_dist, 0.02) ){
        good_matches.push_back( matches[i]);
        imgpts1.push_back(keypoints_1[matches[i].queryIdx].pt);
        imgpts2.push_back(keypoints_2[matches[i].trainIdx].pt);
    }

}
drawMatches(g1, keypoints_1, g2, keypoints_2, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
imshow("goodmatches_mirror", img_matches);
waitKey(0);

std::vector<uchar> status;
cv::Mat F = cv::findFundamentalMat(imgpts1, imgpts2, cv::FM_RANSAC, 3., 0.99, status);   //FM_RANSAC

Mat H1,H2;
cv::stereoRectifyUncalibrated(imgpts1, imgpts1, F, g1.size(), H1, H2);

cv::Mat rectified1(g1.size(), g1.type());
cv::warpPerspective(g1, rectified1, H1, g1.size());

cv::Mat rectified2(g2.size(), g2.type());
cv::warpPerspective(g2, rectified2, H2, g2.size());

sgbm->compute(rectified1, rectified2, disparity);
minMaxLoc( disparity, &minVal, &maxVal );
printf("Min disp: %f Max value: %f after rectification\n", minVal, maxVal);
disparity.convertTo( disparity1, CV_8UC1, 255/(maxVal - minVal));  
applyColorMap(disparity1, falsemap, cv::COLORMAP_JET);
imshow("disparity_rectified_mirror", disparity1);
imshow("disparity_rectified_color_mirror", falsemap);
imwrite("disparity_rectified_color_mirror.jpg", falsemap);
waitKey(0);


return(0);

}

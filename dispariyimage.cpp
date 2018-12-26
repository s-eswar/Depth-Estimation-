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
#include </home/eswar/opencv_softies/opencv/opencv_contrib/modules/xfeatures2d/include/opencv2/xfeatures2d/nonfree.hpp>
#include <python2.7/Python.h>

using namespace cv;
using namespace std;
using namespace xfeatures2d;

int main(int argc, char** argv)
{
Mat img1, img2, g1, g2,color;
Mat disp1, disp18,disp2,disp28,disparity,disparity1,falsemap;
Mat falseColorsMap, sfalseColorsMap;
img1 = imread(argv[1],CV_8UC1);
img2 = imread(argv[2],CV_8UC1);
//img1 =cvarrToMat(argv[1]);
//img2 =cvarrToMat(argv[2]);
// Size size(360,640);//the dst image size,e.g.100x100
// resize(img1,img1,size);//resize image
// resize(img2,img2,size);//resize image
int max_disp;
// cout << "this is BM" << endl;
//  int ndisparities = 112;/**< Range of disparity */
//  int SADWindowSize =13; /**< Size of the block window. Must be odd */
// // 
//  Ptr<StereoBM> sbm = StereoBM::create(ndisparities,SADWindowSize);
// 	
//   //-- 3. Calculate the disparity image
//   sbm->compute( img1, img2, disp1);

  //-- Check its extreme values
  double minVal; double maxVal;

//   minMaxLoc( disp1, &minVal, &maxVal );
// 
// //   printf("Min disp: %f Max value: %f for SBM\n", minVal, maxVal);
// 
//   //-- 4. Display it as a CV_8UC1 image
//   disp1.convertTo( disp18, CV_8UC1, 255/(maxVal - minVal));
// 
//   //namedWindow( "windowDisparity", WINDOW_NORMAL );
//   applyColorMap(disp18, falseColorsMap, cv::COLORMAP_JET);
// //   imshow( "BM", falseColorsMap);
// // // 
// //   imshow( "windowDisparity", disp18);
// //   waitKey(1000);
// //   
//   //-- 5. Save the image
//    imwrite("SBM_sample.png", disp18);
   
   
// //   imwrite("SBMdisparity.png", falseColorsMap);
  Ptr<StereoSGBM> sgbm = StereoSGBM::create(0,    //int minDisparity
                                        112,     //int numDisparities
                                        11,      //int SADWindowSize
                                        200,    //int P1 = 0
                                        2600,   //int P2 = 0
                                        255,     //int disp12MaxDiff = 0
                                        20,     //int preFilterCap = 0
                                        0,      //int uniquenessRatio = 0
                                        90,    //int speckleWindowSize = 0
                                        2,     //int speckleRange = 0
                                        true);  //bool fullDP = false
                                        
// 
  sgbm->compute(img1, img2, disp2);
  minMaxLoc( disp2, &minVal, &maxVal );
// // //   printf("Min disp: %f Max value: %f for SGBM\n", minVal, maxVal);
  disp2.convertTo( disp28, CV_8UC1, 255/(maxVal - minVal));
//   char filename[] = "stop.py";
//   FILE* fp;
    for(int i=0;i<disp28.rows;i++)
    {
        for(int j=0; j<disp28.cols;j++)
        {
            if((int)disp28.at<uchar>(i,j) > 200)
            {
                Py_Initialize();
                PyRun_SimpleString("print 'Hi' \n");
                Py_Finalize();
                  exit(2);
            }
        }
    }
// //   applyColorMap(disp28, sfalseColorsMap, cv::COLORMAP_JET);
// // //   namedWindow("BM",WINDOW_NORMAL);
// // //   imshow( "BM", falseColorsMap);
// // //   imshow( "windowDisparity", disp18);
// // //   imshow( "SGBM",sfalseColorsMap);
// // //   imshow( "sgbm", disp28);
//   imwrite("SGBM_sample.png", disp28);
//   getchar();
//   imwrite("SGBMdisparity.png", sfalseColorsMap);
//    waitKey(0);


// int minHessian = 400;
// // Ptr<Feature2D> f2d = SIFT::create();
// Ptr<SURF> detector = SURF::create(minHessian);
// std::vector<KeyPoint> keypoints_1, keypoints_2;
// Mat descriptors_1, descriptors_2;
// detector->detect( img1, keypoints_1 );
// detector->detect( img2, keypoints_2 );
//  
// // f2d->detectAndCompute(img1,Mat(),keypoints_1,descriptors_1);
// // f2d->detectAndCompute(img2,Mat(),keypoints_2,descriptors_2);
// 
// //-- Step 2: Calculate descriptors (feature vectors)
// Ptr<SURF> extractor= SURF::create();
// //Ptr<Feature2D> fd = SIFT::create();
// extractor->compute( img1, keypoints_1, descriptors_1 );
// extractor->compute( img2, keypoints_2, descriptors_2 );
// //fd->compute( img1, keypoints_1, descriptors_1 );
// //fd->compute( img2, keypoints_2, descriptors_2 );
// //-- Step 3: Matching descriptor vectors with a brute force matcher
// //BFMatcher matcher(NORM_L2, true);   //BFMatcher matcher(NORM_L2);
// FlannBasedMatcher matcher;
// std::vector< DMatch> matches;
// vector<vector<DMatch > > match_candidates;
// matcher.knnMatch( descriptors_1, descriptors_2, match_candidates,3);
// Mat img_matches;
// drawMatches(img1, keypoints_1, img2, keypoints_2, match_candidates, img_matches);
// imshow("matches", img_matches);
// waitKey(0);
// 
// double max_dist = 0; 
// double min_dist = 100;
// //-- Quick calculation of max and min distances between keypoints
// /*for( int i = 0; i < match_candidates.size(); i++ )
// { double dist = match_candidates[i][0].distance;
//     if( dist < min_dist ) min_dist = dist;
//     if( dist > max_dist ) max_dist = dist;
//    if (match_candidates[i][0].distance < 0.9 * match_candidates[i][1].distance)
//       matches.push_back(match_candidates[i][0]);
// }*/
// 
// for (int i = 0; i < match_candidates.size(); i++)
// {
//    if (match_candidates[i][0].distance < 0.8 * match_candidates[i][1].distance)
//       matches.push_back(match_candidates[i][0]);
// }
// std::vector< DMatch > good_matches;
// vector<Point2f>imgpts1,imgpts2;
// for( int i = 0; i < matches.size(); i++ )
// {
//     if( matches[i].distance <= max(4.5*min_dist, 0.02) ){
//         good_matches.push_back( matches[i]);
//         imgpts1.push_back(keypoints_1[matches[i].queryIdx].pt);
//         imgpts2.push_back(keypoints_2[matches[i].trainIdx].pt);
//     }
// 
// }
// drawMatches(img1, keypoints_1, img2, keypoints_2, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
// imshow("goodmatches", img_matches);
// waitKey(0);
// 
// std::vector<uchar> status;
// cv::Mat F = cv::findFundamentalMat(imgpts1, imgpts2, cv::FM_RANSAC, 3, 0.99, status);   //FM_RANSAC
// 
// Mat H1,H2;
// cv::stereoRectifyUncalibrated(imgpts2, imgpts1, F, img1.size(), H1, H2);
// 
// cv::Mat rectified1(img1.size(), img1.type());
// cv::warpPerspective(img1, rectified1, H1, img1.size());
// 
// cv::Mat rectified2(img2.size(), img2.type());
// cv::warpPerspective(img2, rectified2, H2, img2.size());
// 
// sgbm->compute(rectified1, rectified2, disparity);
// minMaxLoc( disparity, &minVal, &maxVal );
// printf("Min disp: %f Max value: %f after rectification\n", minVal, maxVal);
// disparity.convertTo( disparity1, CV_8UC1, 255/(maxVal - minVal));  
// applyColorMap(disparity1, falsemap, cv::COLORMAP_JET);
// imshow("disparity_rectified", disparity1);
// imshow("disparity_rectified_color", falsemap);
// imwrite("disparity_rectified_color.jpg", falsemap);
// imwrite("disparity_rectified.jpg", disparity1);
// waitKey(0);


return(0);

}

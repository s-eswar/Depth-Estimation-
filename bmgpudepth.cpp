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
UMat img1, img2, g1, g2,color;
UMat disp1, disp18,disp2,disp28,disparity,disparity1,falsemap;
imread(argv[1],CV_8UC1).copyTo(img1);
imread(argv[2],CV_8UC1).copyTo(img2);

int max_disp;
cout << "this is BM" << endl;
 int ndisparities = 112;/**< Range of disparity */
 int SADWindowSize =13; /**< Size of the block window. Must be odd */
// 
 Ptr<StereoBM> sbm = StereoBM::create(ndisparities,SADWindowSize);
	
  //-- 3. Calculate the disparity image
  sbm->compute( img1, img2, disp1);

  //-- Check its extreme values
  double minVal; double maxVal;

  minMaxLoc( disp1, &minVal, &maxVal );

  //-- 4. Display it as a CV_8UC1 image
  disp1.convertTo( disp18, CV_8UC1, 255/(maxVal - minVal));

  //-- 5. Save the image
   imshow( "windowDisparity", disp18);
   imwrite("SBM_sample.png", disp18);
   waitKey(0);
return(0);

}

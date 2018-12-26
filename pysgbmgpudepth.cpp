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

 //-- Check its extreme values
 double minVal; double maxVal;

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
                                        
 sgbm->compute(img1, img2, disp2);
 minMaxLoc( disp2, &minVal, &maxVal );
 disp2.convertTo( disp28, CV_8UC1, 255/(maxVal - minVal));

 imshow( "sgbm", disp28);
 imwrite("SGBM_sample.png", disp28);
 waitKey(0);

return(0);

}

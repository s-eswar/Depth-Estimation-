#include <opencv2/opencv.hpp>
#include </home/eswar/softwares/opencv_contrib-3.2.0/modules/contrib_world/include/opencv2/contrib_world.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <stdio.h>
#include <iostream>
#include <omp.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    
    //initialize and allocate memory to load the video stream from camera 
    VideoCapture cap0(argv[1]);
    VideoCapture cap1(argv[2]);
   int frame_width=   cap0.get(CV_CAP_PROP_FRAME_WIDTH);
   int frame_height=  cap0.get(CV_CAP_PROP_FRAME_HEIGHT);
//    VideoWriter video("out.avi",CV_FOURCC('M','J','P','G'),cap0.get(CV_CAP_PROP_FPS),cvSize(64,64),false); 
    if( !cap0.isOpened() ) return 1;
    if( !cap1.isOpened() ) return 1;
     
//     cap0.set(CV_CAP_PROP_FRAME_WIDTH, 64);
//     cap0.set(CV_CAP_PROP_FRAME_HEIGHT, 64);
//     cap1.set(CV_CAP_PROP_FRAME_WIDTH, 64);
//     cap1.set(CV_CAP_PROP_FRAME_HEIGHT, 64);
        cv::Mat frame0, frame1;
        cv::Mat frame0gray, frame1gray;
        cv::Mat dispbm,dispsgbm;
        cv::Mat dispnorm_bm;
	Mat dispnorm_sgbm;
        cv::Mat falseColorsMap, sfalseColorsMap;
//         cv::UMat gframe0, gframe1, gframe0gray, gframe1gray;
//      int ndisparities = 64;   /**< Range of disparity */
//      int SADWindowSize = 19;
//      Ptr<StereoBM> sbm = StereoBM::create( ndisparities, SADWindowSize );
        VideoWriter outputVideo;
	if (!outputVideo.isOpened())
		outputVideo.open("result.avi", CV_FOURCC('M', 'P', 'E', 'G'), cap0.get(CV_CAP_PROP_FPS), Size(64,64));
     Ptr<StereoSGBM> sgbm = StereoSGBM::create( 0,    //int minDisparity
                                               16,    //int numDisparities
                                                5,    //int SADWindowSize
                                               60,    //int P1 = 0
                                             2400,    //int P2 = 0
                                               90,    //int disp12MaxDiff = 0
                                               16,    //int preFilterCap = 0
                                                1,    //int uniquenessRatio = 0
                                               60,    //int speckleWindowSize = 0
                                               20,    //int speckleRange = 0
                                              true);  //bool fullDP = false


   //-- Check its extreme values
   double minVal; double maxVal;
   int key=0;
   // #pragma omp parallel
    while(true) {
        //grab and retrieve each frames of the video sequentially 
        cap0 >> frame0;
        cap1 >> frame1;
      if(frame0.empty()) {
      cout<<"empty"<<endl;
      exit(1);
      }
      if(frame1.empty()) {
      cout<<"empty"<<endl;
      exit(2);
      }
//       frame0.copyTo(gframe0);
//       frame1.copyTo(gframe1);
       resize(frame0,frame0,Size(64,64));
       resize(frame1,frame1,Size(64,64));
//         imshow("Video0", frame0);
//         imshow("Video1", frame1);
        
         cvtColor(frame0,frame0gray,CV_BGR2GRAY);
         cvtColor(frame1,frame1gray,CV_BGR2GRAY); 

//         sbm->compute( frame0gray, frame1gray, dispbm );
//         minMaxLoc( dispbm, &minVal, &maxVal );
//         dispbm.convertTo( dispnorm_bm, CV_8UC1, 255/(maxVal - minVal));

        sgbm->compute(frame0gray, frame1gray, dispsgbm);
        minMaxLoc( dispsgbm, &minVal, &maxVal );
        dispsgbm.convertTo( dispnorm_sgbm, CV_8UC1, 255/(maxVal - minVal));
        
//         medianBlur(dispnorm_bm,dispnorm_bm, 3);
//        medianBlur(dispnorm_sgbm,dispnorm_sgbm, 3);	
        
//        	applyColorMap(dispnorm_bm, falseColorsMap, cv::COLORMAP_JET);
//         applyColorMap(dispnorm_sgbm, sfalseColorsMap, cv::COLORMAP_JET);
//         imshow( "SBM", falseColorsMap);
//         imshow( "JSGBM",sfalseColorsMap);
//         imshow( "BM", dispnorm_bm);
        outputVideo.write(dispnorm_sgbm);
        imshow( "SGBM",dispnorm_sgbm);
   

//        sbm->compute(frame0,frame1,dispbm);
//        normalize(dispbm, dispnorm_bm, 0, 255, CV_MINMAX, CV_8UC1);

//        sbm(frame0gray,frame1gray, dispsgbm);
//        normalize(dispsgbm, dispnorm_sgbm, 0, 65535, CV_MINMAX, CV_16UC1);

        
//        cv::imshow("dispbm", dispnorm_bm);
//        cv::imshow("dispsgbm", dispnorm_sgbm);

        //wait for 40 milliseconds
//         cv::waitKey(0);
        int c = cvWaitKey(1);

//         exit the loop if user press "Esc" key  (ASCII value of "Esc" is 27) 
        if(27 == char(c)) break;
    }
//     video.release();
    return 0;

}

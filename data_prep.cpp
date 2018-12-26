#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    VideoCapture cap("cat021_01.mp4");
    if( !cap.isOpened() ) return 1;
    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH); 
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); 
    int fps = cap.get(CV_CAP_PROP_FPS);
    printf("frame width = %d\n",frame_width);
    printf("frame height = %d\n",frame_height);
    printf("fps = %d\n",fps);
//     Rect roi1(0,0,frame_width/2,frame_height);
    //Rect roi2(0,frame_width/2,frame_width/2,frame_height);
//    Mat crop;
    VideoWriter leftvideo("leftout.mp4",CV_FOURCC('M','J','P','G'),fps, Size(frame_width/2,frame_height));
    VideoWriter rightvideo("rightout.mp4",CV_FOURCC('M','J','P','G'),fps, Size(frame_width/2,frame_height));
    
    while(true)
    { 
      Mat frame;
      cap >> frame;
      if (frame.empty())
            break;
      Mat left = frame(Rect(0,0,frame_width/2,frame_height));
      Mat right = frame(Rect(frame_width/2,0,frame_width/2,frame_height));

      leftvideo.write(left);
      rightvideo.write(right);
      imshow("frame", frame);

      if(waitKey(30) >= 0) break;
    }

 // When everything done, release the video capture object
    cap.release();
 // Closes all the frames
    destroyAllWindows();

 return 0;
}

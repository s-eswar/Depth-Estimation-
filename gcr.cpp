#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char ** argv)
{
// Open another image
Mat image,background;
image= cv::imread(argv[1]);

Mat image2 = image.clone();

// define bounding rectangle
cv::Rect rectangle(30,30,image.cols -60,image.rows-60);

cv::Mat result; // segmentation result (4 possible values)
cv::Mat bgModel,fgModel; // the models (internally used)

// GrabCut segmentation
cv::grabCut(image,    // input image
            result,   // segmentation result
            rectangle,// rectangle containing foreground
            bgModel,fgModel, // models
            5,        // number of iterations
            cv::GC_INIT_WITH_RECT); // use rectangle
cout << "ok here" <<endl;
// Get the pixels marked as likely foreground
cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);

// Generate output image
cv::Mat foreground(image.size(),CV_8UC3,cv::Scalar(255,255,255));
//cv::Mat background(image.size(),CV_8UC3,cv::Scalar(255,255,255));
image.copyTo(foreground,result); // bg pixels not copied
image.copyTo(background,~result); // bg pixels copied


// draw rectangle on original image
cv::rectangle(image, rectangle, cv::Scalar(255,255,255),1);
cv::Mat binaryImage = Mat::zeros(background.rows, background.cols, CV_8UC3);

for (int i=0; i<background.rows; ++i){
    for (int j=0; j<background.cols; ++j){
        // choose pixels that are certainly or likely background
        if (background.at<uchar>(i,j) == GC_BGD || background.at<uchar>(i,j) == GC_BGD){
            binaryImage.at<uchar>(i,j) = 255;
        }
    }
}
imwrite("img_1.jpg",image);

imwrite("Foregroundr.jpg",foreground);
//Mat background = image2 - foreground;
imwrite("Backgroundr.jpg",background);
imshow("dsp",binaryImage);
return 0;
}

/*=============================================================================
#     FileName: faceDetect.cpp
#         Desc: 人脸检测
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-20 13:59:40
#      History:
=============================================================================*/
#include "faceDetect.h"
#include "opencv2/opencv.hpp"
#include "log.h"

static cv::CascadeClassifier face_cascade;

void detectInit()
{
    // 加载级联分类器文件
    std::string face_cascade_name = "haarcascade_frontalface_default.xml";
    if (!face_cascade.load(face_cascade_name)) {
        std::cout << "加载级联分类器失败" << std::endl;
        exit(-1);
    }
}

cv::Mat detectOneFace(cv::Mat& img)
{
    Log log(__LOGARG__,1);
    cv::Mat img_gray;
    std::vector<cv::Rect> facesRect;

    log << "image:channels=" << img.channels() << Log::endl;
    cv::cvtColor(img, img_gray, CV_BGR2GRAY);
    cv::equalizeHist(img_gray, img_gray);

    // 多尺寸检测人脸
    face_cascade.detectMultiScale(img_gray, facesRect, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

    if (facesRect.size()==0) {
        return img;
    }
    double maxSquare = facesRect[0].width*facesRect[0].height;
    int maxSquareIdx = 0;
    for(int i=1; i<facesRect.size(); i++)
    {
        double square = facesRect[i].width*facesRect[i].height;
        if (square>maxSquare) {
            maxSquare = square;
            maxSquareIdx = i;
        }
   }
   int i = maxSquareIdx;
   return img(cv::Rect(facesRect[i].x,facesRect[i].y,facesRect[i].width,facesRect[i].height));
}


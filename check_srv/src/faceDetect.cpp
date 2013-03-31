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
#include "opencv2/opencv.hpp"
#include "log.h"
#include <iostream>
#include <cstdio>
#include<ctime>
#include <sstream>
#include <string>

cv::CascadeClassifier face_cascade;

// 函数声明
void detectFace(cv::CascadeClassifier& face_cascade, cv::Mat& img, std::vector<cv::Mat>& o_faces);

void detectInit()
{
    Log log(__LOGARG__,1);
    //-- 1. 加载级联分类器文件
    std::string face_cascade_name = "haarcascade_frontalface_alt_tree.xml";
    if (!face_cascade.load(face_cascade_name)) {
        log << "--(!)Error loading" << Log::endl;
        exit(-1);
    }
}

void detectFace(cv::CascadeClassifier& face_cascade, cv::Mat& img, std::vector<cv::Mat>& o_faces)
{
    std::vector<cv::Rect> facesRect;
    cv::Mat img_gray;

    cv::cvtColor(img, img_gray, CV_BGR2GRAY);
    cv::equalizeHist(img_gray, img_gray);

    //-- 多尺寸检测人脸
    face_cascade.detectMultiScale(img_gray, facesRect, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

    for(int i=0; i<facesRect.size(); i++)
    {
        cv::Mat face = img(cv::Rect(facesRect[i].x,facesRect[i].y,facesRect[i].width,facesRect[i].height));
        o_faces.push_back(face);
        rectangle(img,
                cv::Point(facesRect[i].x, facesRect[i].y),
                cv::Point(facesRect[i].x+facesRect[i].width, facesRect[i].y+facesRect[i].height),
                cv::Scalar(0, 255, 255),
                1,
                8);
   }
}

// 测试
void test_detectFace()
{
    std::vector<cv::Mat> o_faces;
    cv::Mat img;    // 照片

    detectInit();
    detectFace(face_cascade, img, o_faces);
}



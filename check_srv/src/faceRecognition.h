/*=============================================================================
#     FileName: faceRecognition.h
#         Desc: 人脸识别
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-19 20:16:06
#      History:
=============================================================================*/
#ifndef __FACE_RECOGNITION_H_
#define __FACE_RECOGNITION_H_

#include "opencv2/opencv.hpp"

bool updateFaceLibrary();
int faceRecognition(cv::Mat& image);

#endif


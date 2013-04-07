/*=============================================================================
#     FileName: faceDetect.h
#         Desc: 人脸检测
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-04-03 21:50:50
#      History:
=============================================================================*/
#ifndef __FACE_DECTECT_H_
#define __FACE_DECTECT_H_

#include "opencv2/opencv.hpp"

void detectInit();
cv::Mat detectOneFace(cv::Mat& img);

#endif


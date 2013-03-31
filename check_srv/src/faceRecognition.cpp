/*=============================================================================
#     FileName: faceRecognition.cpp
#         Desc: 人脸识别
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-28 20:41:22
#      History:
=============================================================================*/
#include "opencv2/opencv.hpp"
#include "log.h"

// 归一化
static cv::Mat norm_0_255(cv::InputArray _src)
{
    cv::Mat src = _src.getMat();
    // Create and return normalized image:
    cv::Mat dst;
    switch(src.channels()) {
    case 1:
        //cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, cv::CV_8UC1);
        break;
    case 3:
        //cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, cv::CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

// 先进行人脸检测，截取人脸区域
// 然后进行归一化
void loadImageFromDB(std::vector<cv::Mat>& images, std::vector<int> labels)
{
}

// 数据库中保存的图片必须是灰度图，且归一化
void updateFaceLibrary()
{
    Log log(__LOGARG__,1);
    // These vectors hold the images and corresponding labels.
    std::vector<cv::Mat> images;
    std::vector<int> labels;

    // Load image from db
    loadImageFromDB(images,labels);

    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        std::string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        log << error_message << Log::endl;
    }

    cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
    // cv::Ptr<FaceRecognizer> model = cv::createEigenFaceRecognizer();
    // cv::Ptr<FaceRecognizer> model = cv::createLBPHFaceRecognizer();
    model->train(images, labels);
    model->save("fisherfaces_at.xml");
}

// 人脸识别
int faceRecognition(cv::Mat& image)
{
    cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
    // cv::Ptr<FaceRecognizer> model = cv::createEigenFaceRecognizer();
    // cv::Ptr<FaceRecognizer> model = cv::createLBPHFaceRecognizer();
    model->load("fisherfaces_at.xml");
    int predictedLabel = model->predict(image);
    return predictedLabel;
}





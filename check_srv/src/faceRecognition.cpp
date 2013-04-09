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
#include "faceRecognition.h"
#include "faceDetect.h"
#include "db.h"
#include "log.h"

#define DST_IMG_WIDTH 24        //需要调整图片后的尺寸宽度
#define SRC_IMG_HEIGH 24        //需要调整图片后的尺寸高度

// 归一化
cv::Mat norm_0_255(cv::InputArray _src)
{
    cv::Mat src = _src.getMat();
    // Create and return normalized image:
    cv::Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

// 先进行人脸检测，截取人脸区域
// 然后进行归一化
bool loadImageFromDB(cv::vector<cv::Mat>& images, cv::vector<int>& labels)
{
    Log log(__LOGARG__,1);
    images.clear();
    labels.clear();
    cv::vector<DB::model_img_Rec> recs;
    bool ret = DB::model_img_select_all(recs);
    if (!ret) {
        return false;
    }
    for (int i=0; i<recs.size(); ++i) {
        int emp_id = recs[i].emp_id;
        AutoType photo = recs[i].photo;
        cv::Mat mat = AutoType2Mat(photo);
        mat = detectOneFace(mat);
        //缩放
        cv::Size dsize(DST_IMG_WIDTH,SRC_IMG_HEIGH);
        cv::Mat dst(dsize,mat.type());
        cv::resize(mat, dst,dsize);
        log << "image:channels=" << dst.channels() << Log::endl;
        cv::cvtColor(dst, dst, CV_BGR2GRAY);
        dst.convertTo(dst,CV_32SC1);
        dst = norm_0_255(dst);
        cv::imwrite("tmp.jpg",dst);
        images.push_back(dst);
        labels.push_back(emp_id);
    }
    return true;
}

// 数据库中保存的图片必须是灰度图，且归一化
bool updateFaceLibrary()
{
    Log log(__LOGARG__,1);
    // These vectors hold the images and corresponding labels.
    cv::vector<cv::Mat> images;
    cv::vector<int> labels;

    // Load image from db
    bool ret = loadImageFromDB(images,labels);
    if (!ret) {
        log << "读取数据失败" << Log::endl;
        return false;
    }
    log << "type:" << cv::InputArray(labels).getMat().type() << Log::endl;
    log << "total:" << cv::InputArray(labels).getMat().total() << Log::endl;

    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        std::string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        log << error_message << Log::endl;
    }

    //cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
    cv::Ptr<cv::FaceRecognizer> model = cv::createEigenFaceRecognizer();
    // cv::Ptr<cv::FaceRecognizer> model = cv::createLBPHFaceRecognizer();
    model->train(images, labels);
    model->save("fisherfaces_at.xml");
    return true;
}

// 人脸识别
int faceRecognition(cv::Mat& image)
{
    Log log(__LOGARG__,1);
    //cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
    cv::Ptr<cv::FaceRecognizer> model = cv::createEigenFaceRecognizer();
    // cv::Ptr<cv::FaceRecognizer> model = cv::createLBPHFaceRecognizer();
    image = detectOneFace(image);
    //缩放
    cv::Size dsize(DST_IMG_WIDTH,SRC_IMG_HEIGH);
    cv::Mat dst(dsize,image.type());
    cv::resize(image, dst, dsize);
    log << "image:channels=" << dst.channels() << Log::endl;
    cv::cvtColor(dst, dst, CV_BGR2GRAY);
    dst.convertTo(dst,CV_32SC1);
    dst = norm_0_255(dst);

    model->load("fisherfaces_at.xml");
    int predictedLabel = model->predict(dst);
    return predictedLabel;
}





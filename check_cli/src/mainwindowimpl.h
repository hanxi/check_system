/*=============================================================================
#     FileName: mainwindowimpl.h
#         Desc: 客户端，实现拍照功能
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-15 18:18:30
#      History:
=============================================================================*/
#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H

//QT
#include <QMainWindow>
#include <QImage>
#include <QTimer>     // 设置采集数据的间隔时间

//opencv
#include <opencv2/opencv.hpp> //包含opencv库头文件

#include "ui_mainwindow.h"

//
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	virtual ~MainWindowImpl();

public slots:
    void toCheckFace();     // 跳到签到界面

private slots:
	void takingPictures();  // 拍照
	void checkIn();         // 签到
	void searchInfo();      // 查询
    void readShowImg();     // 读取图片并显示
	void takingPicAgain();  // 重拍
	void submitPic();       // 提交
    void clearUIFace();     // 隐藏界面元素
    void toAddNewEmp();     // 跳转界面到添加新用户
    void toCheckRightFace();// 跳到签到确认界面
    void signIn();          // 注册
    void cancelSignIn();    // 取消注册

private:
	QTimer           *m_timer;
	QImage            m_image;
    cv::VideoCapture  m_cap;   // 视频获取结构
	cv::Mat           m_frame; // 存放每一帧图像

	void openCamara();      // 打开摄像头
	void closeCamara();     // 关闭摄像头。
    void showImg();         // 显示图片
	bool readFrame();       // 读取当前帧信息
};
#endif





/*=============================================================================
#     FileName: mainwindowimpl.cpp
#         Desc: 拍照，保存，上传
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-15 18:18:55
#      History:
=============================================================================*/
#include "mainwindowimpl.h"
#include "net.h"
#include "prot.h"
#include "log.h"

//STD
#include <iostream>
#include <string>

//QT
#include <QString>
#include <QDateTime>

const int IMAGE_HEIGHT=640;
const int IMAGE_WIDTH=800;
extern Net *gNet;
const int MAX_IMG_SIZE = 10240;

//
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
	setupUi(this);
	pushButtonCheckIn->setEnabled(true);
	pushButtonSearch->setEnabled(true);
	pushButtonCamara->setEnabled(false);
	pushButtonAgain->setEnabled(false);
	pushButtonSubmit->setEnabled(false);
	
	m_timer   = new QTimer(this);

	/*信号和槽*/
	connect(m_timer, SIGNAL(timeout()), this, SLOT(readShowImg()));  // 时间到，读取当前摄像头信息
	connect(pushButtonCamara, SIGNAL(clicked()), this, SLOT(takingPictures()));
	connect(pushButtonCheckIn, SIGNAL(clicked()), this, SLOT(checkIn()));
	connect(pushButtonSearch, SIGNAL(clicked()), this, SLOT(searchInfo()));
	connect(pushButtonAgain, SIGNAL(clicked()), this, SLOT(takingPicAgain()));
	connect(pushButtonSubmit, SIGNAL(clicked()), this, SLOT(submitPic()));
}

//******************************
//********* 打开摄像头 ***********
void MainWindowImpl::openCamara()
{
	//设置定时器每个多少毫秒发送一个timeout()信号
    m_cap.open(0);                      // 打开摄像头
    if (!m_cap.isOpened())
    {
        std::string err_str("打开摄像头失败");
        std::cout << err_str << std::endl;
    }
    m_cap.set(CV_CAP_PROP_FRAME_WIDTH, IMAGE_WIDTH);
    m_cap.set(CV_CAP_PROP_FRAME_HEIGHT,IMAGE_HEIGHT);
	m_timer->start(60);                 // 开始计时，超时则发出timeout()信号
}

//********************************
//***关闭摄像头，释放资源，必须释放***
void MainWindowImpl::closeCamara()
{
	m_timer->stop();         // 停止读取数据。
	m_cap.release();         // 释放内存；
}

//**********************************
//********* 读取摄像头信息 ***********
bool MainWindowImpl::readFrame()
{
	bool isReadRight = m_cap.read(m_frame);// 从摄像头中抓取并返回每一帧
    if (!isReadRight)
    {
        std::string err_str("读取帧失败");
        std::cout << err_str << std::endl;
        return false;
    }
    return true;
}

//**********************************
//********* 显示图像 ***********
void MainWindowImpl::showImg()
{
	// 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    cv::Mat tmp;
    cvtColor(m_frame, tmp, CV_BGR2RGB);
	m_image = QImage((unsigned char*)tmp.data, m_frame.cols, m_frame.rows, m_frame.step, QImage::Format_RGB888);
	labelShow->setPixmap(QPixmap::fromImage(m_image.scaled(labelShow->size(),Qt::KeepAspectRatio)));  // 将图片显示到labelShow上
}

//读并显示图像
void MainWindowImpl::readShowImg()
{
    if (!readFrame())
    {
        return;
    }
    showImg();
}

//**************************
//********* 拍照 ***********
void MainWindowImpl::takingPictures()
{
    if (!readFrame())
    {
        return;
    }
	m_timer->stop();         // 停止读取数据。
    // 保存图片
    QDateTime t = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = t.toString("yyyyMMddhhmmss"); //设置显示格式
    std::string picName = "./images/"+str.toStdString()+".jpg";
    std::cout << picName << std::endl;
    imwrite(picName.c_str(), m_frame );
    showImg();
	pushButtonCamara->setEnabled(false);
	pushButtonAgain->setEnabled(true);
	pushButtonSubmit->setEnabled(true);
}

//
void MainWindowImpl::checkIn()
{
    if (!m_cap.isOpened())
	{
        openCamara();
	}
    pushButtonCheckIn->setEnabled(false);
	pushButtonSearch->setEnabled(true);
	pushButtonCamara->setEnabled(true);
	pushButtonAgain->setEnabled(false);
	pushButtonSubmit->setEnabled(false);
}

// 查询
void MainWindowImpl::searchInfo()
{
    if (!m_cap.isOpened())
	{
        openCamara();
	}
	pushButtonCheckIn->setEnabled(true);
	pushButtonSearch->setEnabled(false);
	pushButtonCamara->setEnabled(true);
	pushButtonAgain->setEnabled(false);
	pushButtonSubmit->setEnabled(false);
}

// 重拍
void MainWindowImpl::takingPicAgain()
{
	m_timer->start(60);                 // 开始计时，超时则发出timeout()信号
	pushButtonCamara->setEnabled(true);
	pushButtonAgain->setEnabled(false);
	pushButtonSubmit->setEnabled(false);
}

// 提交
void MainWindowImpl::submitPic()
{
    Log log(__LOGARG__,1);
	// sendToSrv
    char data[MAX_IMG_SIZE] = {0};
    memcpy(data,m_frame.data,sizeof(data));

    Prot prot(protCheckIn_C2S);
    prot.setField("imgBin",data);
    gNet->sendProt(1,protCheckIn_C2S);
}

MainWindowImpl::~MainWindowImpl()
{
	closeCamara();
    delete m_timer;
}

//

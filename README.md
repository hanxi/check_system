check_system
============

人脸识别签到:C/S架构,采用opencv的人脸识别库

### 网络模块

使用Qt自带的网络库实现客户端和服务端数据传输.网络协议格式是自己定义的.网络协议采用配置文件格式,
用protInitTool工具可以将profile.txt文件生成protInit.h文件.

协议用c++的双层map保存.为了实现协议支持字符串和整形两种数据类型,还专门实现了autoType.就是一个autoType.h,因为个人感觉使用
c++自带的字符串类对协议模块来说太重了,就自己实现了个简单的string.

### 日志模块

支持html格式和txt格式

### 客户端

使用Qt做的ui.

### 服务端
使用了sqlite.实现sqlitedbtool自动生成代码sqlitedb.cpp操作数据库表.

### 编译
使用cmake

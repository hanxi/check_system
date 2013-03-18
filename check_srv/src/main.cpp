/*=============================================================================
#     FileName: .cpp
#         Desc: 服务器
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-17 20:30:04
#      History:
=============================================================================*/

#include "net.h"
#include <QtCore/QCoreApplication>

#include "log.h"
#include "prot.h"

Net *gNet;

int main(int argc, char **argv)
{
    Log::s_init("./log.html",1,HTML_LOG);
    Prot::s_init();
    QCoreApplication app(argc, argv);
    gNet = new Net(10086);
    app.exec();
    Log::s_stop();
    delete gNet;
    return 0;
}

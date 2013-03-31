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
#include "db.h"
#include "netOperate.h"
#include "conf.h"

Net *gNet;
Net* getNet()
{
    return gNet;
}

S2M confMap;
S2M& getConfMap()
{
    return confMap;
}

int main(int argc, char **argv)
{
    readConfFile("./srv.conf", confMap);
    Log::s_init("./log.html",1,HTML_LOG);
    Prot::s_init();
    regAllHandler();

    QCoreApplication app(argc, argv);
    int port = 10086;
    if (argc>1) {
        std::string portStr = argv[1];
        if (isAllDigit(portStr)) {
            port = str2num(portStr);
        }
    }
    gNet = new Net(port);
    if (DB::start()) {
        Log log(__LOGARG__,1);
        log << "数据库成功打开" << Log::endl;
    }
    app.exec();
    Log::s_stop();
    delete gNet;
    DB::stop();
    return 0;
}

#include <QApplication>
#include "mainwindowimpl.h"

#include "globalVar.h"
#include "log.h"
#include "prot.h"
#include "net.h"
#include "conf.h"
#include "netOperate.h"

Net *gNet;
Net* getNet()
{
    return gNet;
}

int gSockId;
//
int main(int argc, char ** argv)
{
    Log::s_init("./log.html",1,HTML_LOG);
    Prot::s_init();
    regAllHandler();

    S2M confMap;
    readConfFile("./cli.conf", confMap);
    S2S& networkConf = confMap["network"];
    const char *ip = (networkConf["ip"]).c_str();
    int port = str2num(networkConf["port"]);

    QApplication app(argc, argv);
    gNet = new Net(ip,port);
	MainWindowImpl win;
	win.show();
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	app.exec();

    delete gNet;
    Log::s_stop();
    return 0;
}

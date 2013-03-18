#include <QApplication>
#include "mainwindowimpl.h"

#include <log.h>
#include <prot.h>
#include <net.h>

Net *gNet;
//
int main(int argc, char ** argv)
{
    Log::s_init("./log.html",1,HTML_LOG);
    Prot::s_init();

    QApplication app(argc, argv);
    gNet = new Net("127.0.0.1",10086);
	MainWindowImpl win;
	win.show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	app.exec();

    delete gNet;
    Log::s_stop();
    return 0;
}


#include "net.h"

#include <QtCore/QCoreApplication>

#include "log.h"
#include "prot.h"

int main(int argc, char **argv)
{
    Log::s_init("./log.html",1,HTML_LOG);
    Prot::s_init();
    QCoreApplication a(argc, argv);
    Net net(10087);
    return a.exec();
    Log::s_stop();
}


#include "net.h"

#include <QtCore/QCoreApplication>

#include "log.h"

int main(int argc, char **argv)
{
    Log::s_init("./log.html",1,HTML_LOG);
    QCoreApplication a(argc, argv);
    Net net(10087);
    return a.exec();
    Log::s_stop();
}

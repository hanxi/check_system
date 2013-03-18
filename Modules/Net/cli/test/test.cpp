#include "net.h"

#include <QtCore/QCoreApplication>

#include "log.h"
#include "prot.h"

int main(int argc, char **argv)
{
    Log::s_init("./log.html",1,HTML_LOG);
    Log log(__LOGARG__,1);
    Prot::s_init();
    Prot prot(1);
    prot.setField("name","hanxi2");
    prot.setField("passwd","123456");

    prot.setProt(2);
    prot.setField("name","22");

    QCoreApplication a(argc, argv);
    Net *net;
    net = new Net("127.0.0.1",10087);
    for (int i=0; i<10; i++) {
        net->sendProt(1,i);
        log << "[" << i << "]sendProt ok" << Log::endl;
    }
    Log::s_stop();
    return a.exec();
}

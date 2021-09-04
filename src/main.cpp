#include "mainwindow.h"

#include <QApplication>

int callbackEv(std::string ev){

    if(ev=="kshow"){
       QInputMethod *keyboard = QGuiApplication::inputMethod();
       keyboard->show();

   }else if(ev=="khide"){
        QInputMethod *keyboard = QGuiApplication::inputMethod();
       keyboard->hide();

   }

    return 1;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.sY =  a.primaryScreen()->geometry().size().height();
    w.sX =  a.primaryScreen()->geometry().size().width();
    w.asX = a.primaryScreen()->availableSize().width();
    w.asY = a.primaryScreen()->availableSize().height();
    w.show();

    //QInputMethod *keyboard = QGuiApplication::inputMethod();
    //keyboard->show();
    w.EvtCallBackP = callbackEv;
    return a.exec();

}



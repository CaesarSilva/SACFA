#ifndef SERVERTABS_H
#define SERVERTABS_H
#include <QTabWidget>
#include <QPushButton>
#include <QList>

#include "servertab.h"
class ServerTabs: public QTabWidget
{
    Q_OBJECT
public:
    ServerTabs(QWidget *parent = nullptr);
    int EvtCallBack(std::string ev);
    QList < ServerTab* > TabList;
    void CreateTab(std::string host = "", std::string port = "23073", std::string password = "");
 private:

signals:
      void KbShow();
      void KbHide();
      void SvTabs();
};

#endif // SERVERTABS_H

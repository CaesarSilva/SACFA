#ifndef SERVERTAB_H
#define SERVERTAB_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QList>
#include <QStandardPaths>//TODO: Remove it after tests
#include "mylineedit.h"
#include "serverconnection.h"

class ServerTab : public QWidget
{
    Q_OBJECT
public:
    explicit ServerTab(QWidget *parent = nullptr, std::string host = "", std::string port = "23073", std::string password = "");
    QList < ServerTab* > TabList;
    MyLineEdit * TE_host ;
    MyLineEdit * TE_port ;
    MyLineEdit * TE_pass ;
private:

    ServerConnection * SvConnection ;
    QPushButton *m_button;
   // QPlainTextEdit * TE_host ;

    QTextEdit * TE_output;
    QPushButton *Bt_connect;
    //callbackstuff below
    //bool  CallBackSet = false;
   // void ** CbThiss;
 public:
    void handleConnectButton();
 //   int EvtCallBack(std::string ev);
 //   int CallCallBack(std::string ev, std::string data = "");
    /*typedef*/ //int (*EvtCallBackP)(std::string ev, void*);
 //   void SetCallBack(int (*CallBF)(std::string, void*), void * thiss);

signals:
      void KbShow();
      void KbHide();
      void SvTab();
};

#endif // SERVERTAB_H

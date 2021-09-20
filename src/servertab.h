#ifndef SERVERTAB_H
#define SERVERTAB_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QList>
#include <QStandardPaths>//TODO: Remove it after tests
#include <QScrollBar>//idk if thats necessary
#include <QMdiSubWindow>
#include <vector>
#include "mylineedit.h"
#include "serverconnection.h"
#include "playerssubwindow.h"
#include "shared.h"
/*struct PlayerData{
    std::string name;
    unsigned char team;
    short kills;
    short deaths;
    unsigned char id;
    std::string ip;

}*/
class ServerTab : public QWidget
{
    Q_OBJECT
public:
    explicit ServerTab(QWidget *parent = nullptr, std::string host = "", std::string port = "23073", std::string password = "");
    QList < ServerTab* > TabList;
    MyLineEdit * TE_host ;
    MyLineEdit * TE_port ;
    MyLineEdit * TE_pass ;
    MyLineEdit * TE_input ;
    ServerConnection * SvConnection ;
private:


    QPushButton *m_button;
    QPushButton *bt_plwin;
    QPushButton *bt_sendtext;
   // QPlainTextEdit * TE_host ;

    QTextEdit * TE_output;
    QPushButton *Bt_connect;
    //callbackstuff below
    //bool  CallBackSet = false;
   // void ** CbThiss;
    PlayersSubWindow * PSWin;
 public:
    void handleNewLine(std::string line);
    void handleConnectButton();
    void handlePlnwinBT();
    void handleSendTextBT();
    void handleRefreshX(std::vector<PlayerData> pd, GameData gd);
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

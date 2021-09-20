#ifndef PLAYERSSUBWINDOW_H
#define PLAYERSSUBWINDOW_H

#include <QMdiSubWindow>
#include <QPushButton>
#include <QMenu>
#include <playerline.h>
#include "shared.h"
#include <QVector>
#include <QList>
#include <QScrollArea>
#include <QScrollBar>
//these 2 structures bellow were also defined in serverconnection.h
/*struct GameData{
    std::string time;
    std::string mapname;
    std::string nextmap;
    //std::

};

struct PlayerData{
    std::string name;
    unsigned char team;
    short kills;
    short deaths;
    unsigned char id;
    std::string ip;
    std::string hwid;

}*/
class PlayersSubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    PlayersSubWindow(QWidget *parent = nullptr);
    void handleRefreshX(std::vector<PlayerData> pd, GameData gd);
    QMenu * menu;
    QWidget * PlayersWidget = nullptr;
    QVector<playerLine*>  PlLnVec;
    void handlePlayerLineBt(PlayerData pdata);
    int (*CommandTextCallBack)(void* tthis, std::string command);
    void * CbThiss;
    QScrollArea * PlayersScroll = nullptr;
private:
    void HandleAction(QAction *qA);
    void OnHideBt();
    void OnRefreshBt();
    QPushButton * Bt_Hide;
    QPushButton * Bt_refresh;
};

#endif // PLAYERSSUBWINDOW_H

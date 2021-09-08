#ifndef PLAYERSSUBWINDOW_H
#define PLAYERSSUBWINDOW_H

#include <QMdiSubWindow>
#include <QPushButton>
#include <QMenu>
#include <playerline.h>
#include "shared.h"
#include <QVector>
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
    QVector<playerLine*> * PlLnVec;
private:
    void OnHideBt();
    QPushButton * Bt_Hide;
};

#endif // PLAYERSSUBWINDOW_H

#include "playerssubwindow.h"

PlayersSubWindow::PlayersSubWindow(QWidget *parent):QMdiSubWindow(parent)
{
    menu = new QMenu(this);
    Bt_Hide = new QPushButton(this);
    Bt_Hide ->setGeometry(10,10,100,30);
    connect(Bt_Hide,&QPushButton::pressed,this,&PlayersSubWindow::OnHideBt);
}
void PlayersSubWindow::OnHideBt(){


//test->popup(QPoint(10,10));
Bt_Hide ->setGeometry(10,10,150,50);
}
void PlayersSubWindow::handleRefreshX(std::vector<PlayerData> pd, GameData gd){
   // menu->addAction(QString::fromStdString(std::to_string(pd.size())));
   /* menu->addAction(QString::fromStdString(pd[0].name));
    menu->addAction(QString::fromStdString(pd[1].name));
    menu->addAction(QString::fromStdString(pd[2].name));
    menu->addAction(QString::fromStdString(pd[3].name));//*/

    menu->popup(QPoint(10,10));
}

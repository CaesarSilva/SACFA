#include "playerssubwindow.h"
//int LReadCb(std::string line, void* tthis){
int BtClickCallBack(void* tthis, PlayerData pdata){
    ((PlayersSubWindow*)tthis)->handlePlayerLineBt(pdata);
    return 1;
}
PlayersSubWindow::PlayersSubWindow(QWidget *parent):QMdiSubWindow(parent)
{
    PlayersScroll = new QScrollArea(this);
    PlayersScroll->setGeometry(3,55,280,320);
    PlayersScroll->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    PlayersScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    PlayersScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    PlayersScroll->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 30px; }");
    menu = new QMenu("title",this);
    Bt_Hide = new QPushButton("hide",this);
    Bt_Hide ->setGeometry(10,15,100,30);
    connect(Bt_Hide,&QPushButton::pressed,this,&PlayersSubWindow::OnHideBt);
    Bt_refresh = new QPushButton("Refresh",this);
    Bt_refresh ->setGeometry(150,15,100,30);
    connect(Bt_refresh,&QPushButton::pressed,this,&PlayersSubWindow::OnRefreshBt);
}
void PlayersSubWindow::OnHideBt(){

this->hide();
//test->popup(QPoint(10,10));
//Bt_Hide ->setGeometry(10,10,150,50);
}
void PlayersSubWindow::handleRefreshX(std::vector<PlayerData> pd, GameData gd){
  //TODO: DELETE playerLines before creating new ones
    int sizecount = 60;
    PlayersWidget = new QWidget(PlayersScroll);
    PlayersWidget->setGeometry(0,0,300,500);
    for(int i=0;i<32;i++){
        if(pd[i].team != 255){
            playerLine * plln= new playerLine(PlayersWidget,pd[i]);
            //PlayersScroll->setWidget(plln);
            plln->clickCallBack = &BtClickCallBack;
            plln->CbThiss = (void*)this;
            //playerLine * plln= new playerLine(this,pd[i].name,pd[i].team,pd[i].kills,pd[i].deaths,pd[i].ip,pd[i].id);
            plln->setGeometry(5,30+30*i,300,30);
            PlLnVec.push_back(plln);
            sizecount += 30;
        }




  }
    PlayersScroll->setWidget(PlayersWidget);
//PlayersScroll->verticalScrollBar()->setMaximum(sizecount);
    // menu->addAction(QString::fromStdString(std::to_string(pd.size())));
   /* menu->addAction(QString::fromStdString(pd[0].name));
    menu->addAction(QString::fromStdString(pd[1].name));
    menu->addAction(QString::fromStdString(pd[2].name));
    menu->addAction(QString::fromStdString(pd[3].name));//*/

    //menu->popup(QPoint(10,10));
}
void PlayersSubWindow::handlePlayerLineBt(PlayerData pdata){
    menu->clear();
   // menu->setToolTipsVisible(true);//it doesnt seem to work
    //menu->setTitle(QString::fromStdString(pdata.name));
    //QAction * Ac = new QAction()
    //menu->addAction("Kill")->;
    menu->addSection(QString::fromStdString(pdata.name));
    PlayerData pdatamod = pdata;
    pdatamod.command = "kick";
    menu->addAction("Kick")->setData(QVariant::fromValue(pdatamod));
    pdatamod.command = "kill";
    menu->addAction("Kill")->setData(QVariant::fromValue(pdatamod));
    menu->popup(QPoint(10,10));
    pdatamod.command = "admip";
    menu->addAction("Set as admin")->setData(QVariant::fromValue(pdatamod));
    pdatamod.command = "unadm";
    menu->addAction("Remove admin")->setData(QVariant::fromValue(pdatamod));
    pdatamod.command = "setteam0";
    menu->addAction("setteam0")->setData(QVariant::fromValue(pdatamod));
    pdatamod.command = "setteam1";
    menu->addAction("setteam1")->setData(QVariant::fromValue(pdatamod));
    pdatamod.command = "setteam2";
    menu->addAction("setteam2")->setData(QVariant::fromValue(pdatamod));
    pdatamod.command = "setteam3";
    menu->addAction("setteam3")->setData(QVariant::fromValue(pdatamod));
    pdatamod.command = "setteam4";
    menu->addAction("setteam4")->setData(QVariant::fromValue(pdatamod));

    connect(menu, &QMenu::triggered, this, &PlayersSubWindow::HandleAction);


}
void PlayersSubWindow::OnRefreshBt(){


     Bt_refresh ->setGeometry(170,15,100,30);
     PlLnVec.clear();
     delete PlayersWidget;//TODO: delete only the children
     CommandTextCallBack(CbThiss, "REFRESHX\n");
}
void PlayersSubWindow::HandleAction(QAction * qA){
PlayerData pdata = qA->data().value<PlayerData>();
if(pdata.command == "kick"){
    CommandTextCallBack(CbThiss,"/kick "+std::to_string(pdata.id));

}else if(pdata.command == "kill"){
    CommandTextCallBack(CbThiss,"/kill "+std::to_string(pdata.id));

}
else if(pdata.command == "admip"){
    CommandTextCallBack(CbThiss,"/kill "+pdata.ip);

}else if(pdata.command == "unadm"){
    CommandTextCallBack(CbThiss,"/unadm "+pdata.ip);

}else if(pdata.command == "setteam0"){
    CommandTextCallBack(CbThiss,"/setteam0 "+std::to_string(pdata.id));

}else if(pdata.command == "setteam1"){
    CommandTextCallBack(CbThiss,"/setteam1 "+std::to_string(pdata.id));

}else if(pdata.command == "setteam2"){
    CommandTextCallBack(CbThiss,"/setteam2 "+std::to_string(pdata.id));

}else if(pdata.command == "setteam3"){
    CommandTextCallBack(CbThiss,"/setteam3 "+std::to_string(pdata.id));

}else if(pdata.command == "setteam4"){
    CommandTextCallBack(CbThiss,"/setteam4 "+std::to_string(pdata.id));

}



this->hide();
}

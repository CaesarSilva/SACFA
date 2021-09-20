#include "playerline.h"

//playerLine::playerLine(QWidget *parent, std::string Name, unsigned char Team, unsigned short kills, unsigned short deaths, std::string ip, unsigned char id) : QWidget(parent)
playerLine::playerLine(QWidget *parent, PlayerData pdata) : QWidget(parent)
{
    QLabel * Lbl_Name = new QLabel(QString::fromStdString(pdata.name),this);
    QFont font = Lbl_Name->font();
    font.setPointSize(6);
    Lbl_Name->setFont(font);

    QLabel * Lbl_KillDeath = new QLabel(QString("Kills:")+QString::fromStdString(std::to_string(pdata.kills)) +
                                        QString("\nDeaths:")+QString::fromStdString(std::to_string(pdata.deaths))+
                                         QString("\nCaps:") + QString::fromStdString(std::to_string(pdata.caps)),this);
    QLabel * Lbl_IpHWID = new QLabel(QString("IP:")+QString::fromStdString(pdata.ip) +
                                     QString("\nHWID:") +QString::fromStdString(pdata.hwid)+
                                      QString("\nID:")  +QString::fromStdString(std::to_string(pdata.id))+
                                    QString(" Ping:") + QString::fromStdString(std::to_string(pdata.ping)),this);
    font.setPointSize(6);
    Lbl_KillDeath->setFont(font);
     font.setPointSize(5);
    Lbl_IpHWID->setFont(font);
    //Lbl_Name->setStyleSheet("QLabel { background-color : red; color : blue; }");
    switch(pdata.team){
     case 0:
    Lbl_Name->setStyleSheet("QLabel { color : black; }");
     Lbl_KillDeath->setStyleSheet("QLabel { color : black; }");
        break;
    case 1:
        Lbl_Name->setStyleSheet("QLabel { color : red; }");
         Lbl_KillDeath->setStyleSheet("QLabel { color : red; }");
        break;
    case 2:
        Lbl_Name->setStyleSheet("QLabel { color : blue; }");
         Lbl_KillDeath->setStyleSheet("QLabel { color : blue; }");
        break;
    case 3:
        Lbl_Name->setStyleSheet("QLabel { color : yellow; }");
        Lbl_KillDeath->setStyleSheet("QLabel { color : yellow; }");
        break;
    case 4:
        Lbl_Name->setStyleSheet("QLabel { color : green; }");
        Lbl_KillDeath->setStyleSheet("QLabel { color : green; }");
        break;
    case 5:
        Lbl_Name->setStyleSheet("QLabel { color : purple; }");
        Lbl_KillDeath->setStyleSheet("QLabel { color : green; }");
        break;
    default:
        Lbl_Name->setStyleSheet("QLabel { background-color : black; color : white; }");//this is not supposed to happen
         Lbl_KillDeath->setStyleSheet("QLabel { background-color : black; color : white; }");//this is not supposed to happen

        break;

    }

    Lbl_Name->setGeometry(5,5,100,20);
    Lbl_KillDeath->setGeometry(105,5,35,20);
    Lbl_IpHWID->setGeometry(170,5,60,20);
    bt1 = new QPushButton("...",this);
    bt1->setGeometry(140,5, 25 ,15);
    connect(bt1,&QPushButton::pressed,this,[=](){clickCallBack(CbThiss,pdata);});
    //Id=pdata;
   // Ip=id;
}

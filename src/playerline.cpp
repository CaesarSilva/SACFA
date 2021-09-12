#include "playerline.h"

//playerLine::playerLine(QWidget *parent, std::string Name, unsigned char Team, unsigned short kills, unsigned short deaths, std::string ip, unsigned char id) : QWidget(parent)
playerLine::playerLine(QWidget *parent, PlayerData pdata) : QWidget(parent)
{
    QLabel * Lbl_Name = new QLabel(QString::fromStdString(pdata.name+std::to_string(pdata.team)),this);
    QFont font = Lbl_Name->font();
    font.setPointSize(7);
    Lbl_Name->setFont(font);
    //Lbl_Name->setStyleSheet("QLabel { background-color : red; color : blue; }");
    switch(pdata.team){
     case 0:
    Lbl_Name->setStyleSheet("QLabel { color : black; }");
        break;
    case 1:
        Lbl_Name->setStyleSheet("QLabel { color : red; }");
        break;
    case 2:
        Lbl_Name->setStyleSheet("QLabel { color : blue; }");
        break;
    case 3:
        Lbl_Name->setStyleSheet("QLabel { color : yellow; }");
        break;
    case 4:
        Lbl_Name->setStyleSheet("QLabel { color : green; }");
        break;
    case 5:
        Lbl_Name->setStyleSheet("QLabel { color : purple; }");
        break;
    default:
        Lbl_Name->setStyleSheet("QLabel { background-color : black; color : white; }");//this is not supposed to happen
        break;

    }

    Lbl_Name->setGeometry(5,5,100,20);
    bt1 = new QPushButton("...",this);
    bt1->setGeometry(120,5, 25 ,15);
    connect(bt1,&QPushButton::pressed,this,[=](){clickCallBack(CbThiss,pdata);});
    //Id=pdata;
   // Ip=id;
}

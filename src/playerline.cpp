#include "playerline.h"

playerLine::playerLine(QWidget *parent, std::string Name, unsigned char Team, unsigned short kills, unsigned short deaths, std::string ip, unsigned char id) : QWidget(parent)
{
    QLabel * Lbl_Name = new QLabel(QString::fromStdString(Name),this);
    Lbl_Name->setGeometry(5,5,100,20);
}

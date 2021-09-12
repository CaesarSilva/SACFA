#ifndef PLAYERLINE_H
#define PLAYERLINE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "shared.h"
class playerLine : public QWidget
{
    Q_OBJECT
public:
    //explicit playerLine(QWidget *parent, std::string Name, unsigned char Team, unsigned short kills, unsigned short deaths, std::string ip, unsigned char id);
    explicit playerLine(QWidget *parent, PlayerData pdata);
    QPushButton * bt1;
    std::string name;
    std::string Ip;
    unsigned char Id;
    int (*clickCallBack)(void* tthis, PlayerData pdata);
    void * CbThiss;
signals:

};

#endif // PLAYERLINE_H

#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QtNetwork/QAbstractSocket>//idk if that will be useful
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QFile>//for logging
#include <QTextStream>
#include <QDataStream>
#include <QStandardPaths>
#include <sstream>
#include <iostream>
#include <vector>
#include "shared.h"

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
//#include <cmath>
class ServerConnection : public QObject
{
    Q_OBJECT
public:
    int Connect(std::string SvHost, int vPort, std::string SvPass);
    explicit ServerConnection(QObject *parent = nullptr);
    int count = 0;
    int (*LineReadCallBack)(std::string line, void* tthis);
    int (*RefreshxCallBack)( std::vector<PlayerData> plvector, GameData gd , void* tthis);
    void * CbThiss;
    void SendText(std::string text);

private:
    QByteArray * Refr;
    bool stillreadingref = false;
    QTcpSocket * Socket;
    void rready();
    //QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/log.txt");
    //QTextStream stream(&file);
    QFile *file;
    QTextStream *stream ;
    void parseRefreshX();
signals:

};

#endif // SERVERCONNECTION_H

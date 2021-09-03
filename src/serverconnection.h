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
//#include <cmath>
class ServerConnection : public QObject
{
    Q_OBJECT
public:
    int Connect(std::string SvHost, int vPort, std::string SvPass);
    explicit ServerConnection(QObject *parent = nullptr);
    int count = 0;
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

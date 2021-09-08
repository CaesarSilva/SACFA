#ifndef PLAYERLINE_H
#define PLAYERLINE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
class playerLine : public QWidget
{
    Q_OBJECT
public:
    explicit playerLine(QWidget *parent, std::string Name, unsigned char Team, unsigned short kills, unsigned short deaths, std::string ip, unsigned char id);

signals:

};

#endif // PLAYERLINE_H

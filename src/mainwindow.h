#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include "servertabs.h"
#include "inih/INIReader.h"

/*QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
-*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void LoadSettings();
    void LoadTabs();
    void SaveTabs();
public:
    int sY,sX;
    int asY, asX;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
/*typedef*/ int (*EvtCallBackP)(std::string ev);
private:
   // Ui::MainWindow *ui;
    void handleButton();
    void handleDeleteButton();

      QPushButton *m_button;
      QPushButton *m_button2;
      ServerTabs * SvTabs;
signals:
      void KbShow();
      void KbHide();
};
#endif // MAINWINDOW_H

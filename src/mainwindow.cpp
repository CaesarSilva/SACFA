#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

      /*QRect rect = QApplication::primaryScreen()->geometry();
      sY =  QApplication::primaryScreen()->geometry().size().height();
      sX =  QApplication::primaryScreen()->geometry().size().width();
      asX = QApplication::primaryScreen()->availableSize().width();
      asY = QApplication::primaryScreen()->availableSize().height();*/

    //ui->setupUi(this);
    // Create the button, make "this" the parent
      m_button = new QPushButton("My Button", this);
      // set size and location of the button
      m_button->setGeometry(QRect(QPoint(10, 10), QSize(40, 30)));
      /*QPushButton * */m_button2 = new QPushButton("Delete all tabs", this);
      // set size and location of the button
      m_button2->setGeometry(QRect(QPoint(3, 40), QSize(80, 50)));
      // Connect button signal to appropriate slot
      connect(m_button, &QPushButton::clicked, this, &MainWindow::handleButton);
      connect(m_button2, &QPushButton::pressed, this, &MainWindow::handleDeleteButton);
      //svtabs
      SvTabs = new ServerTabs(this);
      SvTabs->setGeometry(10,100,330,600);
      connect(SvTabs,&ServerTabs::KbHide,this, [=](){EvtCallBackP("khide");} );
      connect(SvTabs,&ServerTabs::KbShow,this, [=](){EvtCallBackP("kshow");} );
      connect(SvTabs,&ServerTabs::SvTabs,this, &MainWindow::SaveTabs);

    LoadTabs();
}
void MainWindow::LoadTabs(){
//INIReader reader(QString::toStdString(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/Tabs.ini"));
    QString  qfilepath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/Tabs.ini";

    //std::string filepath = (QString::toStdString(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/Tabs.ini"));
    //QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    INIReader reader(qfilepath.toStdString());
    //INIReader reader("/Tabs.ini");
    if (reader.ParseError() != 0) {
    }else{
    int i;
    for(i = 0; i<reader.GetInteger("info","NumTabs",0);i++){
      SvTabs->CreateTab(reader.Get(std::to_string(i),"Host",""),
      reader.Get(std::to_string(i),"Port","")            ,
      reader.Get(std::to_string(i),"Password",""));
    }
    }
}


void MainWindow::SaveTabs(){
QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/Tabs.ini");
//SvTabs->CreateTab();
if(file.open(QIODevice::WriteOnly| QIODevice::Text)){
    QTextStream stream(&file);
    /**stream << "[info]\nNumTabs=3\n";
    stream << "[0]\nHost=HardcodedHost\nPort=23073\nPassword=Hardcodedpass\n";
    stream << "[1]\nHost=HardcodedHost2\nPort=23072\nPassword=Hardcodedpass2\n";
    stream << "[2]\nHost=HardcodedHost3\nPort=23071\nPassword=Hardcodedpass3\n";
    file.close();*/
    int i = 0;
    foreach(auto n, SvTabs->TabList){
        stream << "["<<i<<"]\n" << "Host="<< n->TE_host->displayText()<<"\n";
        stream << "Port="<< n->TE_port->displayText()<<"\n";
        stream << "Password="<< n->TE_pass->displayText()<<"\n";
        i++;
    }
    stream << "[info]\nNumTabs="<<i;
    stream << "\nscreenX="<<sX;
    stream << "\nscreenY="<<sY;
    stream << "\navailableX="<<asX;
    stream << "\navailableY="<<asY;
    stream << "\nqtversion=" << QT_VERSION_STR ;

    file.close();
}
}
void MainWindow::handleDeleteButton()
{
    /*foreach(auto n, SvTabs->TabList){
        delete n;
    }*/
    for(int i = SvTabs->TabList.length()-1 ; i>=0;i--){
    auto *n = SvTabs->TabList[i];
    delete n;
    SvTabs->TabList.removeAt(i);
    }
}
void MainWindow::handleButton()
{
  SvTabs->CreateTab();

}
MainWindow::~MainWindow()
{
    //delete ui;
}


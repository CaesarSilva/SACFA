#include "servertab.h"

ServerTab::ServerTab(QWidget *parent,std::string host , std::string port, std::string password) : QWidget(parent)
{
   // m_button = new QPushButton("My Button", this);
    // set size and location of the button
   // m_button->setGeometry(QRect(QPoint(10, 70), QSize(50, 50)));

    //TE_host = new QPlainTextEdit(this);
    TE_host = new MyLineEdit(this);
    TE_port = new MyLineEdit(this);
    TE_pass = new MyLineEdit(this);
    Bt_connect = new QPushButton(this);
    TE_host->setGeometry(QRect(QPoint(10, 20), QSize(80, 40)));
    TE_port->setGeometry(QRect(QPoint(100, 20), QSize(50, 40)));
    TE_pass->setGeometry(QRect(QPoint(160, 20), QSize(60, 40)));
    Bt_connect->setGeometry(QRect(QPoint(240, 20), QSize(40, 50)));
    TE_output = new QTextEdit(this);
    TE_output->setGeometry(QRect(QPoint(10, 70), QSize(270, 300)));
    TE_output->setText("a");
    //ISSUE: QPushButton::released event doesn't work, only pressed
    connect(Bt_connect, &QPushButton::pressed, this, &ServerTab::handleConnectButton);
    connect(TE_host, &MyLineEdit::FocusIN, this, [=](){TE_output->append("HFIN"); emit KbShow(); });
   connect(TE_host, &MyLineEdit::FocusOUT, this, [=](){TE_output->append("HFOUT"); emit KbHide();});

   connect(TE_port, &MyLineEdit::FocusIN, this, [=](){TE_output->append("PoFIN"); emit KbShow(); });
  connect(TE_port, &MyLineEdit::FocusOUT, this, [=](){TE_output->append("PoFOUT"); emit KbHide();});

  connect(TE_pass, &MyLineEdit::FocusIN, this, [=](){TE_output->append("PaFIN"); emit KbShow(); });
 connect(TE_pass, &MyLineEdit::FocusOUT, this, [=](){TE_output->append("PaFOUT"); emit KbHide();});


 SvConnection = new ServerConnection(this);

    TE_host->insert(QString::fromStdString(host));
    TE_port->insert(QString::fromStdString(port));
    TE_pass->insert(QString::fromStdString(password));


    //connect(Bt_connect, &QPushButton::pressed, this , [=](){TE_output->append("WTF"); handleConnectButton();});


}
/*int ServerTab::CallCallBack(std::string ev, std::string data){
    EvtCallBackP("ev",parent());
//It crashed here because return is missing, this chain of callbacks was replaced by a chain of events
}
void ServerTab::SetCallBack(int (*CallBF)(std::string, void*), void * thiss){
    CallBackSet = true;
    CallBF("SetCallBack", thiss);
    EvtCallBackP = CallBF;
    CbThiss = &thiss;
    //EvtCallBackP = CallBF;

}*/
void ServerTab::handleConnectButton()
{
    SvConnection->Connect(TE_host->displayText().toStdString(),std::stoi(TE_port->displayText().toStdString()), TE_pass->displayText().toStdString());
    //emit KbShow();
    //TE_output->setText("b");
    TE_output->append("Go Button released");
    TE_output->append(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    //Bt_connect->resize(100,100);
    //QInputMethod *keyboard = QGuiApplication::inputMethod();
    //keyboard->show();
    emit SvTab();
}

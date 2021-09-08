#include "servertab.h"
int LReadCb(std::string line, void* tthis){
    //((ServerTabs*)thiss)->EvtCallBack(ev);
    ((ServerTab*)tthis)->handleNewLine(line);
return 1;
}
int PUpdCb( std::vector<PlayerData> plvector, GameData gd , void* tthis){
    ((ServerTab*)tthis)->handleRefreshX(plvector,gd);
     //((ServerTab*)tthis)->handleNewLine("REFRESH CALLBACK");
    return 1; //without return it causes "illegal instruction" on the line above
}
ServerTab::ServerTab(QWidget *parent,std::string host , std::string port, std::string password) : QWidget(parent)
{
   // m_button = new QPushButton("My Button", this);
    // set size and location of the button
   // m_button->setGeometry(QRect(QPoint(10, 70), QSize(50, 50)));

    //TE_host = new QPlainTextEdit(this);
    TE_host = new MyLineEdit(this);
    TE_port = new MyLineEdit(this);
    TE_pass = new MyLineEdit(this);
    TE_input = new MyLineEdit(this);
    Bt_connect = new QPushButton(this);
    bt_sendtext = new QPushButton(this);
    bt_plwin = new QPushButton("players",this);
    TE_host->setGeometry(QRect(QPoint(10, 20), QSize(80, 40)));
    TE_port->setGeometry(QRect(QPoint(100, 20), QSize(50, 40)));
    TE_pass->setGeometry(QRect(QPoint(160, 20), QSize(60, 40)));
    TE_input->setGeometry(QRect(QPoint(10, 355), QSize(200, 40)));
    Bt_connect->setGeometry(QRect(QPoint(240, 20), QSize(40, 50)));
    bt_sendtext->setGeometry(220,355,25,40);
    bt_plwin->setGeometry(QRect(QPoint(10, 385), QSize(40, 50)));
    TE_output = new QTextEdit(this);
    TE_output->setGeometry(QRect(QPoint(10, 70), QSize(270, 250)));
    TE_output->setText("a");
    //TE_output->setMaximumBlockCount(55);
    //ISSUE: QPushButton::released event doesn't work, only pressed
    //handlePlnwinBT()
    connect(Bt_connect, &QPushButton::pressed, this, &ServerTab::handleConnectButton);
    connect(bt_plwin, &QPushButton::pressed, this, &ServerTab::handlePlnwinBT);
    connect(bt_sendtext, &QPushButton::pressed, this, &ServerTab::handleSendTextBT);
    connect(TE_host, &MyLineEdit::FocusIN, this, [=](){TE_output->append("HFIN"); emit KbShow(); });
   connect(TE_host, &MyLineEdit::FocusOUT, this, [=](){TE_output->append("HFOUT"); emit KbHide();});

   connect(TE_port, &MyLineEdit::FocusIN, this, [=](){TE_output->append("PoFIN"); emit KbShow(); });
  connect(TE_port, &MyLineEdit::FocusOUT, this, [=](){TE_output->append("PoFOUT"); emit KbHide();});

  connect(TE_pass, &MyLineEdit::FocusIN, this, [=](){TE_output->append("PaFIN"); emit KbShow(); });
 connect(TE_pass, &MyLineEdit::FocusOUT, this, [=](){TE_output->append("PaFOUT"); emit KbHide();});

 connect(TE_input, &MyLineEdit::FocusIN, this, [=](){TE_output->append("PaFIN"); emit KbShow(); });
connect(TE_input, &MyLineEdit::FocusOUT, this, [=](){TE_output->append("PaFOUT"); emit KbHide();});

 SvConnection = new ServerConnection(this);
 SvConnection->LineReadCallBack=&LReadCb;
 SvConnection->RefreshxCallBack=&PUpdCb;
 SvConnection->CbThiss = (void*)this;
    TE_host->insert(QString::fromStdString(host));
    TE_port->insert(QString::fromStdString(port));
    TE_pass->insert(QString::fromStdString(password));


    //connect(Bt_connect, &QPushButton::pressed, this , [=](){TE_output->append("WTF"); handleConnectButton();});


    PSWin = new PlayersSubWindow(this);
    PSWin->setGeometry(0,20,300,400);
    PSWin->hide();

    QFont font = TE_output->font();
    font.setPointSize(7);
    TE_output->setFont(font);
    TE_input->setFont(font);
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
void ServerTab::handleRefreshX(std::vector<PlayerData> pd, GameData gd){
PSWin->handleRefreshX(pd,gd);
}
void ServerTab::handleSendTextBT(){
SvConnection->SendText(TE_input->text().toStdString());
TE_input->setText("/say");

}
void ServerTab::handleNewLine(std::string line){
    //TE_output->append(QString::fromStdString(line));
    int maxchange = TE_output->verticalScrollBar()->maximum();
    TE_output->append(line.substr(0,line.length()-1).c_str());//the purpose of the substr is to remove the \r at the end of the line
    maxchange = TE_output->verticalScrollBar()->maximum()-maxchange;
    TE_output->verticalScrollBar()->setValue(TE_output->verticalScrollBar()->value()+maxchange);
}
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
void ServerTab::handlePlnwinBT(){
    TE_output->setText("handleplnwinbtpressed");
    //QMdiSubWindow * test = new QMdiSubWindow(this);

    PSWin->show();

}

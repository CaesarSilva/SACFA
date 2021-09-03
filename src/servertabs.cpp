#include "servertabs.h"
/*int staticcallback(std::string ev, void *thiss){
    ((ServerTabs*)thiss)->EvtCallBack(ev);
return 9;
}*/


ServerTabs::ServerTabs(QWidget *parent)
    : QTabWidget(parent)
{
//ServerTab * tabtest1 = new ServerTab(this);
//tabtest1->SetCallBack(&ServerTabs::EvtCallBack );
//tabtest1->SetCallBack(&staticcallback,this );
//tabtest1->SetCallBack([&](std::string ev, void *thiss)-> int {return EvtCallBack(ev);},this );
//tabtest1->SetCallBack([](std::string ev, void *thiss)-> int {return 2;},this );
//tabtest1->SetCallBack(&ServerTabs::EvtCallBack,this );

//connect(TE_host, &MyLineEdit::FocusIN, this, [=](){TE_output->append("HFIN"); emit KbShow(); });
//connect(tabtest1,&ServerTab::KbHide,this, [=](){emit KbHide();} );
//connect(tabtest1,&ServerTab::KbShow,this, [=](){emit KbShow();} );
//ServerTab * tabtest2 = new ServerTab(this);
//this->addTab(tabtest1,"tab1");
//this->addTab(tabtest2,"tab2");

}
void ServerTabs::CreateTab(std::string host, std::string port, std::string password){
    ServerTab * tab = new ServerTab(this,host,port,password);
    this->addTab(tab,"tabx");
    connect(tab,&ServerTab::KbHide,this, [=](){emit KbHide();} );
    connect(tab,&ServerTab::KbShow,this, [=](){emit KbShow();} );
    connect(tab,&ServerTab::SvTab,this, [=](){emit SvTabs();} );
    TabList << tab;


}
/*int ServerTabs::EvtCallBack(std::string ev){
    ServerTab * tabtest1 = new ServerTab(this);
   // ServerTab * tabtest2 = new ServerTab(this);
    //this->addTab(tabtest1,QString::fromStdString( ev));
    this->addTab(tabtest1,"tab2");
    return 0;
}*/

#include "serverconnection.h"

ServerConnection::ServerConnection(QObject *parent) : QObject(parent)
{
    //CbThiss = &parent;
    Socket = new QTcpSocket(this);
    connect(Socket,&QTcpSocket::readyRead,this,&ServerConnection::rready);
    file = new QFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/log.txt");
    file->open(QIODevice::WriteOnly| QIODevice::Text);
        stream = new QTextStream(file);

}
int ServerConnection::Connect(std::string SvHost, int vPort, std::string SvPass){

    //Socket->connectToHost(QHostAddress(QString::fromStdString(SvHost)), vPort);
    //Socket->connectToHost("192.168.1.198", 23074);
    Socket->connectToHost(QString::fromStdString(SvHost), vPort);

    //QString str = QString::fromStdString(SvPass+"\n");
    std::string pswd = SvPass+"\n";

                Socket->write(pswd.c_str());
    std::string command = "/maxplayers\n/clientlist\nREFRESHX\n";
                //Socket->write(command.c_str());




    return 1;

}
void ServerConnection::rready(){
    unsigned int count = 0;
    bool refreshfound=false;
    QByteArray block = Socket->readAll();
    std::string stdstrin = block.toStdString();
    std::istringstream f(stdstrin);
    QFile file2(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/wtf.txt");

    file2.open(QIODevice::WriteOnly| QIODevice::Append |QIODevice::Text);

    QTextStream stream2(&file2);
    stream2 << stdstrin.substr(0,200).c_str() <<"|||" << block.length() << "<...>";
    //file2.close();
    std::string s;
    if(stillreadingref){
        Refr->append(block); //TODO: check number of bytes before doing that
        stillreadingref = false;
        parseRefreshX();
    }else
    if(block.startsWith("REFRES") || block.startsWith("\rREFRES") ){
    stream2<< "PANIC!!";
    if(block.length()<2002){
        stillreadingref = true;
        Refr = new QByteArray(block);
    }else if(block.length()==2002){
       //send it to the function
    }

    }else
        while (getline(f, s, '\n') && !refreshfound) {
            stream2 << "\n<count>" << count << s.c_str() ;
            count += s.length()+1;//+1 includes the \n in the counting
            stream2 << "</count>" << count << "  ";
        //s.substr(0,12) == std::string("/clientlists")
            //stream2 << s.substr(0,11).c_str() << "<|||>";
            if(s.substr(0,11) == std::string("/clientlist")){
               // stream2 << "<<clientlist>>";
                std::string command;
                command = std::string("")+"["+(const char)170+"] Hardcoded User: SACFA\n" ;
                Socket->write(command.c_str());
                std::cout << "wtf man" << std::endl;
                //assert("hurra hurra");
            }else if(s.substr(0,11) == std::string("/tlientlist")){
             //Socket->write(block.toStdString().c_str());
                std::string command = "REFRESHX\n";
                //command = "std::string("")+"["+(const char)170+"] Hardcoded User: SACFA\n"" ;
                Socket->write(command.c_str());

            }else if(s.substr(0,8) == std::string("REFRESHX")){
                refreshfound = true;
               }
            else {
                  LineReadCallBack(s,CbThiss); //&CbThiss caused segmentation fault
                           }



        }
    if(refreshfound){//one alternative to this is to use the string stream
      QByteArray block2 = block.right(block.length()-count+10);
      stream2 << "\n REFRESH found in the way. \n Length" << block2.length() << "\n First 10 char:" << block2.toStdString().substr(0,12).c_str();
      stillreadingref = true;
      Refr = new QByteArray(block2);
    }



file2.close();
        //
/*
    if(count<10){
        stream->setString(new QString(block.toStdString().c_str()));
        stream->flush();
        count++;
    }else file->close();*/

}
void ServerConnection::SendText(std::string text){
    Socket->write((text+"\n").c_str());

}
void ServerConnection::parseRefreshX(){
//https://wiki.soldat.pl/index.php/Refreshx
QByteArray  Qar = Refr->left(2002);
//QByteArray * Qar = new QByteArray(Refr->left(Refr->size()).data());
int removeitlater =  Refr->left(2002).length();
QDataStream Rstream(&Qar, QIODevice::ReadOnly);
QFile file2(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/refreshx.txt");
file2.open(QIODevice::WriteOnly| QIODevice::Append |QIODevice::Text);
QTextStream stream2(&file2);
char refreshxrn[10];
Rstream.readRawData(refreshxrn,10);

//char  playern[24] ;
//stream2 <<Rstream.readRawData(playern,24);
stream2 << "\n\n\n\n" <<Qar.length() << "  " << Refr->length() << "  " << removeitlater <<"<REFRESHX>" << refreshxrn;
std::vector<PlayerData> pvec;
GameData gdata;
for(int i = 0; i<32;i++){
    PlayerData Pstruct;

    Rstream.skipRawData(1);
    char  playern[24] ;
    stream2 <<Rstream.readRawData(playern,24);
    Pstruct.name= playern;
    stream2 << "\n<PLAYER" << i << ">" << playern;
    pvec.push_back(Pstruct);
}
for(int i = 0; i<32;i++){//HWID
    char  hwids[12] ;
    stream2 <<Rstream.readRawData(hwids,12);
    stream2 << "\n<HWID" << i << ">" << hwids;
}
for(int i = 0; i<32;i++){//TEAMS
    unsigned char  teams ;
    //stream2 <<Rstream.readRawData(teams,1);
    Rstream >> teams;
    stream2 << "\n<TEAM" << i << ">" << (unsigned int)(teams);
}
for(int i = 0; i<32;i++){//KILLS
    unsigned char kills[2] ;
    //stream2 <<Rstream.readRawData(kills,2);
    Rstream >> kills[0] ;
    Rstream >> kills[1];
    stream2 << "\n<kills" << i << ">" << (unsigned int)(kills[1]*256+kills[0]) ;
}
for(int i = 0; i<32;i++){//CAPS
    unsigned char  caps ;
    //stream2 <<Rstream.readRawData(teams,1);
    Rstream >> caps;
    stream2 << "\n<CAPS" << i << ">" << (caps);
}
for(int i = 0; i<32;i++){//DEATHS
    unsigned char deaths[2] ;
    //stream2 <<Rstream.readRawData(kills,2);
    Rstream >> deaths[0] >> deaths[1];
    stream2 << "\n<deaths" << i << ">" << (unsigned int)(deaths[1]*256+ deaths[0]);
    //stream2 << "\n<deaths detailed>" << i << ">" << (unsigned int)deaths[1] << "  " << (unsigned int)deaths[0];
}
for(int i = 0; i<32;i++){//PINGS
    signed long pings ;
    //stream2 <<Rstream.readRawData(kills,2);
    //Rstream >> pings;
    //stream2 << "\n<ping" << i << ">" << pings;
    Rstream.skipRawData(4);
}
for(int i = 0; i<32;i++){//IDS
    unsigned char  ids ;
    //stream2 <<Rstream.readRawData(teams,1);
    Rstream >> ids;
    stream2 << "\n<ID" << i << ">" << (ids);
}
for(int i = 0; i<32;i++){//IDS
    unsigned char  ips[4] ;
    //stream2 <<Rstream.readRawData(teams,1);
    Rstream >> ips[0] >> ips[1] >> ips[2] >> ips[3];
    stream2 << "\n<IP" << i << ">" << (unsigned int)ips[0] << "." << (unsigned int)ips[1] << "." << (unsigned int)ips[2] << "." << (unsigned int)ips[3];
}
for(int i = 0; i<32;i++){//x pos
    Rstream.skipRawData(4);
}
for(int i = 0; i<32;i++){//y pos
    Rstream.skipRawData(4);
}
Rstream.skipRawData(4);
Rstream.skipRawData(4);
Rstream.skipRawData(4);
Rstream.skipRawData(4);//skipping flag position
for(int i = 0; i<4;i++){//IDS
    unsigned char  tsc[4] ;
    //stream2 <<Rstream.readRawData(teams,1);
    Rstream >> tsc[0] >> tsc[1];
    stream2 << "\n<team"<<i<<">"<< (unsigned short)(tsc[1]*256+tsc[0]);
}
Rstream.skipRawData(1);//skips map name length
char  mapn[16] ;
Rstream.readRawData(mapn,16);
stream2 << "\n Map:" << mapn;
unsigned long tlimit, tleft;
unsigned char times[4];
Rstream >> times[0] >> times[1] >> times[2] >> times[3];
tlimit = times[3]* 0xFFFFFF + times[2]*0xFFFF + times[1]*0xFF;
Rstream >> times[0] >> times[1] >> times[2] >> times[3];
tleft = times[3]* 0xFFFFFF + times[2]*0xFFFF + times[1]*0xFF;
stream2 << "\n Time:" << (int)(tleft/(60*60*60)) <<
          ":" << (int)((tleft%(60*60*60))/(60*60)) <<
          ":" << (int)(((tleft%(60*60*60))%(60*60))/60);
stream2 << "/" << (int)(tlimit/(60*60*60)) <<
          ":" << (int)((tlimit%(60*60*60))/(60*60)) <<
          ":" << (int)(((tlimit%(60*60*60))%(60*60))/60);

/*stream2 <<Rstream.readRawData(playern,24);
stream2 << "\n<PLAYER2>" << playern ;
stream2 <<Rstream.readRawData(playern,24);
stream2 << "\n<PLAYER3>" << playern ;
stream2 <<Rstream.readRawData(playern,24);
stream2 << "\n<PLAYER3>" << playern ;
stream2 <<Rstream.readRawData(playern,24);
stream2 << "\n<PLAYER3>" << playern ;
stream2 <<Rstream.readRawData(playern,24);
stream2 << "\n<PLAYER3>" << playern ;
stream2 <<Rstream.readRawData(playern,24);
stream2 << "\n<PLAYER3>" << playern ;
stream2 <<Rstream.readRawData(playern,24);
stream2 << "\n<PLAYER3>" << playern ;*/




file2.close();



RefreshxCallBack(pvec,gdata, CbThiss);
}

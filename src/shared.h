#ifndef SHARED_H
#define SHARED_H

struct GameData{
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

};

#endif // SHARED_H

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
    unsigned char caps;
    signed long ping;
    short kills;
    short deaths;
    unsigned char id;
    std::string ip;
    std::string hwid;
    std::string command;//remove if unnecessary

};
Q_DECLARE_METATYPE(PlayerData)

#endif // SHARED_H

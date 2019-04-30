#include <iostream>
#include <string>
#include <QtCore>

#include "client.h"

using namespace std;


class SendData : public QThread {
private:
    bool stop;
    bool write_is_safe = true;
    bool is_obj_selected = false;
    string html_data = "";
    Client client;

    void writeData();
    int str_find(string str, string s);
    string str_replaceAll(string data, string str, string rep);
    string str_findWithName_containsName(string data, string str);
    string str_findWithName_excludeName(string data, string str);
    float getRA(string data);
    float getDEC(string data);
    int sendToServer(string data);

public:
    SendData(/* args */);
    ~SendData();
    void setHTML_data(string data);
    void run();
};
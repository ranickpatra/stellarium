#include <iostream>
#include <string>
#include <QtCore>

using namespace std;


class SendData : public QThread {
private:
    bool stop;
    bool write_is_safe = true;
    bool is_obj_selected = false;
    string html_data = "";

    void writeData();
    int str_find(string str, string s);

public:
    SendData(/* args */);
    ~SendData();
    void setHTML_data(string data);
    void run();
};
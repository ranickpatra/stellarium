#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;


class SendData {
private:
    bool stop;
    void* dd(void *d);

public:
    SendData(/* args */);
    ~SendData();
    void setHTML_data(string data);
};
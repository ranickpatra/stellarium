#include "SendData.hpp"

#include <boost/algorithm/string.hpp>

SendData::SendData(/* args */)
{
    stop = false;   // check if the application is running or not
    // to start the thread
    //this->start();


}

SendData::~SendData()
{
    stop = true;
}


void SendData::setHTML_data(string data) {

    // check if writable
    if (write_is_safe) {
        this-> html_data = data;    // write data
        is_obj_selected = true;       // user select an object
    }

}

void SendData::run() {
    unsigned int loop_counter = 0;
    while(!stop) {
        if (is_obj_selected)
        {
            writeData();
        }
        loop_counter++;
        write_is_safe = true;
        is_obj_selected = false;
        msleep(50);
    }
}


void SendData::writeData() {

    static int i = 0;
    i++;
    write_is_safe = false;

    


    
}

// to find position in a string
int SendData::str_find(string str, string s) {
    int length = str.length();
    int pos = str.find(s);
    return pos < length ? pos : -1;
}



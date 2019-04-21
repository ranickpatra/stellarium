#include "SendData.hpp"

#include <boost/algorithm/string.hpp> 

SendData::SendData(/* args */)
{
    stop = false;
    pthread_t t1;
    pthread_create(&t1, NULL, dd, (void *) 0);

}

SendData::~SendData()
{
    stop = true;
}


void SendData::setHTML_data(string data) {

    vector<string> result;
    // boost::split(result, data, boost::is_any_of("<br >"));

    // for (int i = 0; i < result.size(); i++)
    // {
    //     cout << result[i] << " ";
    // }

    // int pos_start;
    // while ((pos_start = data.find("<br />")) != -1)
    // {
    //     cout << pos_start << endl;
    // }
    

}

void* SendData::dd(void *t) {
    // while (!stop)
    // {
    //     cout << "hhhh" << endl;
    // }
}




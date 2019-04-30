
class Client {
private:
    

public:

    Client();
    ~Client();
    short SocketCreate(void);
    int SocketConnect(int hSocket);
    int SocketSend(int hSocket, char* Rqst, short lenRqst);
    int SocketReceive(int hSocket, char* Rsp, short RvcSize);
    int sendData(char* data);

};
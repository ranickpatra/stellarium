#include <arpa/inet.h>

class Client {
private:
    int hSocket, read_size;
	struct sockaddr_in server;

public:

    Client();
    ~Client();
    short SocketCreate(void);
    int SocketConnect(int hSocket);
    int SocketSend(int hSocket, char* Rqst, short lenRqst);
    int SocketReceive(int hSocket, char* Rsp, short RvcSize);
    int create(void);
    int soc_close(void);
    int sendData(char* data);

};
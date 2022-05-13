#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::ostringstream;

int main(int argc, char* argv[]) {
    // Startup Winsock
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    int wsOk = WSAStartup(ver, &data);
    if (wsOk != 0) {
        cerr << "Can't start Winsock! Quitting..." << wsOk << endl;
        return -1;
    }

    // Create hint struct
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(55000);

    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);
    // Socket creation
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    // Write out message
    string s(argv[1]);
    int sendOk = sendto(sock, s.c_str(), s.size() + 1, 0, (sockaddr*)&hint, sizeof(hint));
    if (sendOk == SOCKET_ERROR) {
        cerr << "Msg send to server failed! Error:" << WSAGetLastError() << endl;
        return -1;
    }
    // close the socket
    closesocket(sock);

    // Cleanup Winsock
    WSACleanup();
}

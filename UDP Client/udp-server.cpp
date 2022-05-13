//#include <iostream>
//#include <WS2tcpip.h>
//
//#pragma comment (lib, "ws2_32.lib")
//
//using std::cout;
//using std::cin;
//using std::cerr;
//using std::endl;
//using std::string;
//using std::ostringstream;
//
//int main() {
//    // Startup Winsock
//    WSAData data;
//    WORD ver = MAKEWORD(2, 2);
//    int wsOk = WSAStartup(ver, &data);
//    if (wsOk != 0) {
//        cerr << "Can't start Winsock! Quitting..." << wsOk <<  endl;
//        return -1;
//    }
//
//    // Bind socket to ip and port
//    SOCKET insock = socket(AF_INET, SOCK_DGRAM, 0);
//    sockaddr_in serverHint;
//    serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
//    serverHint.sin_family = AF_INET;
//    serverHint.sin_port = htons(54000); // convert to little to big endian
//
//    if( bind(insock, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
//        cerr << "Can't bind socket! Quitting..." << endl;
//        return -1;
//    }
//
//    sockaddr_in clientHint;
//    int clientLen = sizeof(clientHint);
//    ZeroMemory(&clientHint, clientLen);
//
//    char buf[1024];
//        
//    // Enter a loop
//    while (true) {
//        // Wait for msg
//        ZeroMemory(buf, 1024);
//        int bytesIn = recvfrom(insock, buf, 1024, 0, (sockaddr*)&clientHint, &clientLen);
//        if (bytesIn == SOCKET_ERROR) {
//            cerr << "Not receiving message! Waiting..." << endl;
//            continue;
//        }
//        // Dispaly msg and client info
//        char clientIp[256];
//        ZeroMemory(clientIp, 256);
//
//        // the hint struct provides in bytes convert to string ip
//        inet_ntop(AF_INET, &clientHint.sin_addr, clientIp, 256); 
//
//        cout << "Message: [from " << clientIp  << "] " << buf << endl;
//    }
//    // close socket
//    closesocket(insock);
//    // shutdown winsock
//    WSACleanup();
//    return 0;
//}

// #include <iostream>
// #include <wS2tcpip.h>
// 
// #pragma comment(lib, "ws2_32.lib")
// 
// using std::cout;
// using std::cerr;
// using std::endl;
// using std::string;
// 
// int main() {
// 
//     // initialize winsock 
//     WSADATA wsData;
//     WORD ver = MAKEWORD(2, 2);
// 
//     int wsok = WSAStartup(ver, &wsData);
//     if (wsok != 0) {
//         cerr << "WSAStartup failed: cant initialize win sock" << endl;
//         return -1;
//     }
// 
//     // Create a socket
//     SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
//     if (listening == INVALID_SOCKET) {
//         cerr << "Can't Create socket " << endl;
//         return -2;
//     }
// 
//     // bind ip and port to the socket
//     sockaddr_in hint;
//     hint.sin_family = AF_INET;
//     hint.sin_port = htons(54000);
//     hint.sin_addr.S_un.S_addr = INADDR_ANY; // could also use inet_pton ...
// 
//     bind(listening, (sockaddr*)&hint, sizeof(hint));
// 
//     // tell the winsock that socket is for listening
//     listen(listening, SOMAXCONN);
// 
//     // wait for connection
//     sockaddr_in client;
//     int clientsize = sizeof(client);
// 
//     SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientsize);
//     if (clientSocket == INVALID_SOCKET) {
//         cerr << "Accept failed" << endl;
//         return -3;
//     }
// 
//     // send and receive data
//     char host[NI_MAXHOST]; // client's IP
//     char service[NI_MAXSERV]; // Service (i.e port) the client is connected on
// 
//     ZeroMemory(host, NI_MAXHOST); // equivalent of memset(host, 0, NI_MAXHOST);
//     ZeroMemory(service, NI_MAXSERV);
// 
//     if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
//         cout << host << " connected on port " << service << endl;
//     }
//     else {
//         inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
//         cout << host << " connected on port " << ntohs(client.sin_port) << endl;
//     }
// 
//     // close the listing socket
//     closesocket(listening);
// 
//     // while loop : accept and echo msg back to client
//     char buf[4096];
//     while (true)
//     {
//         ZeroMemory(buf, 4096);
//         // wait for client to send data
//         int bytesReceived = recv(clientSocket, buf, 4096, 0);
//         if (bytesReceived == SOCKET_ERROR) {
//             cerr << "recv failed" << endl;
//             return -4;
//         }
//         if (bytesReceived == 0) {
//             cout << "Client disconnected" << endl;
//             break;
//         }
// 
//         cout << string(buf, 0, bytesReceived) << endl;
//         // echo message back to client
//         send(clientSocket, buf, bytesReceived + 1, 0);
//     }
// 
//     // close the socket
//         closesocket(clientSocket);
//     // cleanup winsock
//         WSACleanup();
// 
//         return 0;
// }
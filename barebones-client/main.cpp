#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::string;

int main() {

	string ipAddress = "127.0.0.1"; // IP Addr of the server
	int port = 55000; // listening port # on the server

	// Initlialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		cerr << "WSAStartup failed Cannot start WinSock. Error code: " << wsResult << endl;
		return -1;
	}
    	
	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "socket creation failed. Error code: " << WSAGetLastError() << endl;
		return -2;
	}
	
	// fill in hint structures
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	
	// connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		cerr << "Cannot connect to server, Error Code: " << WSAGetLastError() << endl;
		WSACleanup();
		return -3;
	}

	// Do while loop to send and receive data
	char buf[4096];
	string userInput;
	do {
		// prompt user for text
		cout << "> ";
		getline(cin, userInput);

		if (userInput.size() > 0){ // make sure user typed something
		// send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
			// wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0) {
		             // echo response to console
					cout << "SERVER " << string(buf, 0, bytesReceived) << endl;
				}

			}
	   }
	} while (userInput.size() > 0);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}

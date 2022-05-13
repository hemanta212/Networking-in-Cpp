#include <iostream>
#include <string>

#include "TcpListener.h"

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;

void Listener_MessageReceived(CTcpListener* listener, int client, string msg);

int main() {
	CTcpListener server("127.0.0.1", 55000, Listener_MessageReceived) ;
	if (server.Init()) {
		server.Run();
	}
}

void Listener_MessageReceived(CTcpListener* listener, int client, string msg) {
	listener->Send(client, msg);
}

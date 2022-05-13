#include <iostream>
#include <string>
#include <algorithm>

#include "TcpListener.h"
#include "Qotd.h"

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;

void Listener_MessageReceived(CTcpListener* listener, int client, string msg);

// not good a global variable just for mini demo:
CQotd quotes("wisdom.txt");

int main() {
    CTcpListener server("0.0.0.0", 55000, Listener_MessageReceived) ;
    if (server.Init()) {
    	server.Run();
    }
}

void Listener_MessageReceived(CTcpListener* listener, int client, string msg) {
    msg.erase(remove_if(msg.begin(), msg.end(), isspace), msg.end());
    if (msg == "quote") {
        listener->Send(client, quotes.GetRandomQuote());
    }
}

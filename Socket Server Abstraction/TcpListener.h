#pragma once

#include <string>

#include <WS2tcpip.h> // header for winsock functions
#pragma comment(lib, "ws2_32.lib") // winsock library file (actual)

#define MAX_BUFFER_SIZE (49152) // 48k ish

// Forward declaraton of class
class CTcpListener;

// TODO: Callback to data received
typedef void(*MessageReceivedHandler)(CTcpListener* listener, int socketId, std::string msg);


class CTcpListener
{
public:
	CTcpListener(std::string ipAddress, int port, MessageReceivedHandler handler);
	~CTcpListener();
	
	// Send a message to the specified client
	void Send(int clientSocket, std::string msg);
	
	// Init winsock
	bool Init();
	
	
	// Main processing loop
	void Run();
	
	// Cleanup up after using the service
	void Cleanup();
	
private:
	// create a socket
	SOCKET CreateSocket();
	
	// wait for a connection
	SOCKET WaitForConnection(SOCKET listening);

	std::string m_ipAddress;
	int m_port;
	MessageReceivedHandler m_handler;
};

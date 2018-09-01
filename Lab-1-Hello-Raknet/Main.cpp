#include <stdio.h>
#include <string.h>

#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakPeerInterface.h"

int main(void) {
	char str[512];
	bool isServer;

	unsigned int MAX_CLIENTS = 10;
	unsigned short SERVER_PORT = 60000;

	RakNet::RakPeerInterface* pPeer = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet* pPacket;

	printf("(C)lient or (S)erver? \n");
	fgets(str, 512, stdin);

	printf("What is the server port? \n");
	scanf("%hu", &SERVER_PORT);

	if ((str[0] == 'c') || (str[0] == 'C')) {
		RakNet::SocketDescriptor sd;
		pPeer->Startup(1, &sd, 1);
		isServer = false;

		// NEW LINE CHARACTER, ENTER DEFAULT IP ADDRESS
	}
	else {
		printf("Maximum number of clients? \n");
		scanf("%d", &MAX_CLIENTS);

		RakNet::SocketDescriptor sd(SERVER_PORT, 0);
		pPeer->Startup(MAX_CLIENTS, &sd, 1);
		isServer = true;
	}

	//while (1) {}

	if (isServer) {
		printf("Initializing the server... \n");

		pPeer->SetMaximumIncomingConnections(MAX_CLIENTS);
	} // Initiate client
	else {
		printf("Enter server IP or enter for localhost \n");
		fgets(str, 512, stdin);
		strcpy(str, "127.0.0.1");

		if (str[0] == '\n') {
			strcpy(str, "127.0.0.1");
		}

		printf("Initializing the client... \n");
		pPeer->Connect(str, SERVER_PORT, 0, 0);
	}

	while (1) {
		for (pPacket = pPeer->Receive(); pPacket; pPeer->DeallocatePacket(pPacket), pPacket = pPeer->Receive()) {
			switch (pPacket->data[0]) {
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				printf("A client has disconnected. \n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				printf("A client has lost connection. \n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				printf("A client has connected. \n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				printf("Connected to server. \n");
				break;
			case ID_NEW_INCOMING_CONNECTION:
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("Server is full. \n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				if (isServer) {
					printf("A client has disconnected. \n");
				}
				else {
					printf("Server has disconnected. \n");
				}
				break;
			case ID_CONNECTION_LOST:
				if (isServer) {
					printf("A client has lost connection. \n");
				}
				else {
					printf("Server has lost connection. \n");
				}
				break;
			default:
				printf("Message with identifier %i has arrived. \n", pPacket->data[0]);
				break;
			}
		}
	}

	RakNet::RakPeerInterface::DestroyInstance(pPeer);

	return 0;
}
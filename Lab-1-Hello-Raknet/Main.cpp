#include <stdio.h>

#include "RakNet/RakPeerInterface.h"

int main(void) {
	char str[512];
	bool isServer;

	unsigned int MAX_CLIENTS = 10;
	unsigned short SERVER_PORT = 60000;

	RakNet::RakPeerInterface* pPeer = RakNet::RakPeerInterface::GetInstance();

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

	RakNet::RakPeerInterface::DestroyInstance(pPeer);

	return 0;
}
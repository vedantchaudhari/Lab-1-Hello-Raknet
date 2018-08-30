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

	if ((str[0] == 'c') || (str[0] == 'C')) {
		RakNet::SocketDescriptor sd;
		pPeer->Startup(1, &sd, 1);
		isServer = false;
	}
	else {
		RakNet::SocketDescriptor sd(SERVER_PORT, 0);
		pPeer->Startup(MAX_CLIENTS, &sd, 1);
		isServer = true;
	}

	RakNet::RakPeerInterface::DestroyInstance(pPeer);

	return 0;
}
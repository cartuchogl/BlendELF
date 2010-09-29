/*
	BlendELF
	------------------------------------------
	File: 		network.c
	Author:		mbg
	Purpose:	Contains all functions related to networking.
*/

#include "default.h"

#include "gfx.h"
#include "blendelf.h"
#include "types.h"

// global networking variables
int elfNetConnectTimeout = 5000;
int elfNetEventTimeout = 100;

// global server variables
elfServer* server = NULL;
unsigned char runServer = ELF_FALSE;

// global client variables
unsigned char runClient = ELF_FALSE;

ENetHost* client;
ENetAddress clientAddress;
ENetPeer* peer;
ENetEvent clientEvent;

GLFWthread clientThread;

/* initialises networking */
unsigned char elfInitNetworking()
{
	if(enet_initialize() != 0)
	{
		elfWriteToLog("net: an error occurred while initialising networking\n");
		return ELF_FALSE;
	}

	return ELF_TRUE;
}

/* the server thread */
void GLFWCALL elfRunNetworking(void* arg)
{
	// we can't run this unless the server is initialised
	if(server == NULL)
		return;

	// run until runServer is set to false
	while(runServer)
	{
		if(enet_host_service(server->host, &server->event, 100) > 0)
		{
			elfWriteToLog("net: cake event %d\n", server->event.type);

			switch(server->event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				elfWriteToLog("net: client connected from %x:%u\n",
					server->event.peer->address.host,
					server->event.peer->address.port);

				break;
			case ENET_EVENT_TYPE_RECEIVE:
				elfWriteToLog("net: packet of length %d received: %s\n",
					server->event.packet->dataLength,
					server->event.packet->data);

				// TODO: add event to queue

				enet_packet_destroy(server->event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				elfWriteToLog("net: server - client disconnected.\n");
				break;
			default:
				break;
			}
		}
	}
}

/* the client thread */
void GLFWCALL elfRunClientNetworking(void* arg)
{
	if(client == NULL)
		return;

	while(runClient)
	{
		if(enet_host_service(client, &clientEvent, 100) > 0)
		{
			elfWriteToLog("net: cookie event %d\n", clientEvent.type);
			switch(clientEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("you like cake");
				//elfWriteToLog("net: server - client connected.\n");
				//elfWriteToLog("net: client connected from %x:%u\n",
				//	event.peer->address.host,
				//	event.peer->address.port);

				break;
			case ENET_EVENT_TYPE_RECEIVE:
				elfWriteToLog("net: packet of length %d received\n",
					clientEvent.packet->dataLength);

				// TODO: add event to queue

				enet_packet_destroy(clientEvent.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				elfWriteToLog("net: client - client disconnected.\n");
				break;
			default:
				break;
			}
		}
	}
}

/* runs the engine as server by creating a new networking session */
unsigned char elfCreateSession(const char* address, int port)
{
	// cannot initialise server if the engine is already hosting a session
	if(NULL != server)
	{
		elfWriteToLog("net: aborting attempt to initialise server: server is already initialised\n");
		return ELF_FALSE;
	}

	// initialise the server handle
	server = (elfServer*)malloc(sizeof(elfServer));

	enet_address_set_host(&server->address, address);
	server->address.port = port;

	printf("hostname: %x\n", server->address.host);

	server->host = enet_host_create(&server->address, 32, 0, 0);

	if(NULL == server->host)
	{
		elfWriteToLog("net: unable to initialise server\n");
		return ELF_FALSE;
	}

	elfWriteToLog("net: server initialised at %s:%d\n", address, port);

	// run the server thread
	runServer = ELF_TRUE;
	server->thread = glfwCreateThread(elfRunNetworking, server);

	// server has successfully been initialised
	return ELF_TRUE;
}

unsigned char elfConnectSession(const char* address, int port)
{
	elfWriteToLog("net: attempting to connect to %s:%d\n", address, port);

	if(NULL != peer)
	{
		elfWriteToLog("net: aborting attempt to connect to server: client is already connected\n");
		return ELF_FALSE;
	}

	client = enet_host_create(0, 1, 0, 0);

	if(NULL == client)
	{
		elfWriteToLog("net: failed to create client\n");
		return ELF_FALSE;
	}

	//clientAddress = (ENetAddress*)malloc(sizeof(ENetAddress));
	enet_address_set_host(&clientAddress, address);
	clientAddress.port = port;

	//printf("hostname: %x\n", clientAddress.host);

	peer = enet_host_connect(client, &clientAddress, 2);

	if(NULL == peer)
	{
		elfWriteToLog("net: failed to connect to server\n");
		return ELF_FALSE;
	}

	if(enet_host_service(client, &clientEvent, elfNetConnectTimeout) > 0 && clientEvent.type == ENET_EVENT_TYPE_CONNECT)
	{
		elfWriteToLog("net: successfully connected to %s:%d\n", address, port);

		runClient = ELF_TRUE;

		clientThread = glfwCreateThread(elfRunClientNetworking, client);

		return ELF_TRUE;
	}

	enet_peer_reset(peer);

	elfWriteToLog("net: unable to connect to host\n");

	return ELF_FALSE;
}

unsigned char elfDisconnectSession()
{
	if(NULL == peer)
	{
		return ELF_FALSE;
	}

	runClient = ELF_FALSE;

	if(glfwWaitThread(clientThread, GLFW_WAIT))
	{
		enet_peer_disconnect(peer, 0);

		if(NULL != client)
			enet_host_destroy(client);

		peer = NULL;
		client = NULL;

		return ELF_TRUE;
	}
	else
	{
		elfWriteToLog("net: unable to terminate client thread");

		return ELF_FALSE;
	}
}

unsigned char elfStopSession()
{
	if(NULL == server)
	{
		return ELF_FALSE;
	}

	runServer = ELF_FALSE;

	if(glfwWaitThread(server->thread, GLFW_WAIT))
	{
		enet_host_destroy(server->host);

		free(server);
		server = NULL;

		return ELF_TRUE;
	}
	else
	{
		elfWriteToLog("net: unable to terminate server thread");
		return ELF_FALSE;
	}
}

void elfSendStringToClients(const char* message)
{
	ENetPacket* packet;

	if(NULL == server) return;

	packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(server->host, 0, packet);
}

void elfSendStringToServer(const char* message)
{
	ENetPacket* packet;

	if(NULL == peer) return;

	packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(client, 0, packet);
}

const char* elfGetServerDataAsString()
{
	return (char*)clientEvent.packet->data;
}

const char* elfGetClientDataAsString()
{
	return (char*)server->event.packet->data;
}

int elfGetServerEvent()
{
	switch(server->event.type)
	{
	case ENET_EVENT_TYPE_NONE:
		return (int)ELF_NET_NONE;
	case ENET_EVENT_TYPE_CONNECT:
		return (int)ELF_NET_CONNECT;
	case ENET_EVENT_TYPE_RECEIVE:
		return (int)ELF_NET_RECEIVE;
	case ENET_EVENT_TYPE_DISCONNECT:
		return (int)ELF_NET_DISCONNECT;
	}

	return (int)ELF_NET_NONE;
}

int elfGetClientEvent()
{
	switch(clientEvent.type)
	{
	case ENET_EVENT_TYPE_NONE:
		return (int)ELF_NET_NONE;
	case ENET_EVENT_TYPE_CONNECT:
		return (int)ELF_NET_CONNECT;
	case ENET_EVENT_TYPE_RECEIVE:
		return (int)ELF_NET_RECEIVE;
	case ENET_EVENT_TYPE_DISCONNECT:
		return (int)ELF_NET_DISCONNECT;
	}

	return (int)ELF_NET_NONE;
}

int elfGetCurrentClient()
{
	return (int)server->event.peer->incomingPeerID;
}

/* gets a value indicating whether the engine is running in server mode */
unsigned char elfIsServer()
{
	return NULL == peer;
}

/* gets a value indicating whether the engine is running in client mode */
unsigned char elfIsClient()
{
	return NULL == server;
}

/* deinitialises networking */
void elfDeinitNetworking()
{
	if(NULL != peer)
	{
		elfDisconnectSession();
	}
	if(NULL != server)
	{
		enet_host_destroy(server->host);
		free(server);
	}
	if(NULL != client)
	{
		enet_host_destroy(client);
	}

	// lastly, deinitialise the enet library
	enet_deinitialize();
}

/* 
	End of File 
*/


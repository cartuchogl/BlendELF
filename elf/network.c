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
int elf_net_connect_timeout = 5000;
int elf_net_event_timeout = 100;

// global server variables
elf_server* server = NULL;
unsigned char run_server = ELF_FALSE;

// global client variables
unsigned char run_client = ELF_FALSE;

ENetHost* client;
ENetAddress clientAddress;
ENetPeer* peer;
ENetEvent clientEvent;

GLFWthread clientThread;

/* initialises networking */
unsigned char elf_init_networking()
{
	if(enet_initialize() != 0)
	{
		elf_write_to_log("net: an error occurred while initialising networking\n");
		return ELF_FALSE;
	}

	return ELF_TRUE;
}

/* the server thread */
void GLFWCALL elf_run_networking(void* arg)
{
	// we can't run this unless the server is initialised
	if(server == NULL)
		return;

	// run until run_server is set to false
	while(run_server)
	{
		if(enet_host_service(server->host, &server->event, 100) > 0)
		{
			elf_write_to_log("net: cake event %d\n", server->event.type);

			switch(server->event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				elf_write_to_log("net: client connected from %x:%u\n",
					server->event.peer->address.host,
					server->event.peer->address.port);

				break;
			case ENET_EVENT_TYPE_RECEIVE:
				elf_write_to_log("net: packet of length %d received: %s\n",
					server->event.packet->dataLength,
					server->event.packet->data);

				// TODO: add event to queue

				enet_packet_destroy(server->event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				elf_write_to_log("net: server - client disconnected.\n");
				break;
			default:
				break;
			}
		}
	}
}

/* the client thread */
void GLFWCALL elf_run_client_networking(void* arg)
{
	if(client == NULL)
		return;

	while(run_client)
	{
		if(enet_host_service(client, &clientEvent, 100) > 0)
		{
			elf_write_to_log("net: cookie event %d\n", clientEvent.type);
			switch(clientEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("you like cake");
				//elf_write_to_log("net: server - client connected.\n");
				//elf_write_to_log("net: client connected from %x:%u\n",
				//	event.peer->address.host,
				//	event.peer->address.port);

				break;
			case ENET_EVENT_TYPE_RECEIVE:
				elf_write_to_log("net: packet of length %d received\n",
					clientEvent.packet->dataLength);

				// TODO: add event to queue

				enet_packet_destroy(clientEvent.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				elf_write_to_log("net: client - client disconnected.\n");
				break;
			default:
				break;
			}
		}
	}
}

/* runs the engine as server by creating a new networking session */
unsigned char elf_create_session(const char* address, unsigned short port)
{
	// cannot initialise server if the engine is already hosting a session
	if(NULL != server)
	{
		elf_write_to_log("net: aborting attempt to initialise server: server is already initialised\n");
		return ELF_FALSE;
	}

	// initialise the server handle
	server = (elf_server*)malloc(sizeof(elf_server));

	enet_address_set_host(&server->address, address);
	server->address.port = port;

	printf("hostname: %x\n", server->address.host);

	server->host = enet_host_create(&server->address, 32, 0, 0);

	if(NULL == server->host)
	{
		elf_write_to_log("net: unable to initialise server\n");
		return ELF_FALSE;
	}

	elf_write_to_log("net: server initialised at %s:%d\n", address, port);

	// run the server thread
	run_server = ELF_TRUE;
	server->thread = glfwCreateThread(elf_run_networking, server);

	// server has successfully been initialised
	return ELF_TRUE;
}

unsigned char elf_connect_session(const char* address, unsigned short port)
{
	elf_write_to_log("net: attempting to connect to %s:%d\n", address, port);

	if(NULL != peer)
	{
		elf_write_to_log("net: aborting attempt to connect to server: client is already connected\n");
		return ELF_FALSE;
	}

	client = enet_host_create(0, 1, 0, 0);

	if(NULL == client)
	{
		elf_write_to_log("net: failed to create client\n");
		return ELF_FALSE;
	}

	//clientAddress = (ENetAddress*)malloc(sizeof(ENetAddress));
	enet_address_set_host(&clientAddress, address);
	clientAddress.port = port;

	//printf("hostname: %x\n", clientAddress.host);

	peer = enet_host_connect(client, &clientAddress, 2);

	if(NULL == peer)
	{
		elf_write_to_log("net: failed to connect to server\n");
		return ELF_FALSE;
	}

	if(enet_host_service(client, &clientEvent, elf_net_connect_timeout) > 0 && clientEvent.type == ENET_EVENT_TYPE_CONNECT)
	{
		elf_write_to_log("net: successfully connected to %s:%d\n", address, port);

		run_client = ELF_TRUE;

		clientThread = glfwCreateThread(elf_run_client_networking, client);

		return ELF_TRUE;
	}

	enet_peer_reset(peer);

	elf_write_to_log("net: unable to connect to host\n");

	return ELF_FALSE;
}

unsigned char elf_disconnect_session()
{
	if(NULL == peer)
	{
		return ELF_FALSE;
	}

	run_client = ELF_FALSE;

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
		elf_write_to_log("net: unable to terminate client thread");

		return ELF_FALSE;
	}
}

unsigned char elf_stop_session()
{
	if(NULL == server)
	{
		return ELF_FALSE;
	}

	run_server = ELF_FALSE;

	if(glfwWaitThread(server->thread, GLFW_WAIT))
	{
		enet_host_destroy(server->host);

		free(server);
		server = NULL;

		return ELF_TRUE;
	}
	else
	{
		elf_write_to_log("net: unable to terminate server thread");
		return ELF_FALSE;
	}
}

void elf_send_string_to_clients(const char* message)
{
	ENetPacket* packet;

	if(NULL == server) return;

	packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(server->host, 0, packet);
}

void elf_send_string_to_server(const char* message)
{
	ENetPacket* packet;

	if(NULL == peer) return;

	packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(client, 0, packet);
}

const char* elf_get_server_data_as_string()
{
	return (char*)clientEvent.packet->data;
}

const char* elf_get_client_data_as_string()
{
	return (char*)server->event.packet->data;
}

int elf_get_server_event()
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

int elf_get_client_event()
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

int elf_get_current_client()
{
	return (int)server->event.peer->incomingPeerID;
}

/* gets a value indicating whether the engine is running in server mode */
unsigned char elf_is_server()
{
	return NULL == peer;
}

/* gets a value indicating whether the engine is running in client mode */
unsigned char elf_is_client()
{
	return NULL == server;
}

/* deinitialises networking */
void elf_deinit_networking()
{
	if(NULL != peer)
	{
		elf_disconnect_session();
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


#ifdef __linux__
	#include <unistd.h>
	#include <arpa/inet.h>
#elif __WIN32
	#include <winsock2.h>
#else
	#warning "net.h: platform is not supported!"
#endif 

#if defined(__linux__) || defined(__WIN32)

typedef enum error_t {
	WINSOCK_ERR = -1;
	SOCKET_ERR = -2;
}	error_t;

#include "net.h"

extern int listen_net(char *address){
#ifdef __WIN32
	WSDATA wsa;
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0){
		return WINSOCK_ERR;
	}
	#endif 
		int listener = socket(AF_INET, SOCK_STREAM, 0);
		if (listener < 0) {
			return SOCKET_ERR;
		}
		
}
extern int accept_net(int listener){

}

extern int connect_net(char *address){

}
extern int close_net(int conn){

}

extern int send_net(int conn, char *buffer, size_t size){

}
extern int recv_net(int conn, char *buffer, size_t size){

}

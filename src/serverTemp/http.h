 
#pragma once
#ifndef HTTP_H
#define HTTP_H

#include <iostream>
#include <string>
#include <stdint.h>

typedef struct HTTPreq {
	char method[16]; //GET
	char path[2048];
	char proto[16]; //HTTP/1.1
	uint8_t state;
	size_t index;
} HTTPreq;
	
typedef struct HTTP HTTP;


extern HTTP *new_http(char *address);
extern void free_http(HTTP *http);

extern void handle_http(HTTP *http, char *path, void(*)(int, HTTPreq*));
extern uint8_t listen_http(HTTP *http);

extern void parsehtml_http(int conn, char *filename);


#endif
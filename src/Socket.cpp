#include "Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include<iostream>

using namespace pr;
using namespace std;

namespace pr{

void Socket::connect(const std::string & host, int port){
	addrinfo * addr;
	int addinfo =getaddrinfo(host.c_str(),NULL,NULL, &addr);
	if(addinfo !=0){
		perror("getaddrinfo");
	}
	in_addr ip = ((struct sockaddr_in *)addr->ai_addr)->sin_addr;
	std::cout<<inet_ntoa(ip)<<std::endl;
	freeaddrinfo(addr);
	connect(ip,port);
}

void Socket::connect(in_addr ipv4, int port){
	 if ((fd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
	 perror("socket");
	 exit(1);
	 }
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	std::cout<<htons(port)<<std::endl;
	sin.sin_addr = ipv4;

	::connect(fd,(struct sockaddr *)&sin, sizeof(sockaddr_in));
}

void Socket::close(){
	shutdown(fd,2);
	::close(fd);
}

std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr){
	std::string host = inet_ntoa(addr->sin_addr);
	return os<<host<<addr->sin_port;
}


}

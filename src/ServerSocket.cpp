/*
 * ServerSocket.cpp
 *  Created on: 2 déc. 2018
 *      Author: lynda
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include "ServerSocket.h"
#include "Socket.h"
#include <unistd.h>
#include<iostream>

using namespace std;
namespace pr{

	ServerSocket::ServerSocket(int port){
		sockaddr_in sin;
		memset((char *)&sin,0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		sin.sin_addr.s_addr = htonl(INADDR_ANY);
		std::cout<<"prof"<<&sin<<std::endl;
		socketfd = ::socket(AF_INET,SOCK_STREAM,0);
		if (socketfd<0){
			perror("socket"); exit(1);
		}
		if (bind(socketfd,(struct sockaddr *) &sin,sizeof(sockaddr_in))){
			perror("bind");
			 exit(1);
		}
		::listen(socketfd,1);
	}


	Socket ServerSocket::accept(){
		sockaddr_in exp;
		unsigned sz = sizeof(exp);
		int scom = ::accept(getFD(),(struct sockaddr *)&exp, &sz);
		if(scom==-1){
			perror("accept");
			exit(3);
		}
		return Socket(scom);
	}


	void ServerSocket::close(){
		shutdown(getFD(),2);
		::close(socketfd);
	}


}

/*
 * TCPServer.cpp
 *
 *  Created on: 3 déc. 2018
 *      Author: 3703039
 */
#include <unistd.h>
#include "TCPServer.h"
#include "Socket.h"
#include "Pool.h"
#include "JobConcret.h"
namespace pr{

bool TCPServer::startServer(int port){
	ss = new ServerSocket(port);
	while(1){
		if(ss->isOpen()){
			auto clone = handler->clone();
			Socket s = ss->accept();
			pool->addJob(new JobConcret(clone,s));
			pool->start(1);
		}
	//return true;
	}
	return true;
}


void TCPServer::stopServer (){
	ss->close();
	//pool->stop();
	handler->~ConnectionHandler();
	pool->~Pool();
}

}





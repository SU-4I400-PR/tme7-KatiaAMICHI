/*
 * JobConcret.h
 *
 *  Created on: 7 déc. 2018
 *      Author: 3703039
 */

#ifndef SRC_JOBCONCRET_H_
#define SRC_JOBCONCRET_H_
#include "ServerSocket.h"
#include "Job.h"
#include <unistd.h>
#include "ConnectionHandler.h"
using namespace pr;
using namespace std;

class JobConcret:public Job{

	ConnectionHandler * handler;
	Socket s;

public:
	JobConcret(ConnectionHandler * handler,Socket s):handler(handler),s(s){}

	void run(){
		handler->handleConnection(s);
	}

	~JobConcret(){}
};



#endif /* SRC_JOBCONCRET_H_ */

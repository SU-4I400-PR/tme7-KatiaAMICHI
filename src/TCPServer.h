#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

#include <thread>
#include "ServerSocket.h"
#include "ConnectionHandler.h"
#include "Pool.h"

namespace pr {

// un serveur TCP, la gestion des connections est déléguée
class TCPServer {
	ServerSocket * ss; // la socket d'attente si elle est instanciee
	ConnectionHandler * handler; // le gestionnaire de session passe a la constru
	Pool * pool = new Pool(20);

public :
	TCPServer(ConnectionHandler * handler): ss(nullptr),handler(handler){}
	// Tente de creer une socket d'attente sur le port donné
	bool startServer (int port);

	// stoppe le serveur
	void stopServer () ;
};

} // ns pr

#endif /* SRC_TCPSERVER_H_ */

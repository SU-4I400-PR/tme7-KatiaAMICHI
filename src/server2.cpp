#include "TCPServer.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

class IncrementServer : public pr::ConnectionHandler {

public :
	void handleConnection (pr::Socket sc) {

		int fd = sc.getFD();

		ssize_t msz = sizeof(int);
		while (1) {

			int lu;
			auto nblu = read(fd, &lu, msz);
			if (nblu == 0) {
				std::cout << "Fin connexion par client" << std::endl;
				break;
			} else if (nblu < msz) {
				perror("read");
				break;
			}
			std::cout << "lu =" << lu << std::endl;

			if (lu == 0) {
				break;
			}
			lu++;
			if (write(fd, &lu, msz) < msz) {
				perror("write");
				break;
			}
			std::cout << "envoyé =" << lu << std::endl;
		}
	}
	ConnectionHandler * clone() const {
		return new IncrementServer();
	}

};

int main() {

	pr::TCPServer server(new IncrementServer());

	server.startServer(1664);

	// attend entree sur la console
//	std::string s ;
//	std::cin >> s ;

	std::cout << "Début fin du serveur." << std::endl ;
	// on quit
	server.stopServer();
	std::cout << "Ok fin du serveur." << std::endl;

	return 0;
}


int main00(int argc, char* argv[]) {

	std::cout << " argv[0]  :" << argv[3] << std::endl;
	pr::TCPServer server(new IncrementServer());

	server.startServer(atoi(argv[2]));

//	 attend entree sur la console
	std::string s ;
	std::cin >> s ;

	std::cout << "Début fin du serveur." << std::endl ;
	// on quit
	server.stopServer();
	std::cout << "Ok fin du serveur." << std::endl;

	return 0;
}




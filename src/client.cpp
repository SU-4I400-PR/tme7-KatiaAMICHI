#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>

/*
int main(int argc, char* argv[]) {
	pr::Socket sock;
	sock.connect(argv[2], atoi(argv[3]));
	std::string PATH_FILE_TO_SEND = "";
	std::fstream fs;
	char file_size[256];

	while(1){
		std::string s;
		std::cin>>s;
		int r = 0;
		switch(s){
			case "LIST":
				r=1;
				std::string listOUT;
				write(sock.getFD(),&r,sizeof(int));
				read(sock.getFD(),&r,sizeof(int));
				read(sock.getFD(),&listOUT, r*sizeof(char));
				break;
			case "UPLOAD":
				r=2;

		        fd = fs.open(PATH_FILE_TO_SEND, O_RDONLY);

				break;
			case "DOWNLOAD":
				r=3;
				write(sock.getFD(),&r,sizeof(int));

				break;
			default:
				break;
		}

		fs.close();

	}


	int N=42;
	write(sock.getFD(),&N,sizeof(int));

	std::cout << N << std::endl;
	return 0;
}*/

int main000() {
	pr::Socket sock;
	sock.connect("127.0.0.1", 1664);
	int N=42;
	write(sock.getFD(),&N,sizeof(int));
	read(sock.getFD(),&N,sizeof(int));
	std::cout << N << std::endl;
	return 0;
}


// avec controle
int main() {

	pr::Socket sock;

	sock.connect("127.0.0.1", 1664);

	if (sock.isOpen()) {
		int fd = sock.getFD();
		int i = 10;
		ssize_t msz = sizeof(int);
		if (write(fd, &i, msz) < msz) {
			perror("write");
		}
		std::cout << "envoyé =" << i << std::endl;
		int lu;
		auto nblu = read(fd, &lu, msz);
		std::cout<<lu<<std::endl;
		if (nblu == 0) {
			std::cout << "Fin connexion par serveur" << std::endl;
		} else if (nblu < msz) {
			perror("read");
		}
		std::cout << "lu =" << lu << std::endl;
	} else {
		std::cout << "connection refused" << std::endl;
	}

	return 0;
}


// avec une boucle, on attend un 0
int main00() {

	pr::Socket sock;

	sock.connect("localhost", 1664);

	if (sock.isOpen()) {
		int fd = sock.getFD();

		ssize_t msz = sizeof(int);
		for (int i = 10; i >= 0; i--) {
			if (write(fd, &i, msz) < msz) {
				perror("write");
				break;
			}
			std::cout << "envoyé =" << i << std::endl;

			int lu;
			auto nblu = read(fd, &lu, msz);
			if (nblu == 0) {
				std::cout << "Fin connexion par serveur" << std::endl;
				break;
			} else if (nblu < msz) {
				perror("read");
				break;
			}
			std::cout << "lu =" << lu << std::endl;
		}
	}

	return 0;
}


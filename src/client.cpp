#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	pr::Socket sock;

	sock.connect("127.0.0.1", 1664);
	//sock.connect(argv[2], atoi(argv[3]));
	const char * PATH_FILE_TO_SEND = "/users/nfs/Etu9/3703039/tme7PR/tme7PR.txt";
	const char * PATH_FILE_TO_R = "/users/nfs/Etu9/3703039/tme7PR/FileReceiverClient.txt";
	int sizeFileR;
	std::ofstream outFile(PATH_FILE_TO_R,std::ofstream::out);
	std::ifstream inFile(PATH_FILE_TO_SEND,std::ifstream::binary);
	int sizeFile;
	enum REQ {LIST, UPLOAD, DOWNLOAD};
	while(1){
		std::string s;
		std::cin>>s;
		int r = 0;
		int written;
		switch(atoi(s.c_str())){
			case 1:
				r=1;
				write(sock.getFD(),&r,sizeof(int));
				read(sock.getFD(),&r,sizeof(int));
				std::cout<<"r : "<<r<<std::endl;
				char listOUT[r+1];
				read(sock.getFD(),&listOUT, r);
				std::cout<<"listOUT : "<<listOUT<<std::endl;
				break;
			case 2:
				r=2;
				write(sock.getFD(),&r,sizeof(int));

				// la taille
				inFile.seekg (0, inFile.end);
				sizeFile = inFile.tellg();
				inFile.seekg (0, inFile.beg);
				char buffer[1024];
				//write(sock.getFD(),&sizeFile,sizeof(int));

				// contenue du file dans buffer
				inFile.read(buffer, sizeFile);

				write(sock.getFD(), buffer, sizeFile);
				inFile.close();
				break;
			case 3:
				r=3;
				write(sock.getFD(),&r,sizeof(int));
				sizeFileR = 1024;
				char bufferR[sizeFileR];
				read(sock.getFD(),&bufferR,sizeFileR);
				std::cout<<"buffer : "<<bufferR<<std::endl;
				outFile << bufferR;
				outFile.close();
				break;
			default:
				break;
		}
		sock.close();
	}

	return 0;
}

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
int main_exo1() {

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


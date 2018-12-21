#include "TCPServer.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "ServerSocket.h"
#include <dirent.h>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
using namespace std;

#define PATH_DIC "/users/nfs/Etu9/3703039/tme7PR"

int main(){
	int readFile;
	int sizeFileR;
	const char * PATH_FILE_TO_SEND = "/users/nfs/Etu9/3703039/tme7PR/tme7PR.txt";
	const char * PATH_FILE_TO_R = "/users/nfs/Etu9/3703039/tme7PR/FileReceived.txt";
	std::ofstream outFile(PATH_FILE_TO_R,std::ofstream::out);
	std::ifstream inFile(PATH_FILE_TO_SEND,std::ifstream::in);
	int sizeFile;
	string str;
	char * home = (char *)PATH_DIC;
	// dossier courant
	DIR* dirCourant= NULL;

	struct dirent* fichier=NULL;
	char* nomfichier=NULL;
	int sz = 0;

	int dir_err = 0;

	pr::ServerSocket ss(1664);

		while (1) {
			pr::Socket sc = ss.accept();
			int fd = sc.getFD();
			int lastSize;
			int lu;
			// recuperation de la requete
			read(fd, &lu, sizeof(int));

			switch(lu){
				case 1:
					ssize_t wr;
					dirCourant = opendir(home);

					if(dirCourant != NULL){
						// recuperation du 1er fic dans dic
						fichier=readdir(dirCourant);

						if ( fichier == NULL )
						   {
							 cout << "Erreur acces fichier ";
						   }
						 else
							  while ( fichier != NULL ){
								  str += string(nomfichier) + ",";
								  fichier=readdir(dirCourant);
							  }
						}
						sz = str.length();
						write(fd,&sz,sizeof(int));
						wr = write(fd,str.c_str(),str.length());
						break;
				case 2:

					// sizeFileR = read(fd,&sizeFileR,sizeof(int));
					// lastSize = sizeFileR;
					lastSize = 1024;
					char bufferR[1024];
					read(fd, &bufferR, sizeof(char)*lastSize);
					std::cout<<"buffer : "<<bufferR<<std::endl;

					outFile << bufferR;
					outFile.close();
					break;
				case 3:
					inFile.seekg (0, inFile.end);
					sizeFile = inFile.tellg();
					inFile.seekg (0, inFile.beg);
					char buffer[1024];
					inFile.read(buffer, sizeFile);
					std::cout<<"buffer : "<<buffer<<std::endl;
					write(fd, buffer, sizeFile);
					break;
				default :
					break;
			}
			sc.close();
		}
		ss.close();



	return 0;
}

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

int main_exo1() {

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




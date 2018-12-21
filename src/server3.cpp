/*
 * serverFtp.cpp
 *
 *  Created on: 19 déc. 2018
 *      Author: 3703039
 */
#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>
#include <dirent.h>
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


using namespace std;

#define PATH_DIC "/users/nfs/Etu9/3703039/tme7PR"

int main(){
	int readFile;
	int sizeFileR;
	const char * PATH_FILE_TO_SEND = " ";
	const char * PATH_FILE_TO_R = " ";
	std::ofstream outFile(PATH_FILE_TO_R,std::ofstream::out);
	std::ifstream inFile(PATH_FILE_TO_SEND,std::ifstream::in);
	int sizeFile;

	pr::ServerSocket ss(1664);

		while (1) {
			pr::Socket sc = ss.accept();
			int fd = sc.getFD();

			int lu;
			// recuperation de la requete
			read(fd, &lu, sizeof(int));

			switch(lu){
				case 1:
					string str;
					char * home = PATH_DIC;
					// dossier courant
					DIR* dirCourant= NULL;

					struct dirent* fichier=NULL;
					char* nomfichier=NULL;
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

								  nomfichier=fichier->d_name;
								  str += nomfichier + ",";
								  fichier=readdir(dirCourant);
							  }
						}

						write(fd,&str.length(),sizeof(int));
						write(fd,str.c_str(),str.length());
						break;
				case 2:
					sizeFileR = read(fd,&sizeFileR,sizeof(int));
					char buffer[sizeFileR];
					read(fd, &buffer, sizeof(char)*sizeFileR);
					outFile << buffer;
					outFile.close();
					break;
				case 3:
					inFile.open(PATH_FILE_TO_SEND,std::ifstream::in);
					sizeFile = inFile.tellg();
					char buffer[sizeFile];
					write(fd, &sizeFile, sizeof(int));
					write(fd, buffer, sizeFile);
					break;
			}
			sc.close();
		}
		ss.close();



	return 0;
}



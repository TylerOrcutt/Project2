/**************************************
*NetworkClient.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __GAME_NETWORKCLIENT_H_
#define __GAME_NETWORKCLIENT_H_
#include<string.h>
#include<sstream>
#include <errno.h>

#include <malloc.h>


#ifdef __linux__
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <resolv.h>
#include <sys/types.h>
#endif

#ifdef _WIN32
#include<WinSock2.h>
#include<WS2tcpip.h>

#include<stdlib.h>
#include<stdio.h>
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib,"AdvApi32.lib")
#endif

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <vector>
#include <openssl/sha.h>
#include <thread>
#include <future>
#include "JSONParser.h"
#include "ConnectionHandler.h"
#include "Crypto.h"
//#define DEBUG
#ifdef DEBUG
#define remoteHost "10.0.0.2"
#define remotePort "9898"
#else
#define remoteHost "10.0.0.15"
#define remotePort "9898"
#endif



class NetworkClient {
private:
	Realm realm;
	SSL_CTX * ctx;
	SSL *ssl = nullptr;
	fd_set master;
	fd_set read_fds;
	timeval t;
	int fdmax;

	std::vector<Realm> realms;
	struct addrinfo hints, *result, *ptr, *servinfo;


#ifdef _WIN32
	//char *port;
	int s;
	WSADATA wsaData;

#endif


	int con = -1;
public:

	NetworkClient(){
		initCTX();
		//	ssl = SSL_new(ctx);
	}
#ifdef __linux__
	bool Connect_LINUX(){

		memset(&hints,0,sizeof hints);
		hints.ai_family=AF_UNSPEC;//use ipv4 or ipv6
		hints.ai_socktype=SOCK_STREAM;//tcp socket
		int res;

		//
		if((res=getaddrinfo(realm.ip.c_str(), realm.port.c_str(),&hints,&servinfo))!=0){
			std::cout<<"host not found.\n";
			return false;
		}
		//setup socket
		con=socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol);
		if(con==-1){
			std::cout<<"socket error.\n";
			return false;
		}
		if(connect(con,servinfo->ai_addr,servinfo->ai_addrlen)==-1){
			close(con);
			std::cout<<"Unable to connect.\n";
			return false;
		}
		//std::cout<<"Atempting SSL Connection\n";
		ssl = SSL_new(ctx);
		SSL_set_fd(ssl,con);
		if ( SSL_connect(ssl)==-1){
			std::cout<<"SSL Connection failed\n";
			return false;
		}
		std::cout<<con<<std::endl;
		fdmax=con;
		SSL_set_fd(ssl,con);
		FD_SET(con,&master);
		return true;
	}
#endif
	bool Connect(){
#ifdef __linux__
		return Connect_LINUX();
#endif
#ifdef _WIN32
		return Connect_WIN();
#endif
	}
#ifdef _WIN32
	bool Connect_WIN(){
		con = INVALID_SOCKET;
		int iresult;
		//closesocket(con);
		//WSACleanup();
		iresult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iresult != 0) {
			printf("WSAStartup failed with error: %d\n", iresult);
			return false;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iresult = getaddrinfo(realm.ip.c_str(), realm.port.c_str(), &hints, &result);
		if (iresult != 0) {
			printf("getaddrinfo failed with error: %d\n", iresult);
			WSACleanup();
			return false;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			con = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (con == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return false;
			}


			// Connect to server.
			iresult = connect(con, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iresult == SOCKET_ERROR) {
				closesocket(con);
				con = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);
		printf("connecting to server...\n");
		if (con == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return false;
		}
		//	printf("connecting to server...\n");
		if (ssl != nullptr){
			SSL_free(ssl);
		}

		ssl = SSL_new(ctx);
		SSL_set_fd(ssl, con);
		if (SSL_connect(ssl) == -1){
			std::cout << "SSL Connection failed\n";
			return false;
		}
		std::cout << con << std::endl;
		fdmax = con;
		SSL_set_fd(ssl, con);
		FD_SET(con, &master);
		//	sendData("");
		//  connected = true;
		//	closesocket(con);
		return true;
	}

#endif

	bool  sendData(std::string data){
		if (con == -1){

			return false;
		}

		data = data + " \n";
		int bytes_sent = SSL_write(ssl, data.c_str(), strlen(data.c_str()));
		if (bytes_sent == 0){
			std::cout << ">>>failed to send message\n";
		}
		return true;
	}



	bool sendMessage(std::string msg){
		std::string data = "{\"Chat\":\"" + msg + "\"}";
		return sendData(data);
	}

	bool sendLogin(std::string user, std::string pass){
		if (con == -1 && !Connect()){
			return false;
		}
		pass = encrypt_SHA1(pass);
		std::string data = "{\"Login\":[\"username\":\"" + user + "\",\"password\":\"" + pass + "\"]}";
		return sendData(data);
	}


	static 	Dictionary * static_getData(NetworkClient *network){
		Dictionary * dic = network->getData();
		return dic;
	}
	Dictionary * getData(){
		if (con == -1){
			return nullptr;
		}
		read_fds = master;
		Dictionary * dict = nullptr;
		read_fds = master;
		FD_SET(con, &read_fds);
		//std::cout<<"reading data\n";
		t.tv_sec = 0;
		t.tv_usec = 10;

		if (select(con + 1, &read_fds, NULL, NULL, &t) == -1){
			std::cout << "select error\n";
			con = -1;
			return nullptr;
		}
		//std::cout<<"reading data 2\n";
		if (FD_ISSET(con, &read_fds)){//data to be red
			char buffer[1024];
			int bytes;
			//cout<<"data?\n";
			//std::cout<<"reading data\n";
			bytes = SSL_read(ssl, buffer, sizeof(buffer));
			if (bytes <= 0){
				con = -1;
				return nullptr;
			}
			buffer[bytes - 2] = '\0';
			if (bytes > 0){

				std::stringstream ss;
				ss << buffer;
				// std::cout<<ss.str()<<std::endl;
				dict = JSONParser::parseJson(ss.str());
				// dict->printDictionay();
			}/**/
		}
		//}
		return dict;
	}


	/*
	  void ShowCerts()
	  {   X509 *cert;
	  char *line;

	  cert = SSL_get_peer_certificate(ssl);
	  if ( cert != NULL )
	  {
	  printf("Server certificates:\n");
	  line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
	  printf("Subject: %s\n", line);
	  delete(line);
	  line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
	  printf("Issuer: %s\n", line);
	  delete(line);
	  X509_free(cert);
	  }
	  else
	  printf("No certificates.\n");
	  }*/

	bool isConnected(){
		if (con <= 0){
			return false;
		}
		return true;
	}
	void setRealm(Realm  _realm){
		realm = _realm;

	}
	Realm getRealm(){
		return realm;
	}

	std::vector<Realm> * getRealms(){
		return &realms;
}
	void setRealms(std::vector<Realm> _realms){
		realms = _realms;
	}

~NetworkClient(){
#ifdef _WIN32
	closesocket(con);
#else
  close(con);
#endif
  SSL_CTX_free(ctx);
}
private:

//#MARK : OPENSSL functions
void initCTX() {
  SSL_library_init();
    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */
    const SSL_METHOD * meth = SSLv3_client_method();  /* create new server-method instance */
    ctx = SSL_CTX_new(meth);   /* create new context from method */
   if ( ctx == NULL ) {
     ERR_print_errors_fp(stderr);
       abort();
    }

}


};

#endif

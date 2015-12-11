/**************************************
*NetworkClient.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __GAME_CONNECTIONHANDLER_H_
#define __GAME_CONNECTIONHANDLER_H_
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
#include "Crypto.h"
//#define DEBUG
#ifdef DEBUG
#define remoteHost "10.0.0.2"
#define remotePort "9898"
#else
#define remoteHost "10.0.0.15"
#define remotePort "9898"
#endif


struct Realm {
	std::string ip;
	std::string port;
	std::string name;
	void print(){
		std::cout << name << std::endl << ip << std::endl << port << std::endl;
	}
};
class ConnectionHandler {
private:
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
	bool Connect(char * host, char* port,bool useSSL){
#ifdef __linux__
		return Connect_LINUX(host,port,useSSL);
#endif
#ifdef _WIN32
		return Connect_WIN(host,port,useSSL);
#endif
	}
#ifdef _WIN32
	bool Connect_WIN(char * host, char *port, bool useSSL){
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
		iresult = getaddrinfo(host, port, &hints, &result);
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
		if (useSSL){
			ssl = SSL_new(ctx);
			SSL_set_fd(ssl, con);
			if (SSL_connect(ssl) == -1){
				std::cout << "SSL Connection failed\n";
				return false;
			}
		    SSL_set_fd(ssl, con);
			std::cout << con << std::endl;
		}
		//fdmax = con;
		
		//FD_SET(con, &master);
		//	sendData("");
		//  connected = true;
		//	closesocket(con);
		return true;
	}

#endif
#ifdef __linux__
	bool Connect_LINUX(char * host, char *port, bool useSSL){

		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;//use ipv4 or ipv6
		hints.ai_socktype = SOCK_STREAM;//tcp socket
		int res;

		//
		if ((res = getaddrinfo(host, port, &hints, &servinfo)) != 0){
			std::cout << "host not found.\n";
			return false;
		}
		//setup socket
		con = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
		if (con == -1){
			std::cout << "socket error.\n";
			return false;
		}
		if (connect(con, servinfo->ai_addr, servinfo->ai_addrlen) == -1){
			close(con);
			std::cout << "Unable to connect.\n";
			return false;
		}
		//std::cout<<"Atempting SSL Connection\n";
		if(useSSL){
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
		}
		return true;
	}

#endif

	bool  sendDataSSL(std::string data){
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
	bool  sendData(std::string data){
		if (con == -1){

			return false;
		}

	//	data = data + " \n";
		int bytes_sent = send(con, data.c_str(), strlen(data.c_str()),0);
		if (bytes_sent == 0){
			std::cout << ">>>failed to send message\n";
		}
		return true;
	}
	Dictionary * getData(){
		if (con == -1){
			return nullptr;
		}
		
		Dictionary * dict = nullptr;
	
			char buffer[1024];
			int bytes;
			//cout<<"data?\n";
			//std::cout<<"reading data\n";
		
			bytes = recv(con, buffer, sizeof(buffer),0);
			if (bytes <= 0){
				con = -1;
				return nullptr;
			}
			buffer[bytes - 2] = '\0';
			if (bytes>0){
			
				std::stringstream ss;
				ss << buffer;
				std::string d = ss.str();
				for (int i = 0; i < d.length(); i++){
					if (d.substr(i, 1) == "{"){
						d = d.substr(i, d.length() - i);
						break;
					}
				}
				// std::cout<<d<<std::endl;
				dict = JSONParser::parseJson(d);
			//	dict->printDictionay();
			}/**/
		
		//}
		return dict;
	}
	bool retrieveRealmList(){
		if (!Connect("10.0.0.19", "80", false)){
			std::cout << "Could not retrieve Realmlist\n";
			return false;
		}
		std::cout << "Connected to server sending HTTP request\n";
		std::string data = "GET /realmlist HTTP/1.1\nHost:10.0.0.19\nConnection:close\n\n";
		sendData(data);
		Dictionary *dict =getData();

		realms.clear();
		std::vector<DictionaryItem>* items = dict->getNodes();
		for (int i = 0; i < items->size(); i++){
			Realm r;
			r.name = (*items)[i].key;
			for (int n = 0; n < (*items)[i].items.size(); n++){
				if ((*items)[i].items[n].key == "ip"){
					r.ip = (*items)[i].items[n].value;
					
				}
				if ((*items)[i].items[n].key == "port"){
					r.port = (*items)[i].items[n].value;

				}
			}
			r.print();
			realms.push_back(r);
		}



			delete(dict);
			if (realms.size() == 0){
				return false;
			}
			return true;
	}
	std::vector<Realm>getRealms(){
		return realms;
	}

	};
#endif
#ifndef __GAME_NETWORKCLIENT_H_
#define __GAME_NETWORKCLIENT_H_
#include<string.h>
#include<sstream>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <resolv.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <vector>
#include <openssl/sha.h>

#include "Crypto.h"

#define remoteHost "127.0.0.1"
#define remotePort 9898

class NetworkClient {
private:
  SSL_CTX * ctx;
  SSL *ssl;
struct addrinfo hints,*servinfo;
  int con;
public:

  NetworkClient(){
    initCTX();

std::cout<<"SHA1:"<< encrypt_SHA1("asdasd1")<<std::endl;
  }
  bool Connect(){

    memset(&hints,0,sizeof hints);
    hints.ai_family=AF_UNSPEC;//use ipv4 or ipv6
    hints.ai_socktype=SOCK_STREAM;//tcp socket
    int res;

    //
    if((res=getaddrinfo(remoteHost,"9898",&hints,&servinfo))!=0){
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
    //close(s);
    std::cout<<"Unable to connect.\n";
    return false;
    }

      ssl = SSL_new(ctx);
      SSL_set_fd(ssl,con);
      if ( SSL_connect(ssl)==-1){
          std::cout<<"SSL Connection failed\n";
              return false;
            }
      return true;
  }
  void sendData(std::string data){
  //  ShowCerts();
  if(data=="showcert"){
    ShowCerts();
  }
data=data+" \n";
  int bytes_sent=SSL_write(ssl,data.c_str(),strlen(data.c_str()));
    if(bytes_sent==0){
    std::cout<<">>>failed to send message\n";
  }
  }
  void ShowCerts()
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    }
    else
        printf("No certificates.\n");
}
~NetworkClient(){
  close(con);
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

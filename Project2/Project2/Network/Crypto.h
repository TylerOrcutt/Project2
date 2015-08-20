#ifndef __KAL_CRYPTO_H_
#define __KAL_CRYPTO_H_
#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <string>
#include <sstream>
#include <iostream>

std::string encrypt_SHA1(std::string data){
  unsigned char digest[SHA_DIGEST_LENGTH];
    const char*  d = (const char*)data.c_str();

    SHA_CTX sha;
    SHA1_Init(&sha);
    SHA1_Update(&sha, d, strlen(d));
    SHA1_Final(digest, &sha);

    char mdString[SHA_DIGEST_LENGTH*2+1];
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++){
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
      }
      std::stringstream ss;
      ss<<mdString;
      
      return ss.str();
}


#endif
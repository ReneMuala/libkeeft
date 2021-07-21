//
//  client.cpp
//  libkeeft
//
//  Created by René Descartes Domingos Muala on 21/07/21.
//

#include <stdio.h>
#include "socket.hpp"

ClientSocket::ClientSocket(){
    Socket();
}

ClientSocket::ClientSocket(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char *zero){
    configure_stream(lenght, family, port, addr, zero);
}

ClientSocket& ClientSocket::connect(const char * serverAddress){
    
    if(!(this->serverHost = gethostbyname(serverAddress)))
        throw std::runtime_error(std::string(LIBKEEFT_TCPIP_VERSION)+": Unable to get host.");
    
    memcpy((char*)&child.sin_addr, (char*)serverHost->h_addr, this->serverHost->h_length);
    
    freehostent(serverHost);
    
    if(::connect(sock, (sockaddr *)&child, sizeof(sockaddr_in)) < 0)
        throw std::runtime_error(std::string(LIBKEEFT_TCPIP_VERSION)+": Connection failed.");
    
    return (*this);
}

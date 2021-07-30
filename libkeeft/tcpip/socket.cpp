//
//  socket.cpp
//  libkeeft
//
//  Created by René Descartes Domingos Muala on 21/07/21.
//

#include "socket.hpp"

Socket::Socket(){
    child.sin_len = 0;
    child.sin_family = INADDR_ANY;
    child.sin_port = 0;
}

Socket::Socket(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char *zero){
    configure_stream(lenght, family, port, addr, zero);
}


Socket& Socket::configure_stream(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char *zero){
    child.sin_len = lenght;
    child.sin_family = family;
    child.sin_port = htons(port);
    child.sin_addr.s_addr = addr;
    if(zero)
        strncpy(child.sin_zero, zero, 4);
    
    if((sock = socket(AF_INET, SOCK_STREAM, INTERNET_PROTOCOL)) < 0)
        throw std::runtime_error(std::string(LIBKEEFT_TCPIP_VERSION)+": Unable to configure client socket.");
    return (*this);
}

Socket& Socket::write(void *data, size_t size){
    if((send(sock, data, size, 0)) != size)
        throw std::runtime_error(std::string(LIBKEEFT_TCPIP_VERSION)+": Write operation failed.");
    return (*this);
}

Socket& Socket::read(void *data, size_t size){
    bzero(data, size);
    recv(sock, data, size, 0);
    return (*this);
}

void Socket::close(int sockfd){
    ::close(sockfd);
}

Socket& Socket::close() {
    ::close(sock);
    return (*this);
}

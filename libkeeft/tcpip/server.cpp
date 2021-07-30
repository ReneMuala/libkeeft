//
//  server.cpp
//  libkeeft
//
//  Created by René Descartes Domingos Muala on 21/07/21.
//

#include <stdio.h>

#include "socket.hpp"

ServerSocket::ServerSocket(){
    Socket();
}

ServerSocket::ServerSocket(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char *zero){
    configure_stream(lenght, family, port, addr, zero);
}

ServerSocket& ServerSocket::configure_stream(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char zero[8]){
    child.sin_len = lenght;
    child.sin_family = family;
    child.sin_port = htons(port);
    child.sin_addr.s_addr = addr;
    if(zero)
        strncpy(child.sin_zero, zero, 4);
    
    if((main_sock = socket(AF_INET, SOCK_STREAM, INTERNET_PROTOCOL)) < 0)
        throw std::runtime_error(std::string(LIBKEEFT_TCPIP_VERSION)+": Unable to configure server socket.");
    return (*this);
}

ServerSocket& ServerSocket::reuse(const int data){
    f_reuse_data = 1;
    //ENOTSOCK
    if(setsockopt(main_sock, SOL_SOCKET, data, &f_reuse_data, sizeof(f_reuse_data))<0)
        printf("%s", (std::string(LIBKEEFT_TCPIP_VERSION)+": Unable to reuse adrr and port. errno:" + std::to_string(errno)).c_str());
    return (*this);
}

ServerSocket& ServerSocket::bind(){
    
    if(::bind(main_sock, (sockaddr *)&child, sizeof(sockaddr_in)) < 0)
        throw std::runtime_error(std::string(LIBKEEFT_TCPIP_VERSION)+": Bind operation failed.");
    return (*this);
}

ServerSocket& ServerSocket::listen(const int connections_count){
    if(::listen(main_sock, connections_count) < 0)
        throw std::runtime_error(std::string(LIBKEEFT_TCPIP_VERSION)+": Listen operation failed.");
    return (*this);
}

ServerSocket& ServerSocket::accept(){
    socklen_t len = sizeof(sockaddr_in);
    if(!(sock = ::accept(main_sock, (struct sockaddr *)this, &len)))
        throw std::runtime_error(std::string(LIBKEEFT_TCPIP_VERSION)+": Accept operation failed.");
    return (*this);
}

ServerSocket& ServerSocket::export_accepted(int & sockfd){
    
    sockfd = sock;
    
    return (*this);
}

//
//  socket.hpp
//  libkeeft
//
//  Created by René Descartes Domingos Muala on 21/07/21.
//

#ifndef socket_hpp
#define socket_hpp

#include <iostream>
#include <string>
#include <functional>

#include <sys/socket.h> // sockaddr
#include <netdb.h> // hostent
#include <netinet/in.h> // protocols
#include <sys/types.h> // types

#define LIBKEEFT_TCPIP_VERSION "libkeeft/tcpip 0.1"

class Socket {
    
public:
    
    const int INTERNET_PROTOCOL = 0;
    
    sockaddr_in child;
    
    int sock;
    
    Socket();
    
    Socket(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char zero[8]);
    
    virtual Socket& configure_stream(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char zero[8]);
    
    virtual Socket& write(void * from, size_t size);
    
    virtual Socket& read(void * to, size_t max_size);
    
    ~Socket();
    
};

class ClientSocket: public Socket {
    hostent * serverHost;
public:
    
    ClientSocket();

    ClientSocket(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char *zero);

    ClientSocket& connect(const char serverAddress[INET_ADDRSTRLEN]);
    
};

class ServerSocket: public Socket {
    int main_sock;
    int f_reuse_data;
public:
    
    ServerSocket();

    ServerSocket(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char *zero);

    ServerSocket& configure_stream(uint8_t lenght, sa_family_t family, int port, in_addr_t addr, char zero[8]) override;
    
    /**
     @brief Forces the  API to reuse the address and port, must to be called after configure_stream(...)  and before bind()
     */
    ServerSocket& reuse();
    
    ServerSocket& bind();
    
    ServerSocket& listen(int = 5);
    
    ServerSocket& accept();
};

#endif /* socket_hpp */

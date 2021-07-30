//
//  tcpip_server_using_select_test.cpp
//  libkeeft
//
//  Created by René Descartes Domingos Muala on 21/07/21.
//

#include <iostream>
#include "tcpip/socket.hpp"

#include <sys/select.h>
#include <sys/types.h>

//fd_set readfds;
//
//// Clear an fd_set
//FD_ZERO(&readfds);
//
//// Add a descriptor to an fd_set
//FD_SET(master_sock, &readfds);
//
//// Remove a descriptor from an fd_set
//FD_CLR(master_sock, &readfds);
//
////If something happened on the master socket , then its an incoming connection
//FD_ISSET(master_sock, &readfds);

#define MACOS_BIG_SUR_COMPATIBLE

#ifdef MACOS_BIG_SUR_COMPATIBLE

    #ifndef FD_ZERO
        /// Clear an fd_set
        #define FD_ZERO(n, p) __DARWIN_FD_ZERO(n, p)
    #endif

    #ifndef FD_SET
        /// Add a descriptor to an fd_set
        #define FD_SET(n, p) __DARWIN_FD_SET(n, p)
    #endif

    #ifndef FD_CLR
        /// Remove a descriptor from an fd_set
        #define FD_CLR(n, p) __DARWIN_FD_CLR(n, p)
    #endif

    #ifndef FD_ISSET
        /// If something happened on the master socket , then its an incoming connection
        #define FD_ISSET(n, p)  __DARWIN_FD_ISSET(n, p)
    #endif
#endif

int main(int argc, const char * argv[]) {
    ServerSocket server = ServerSocket(0, AF_INET, 40001, INADDR_ANY, NULL);
    
    //server.reuse();
    
    server.bind();
    
    server.listen();
    
    // socket set
    fd_set readfds;
    
    while(1) {
                
        // clear the socket set
        FD_ZERO(&readfds);
        
        //
        
        server.accept();
        
        std::cout << "New conection." << std::endl;
        
        char Message[500] = {"Hello client"};
        
        server.write(Message, strlen(Message));
        
        server.read(Message, 500);
        
        std::cout << "Client says: " << Message << std::endl;
    }
    return 0;
}


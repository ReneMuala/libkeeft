//
//  tcpip_server_test.cpp
//  libkeeft
//
//  Created by René Descartes Domingos Muala on 21/07/21.
//

#include <iostream>
#include "tcpip/socket.hpp"

int main(int argc, const char * argv[]) {
    
    ServerSocket server = ServerSocket(0, AF_INET, 40001, INADDR_ANY, NULL);
    
    //server.reuse();
    
    server.bind();
    
    while(1) {
        
        server.listen();
        
        server.accept();
        
        std::cout << "New conection." << std::endl;
        
        char Message[500] = {"Hello client"};
        
        server.write(Message, strlen(Message));
        
        server.read(Message, 500);
        
        std::cout << "Client says: " << Message << std::endl;
    }
    return 0;
}

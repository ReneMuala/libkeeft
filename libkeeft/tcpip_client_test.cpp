//
//  tcpip_client_test.cpp
//  libkeeft
//
//  Created by René Descartes Domingos Muala on 21/07/21.
//

#include <iostream>
#include "tcpip/socket.hpp"

// #include <sys/select.h>

int main(int argc, const char * argv[]) {
    
    
    ClientSocket client(/*uint8_t lenght: geralmente (0)*/ 0, /*sa_family_t family: A familia do entendereço: IPv4 */ AF_INET, /*int port: Porta*/ 40001, /*in_addr_t addr: Indereço: Qualquer*/ INADDR_ANY , /*char *zero*: Um buffer usado pelo socket: NULL*/NULL);
    
    // Ou
    // ClientSocket client = ClientSocket(0, AF_INET, 40001, INADDR_ANY, NULL);
    
    client.connect("localhost");
    
    std::cout << "New conection." << std::endl;
    
    char Message[500];
    
    client.read(Message, 500);
        
    std::cout << "Server says: " << Message << std::endl;
    
    strcpy(Message,"Hello server");
    
    client.write(Message, strlen(Message));
                
    return 0;
}


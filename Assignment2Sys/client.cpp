#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string>

#include "RobustIO.h"

// finished
void *recieve(void *sockID) { // accepts ouptut from server
    //this is how we get previous messages
	std::string message;
	int clientSocket = *((int *) sockID);
    std::cout << "previous messages: " << std::endl;
	while (1) {
        message = RobustIO::read_string(clientSocket);
		if (message.empty()) {
            std::cout << "your message was r " << message << std::endl;
			close(clientSocket);
            break;
		} else {
			std::cout << message << std::endl;

		}
	}

	std::cout << "You disconnected from server!\n" << std::endl;
	// close(clientSocket);
	exit(1);
}

int main(int argc, char **argv) {
	struct addrinfo hints;
	struct addrinfo *addr;
	struct sockaddr_in *addrinfo;
	int rc;
	int sock;
	char buffer[512];
	int len;
    char* username;
    int port = 55555;

    if(argc < 2){
        std::cout << "Must input username as argument\n" << std::endl;
        exit(0);
    }
    username = argv[1];
    std::cout << "Your username is: " << username << std::endl;

    // Clear the data structure to hold address parameters
    memset(&hints, 0, sizeof(hints));

    // TCP socket, IPv4/IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_ADDRCONFIG;

    // Get address info for local host
    rc = getaddrinfo("localhost", NULL, &hints, &addr);
    if (rc != 0) {
        // Note how we grab errors here
        printf("Hostname lookup failed: %s\n", gai_strerror(rc));
        exit(1);
    }

    // Copy the address info, use it to create a socket
    addrinfo = (struct sockaddr_in *) addr->ai_addr;

    sock = socket(addrinfo->sin_family, addr->ai_socktype, addr->ai_protocol);
    if (sock < 0) {
        printf("Can't connect to server\n");
		exit(1);
    }

    // Make sure port is in network order
    addrinfo->sin_port = htons(port);

    // Connect to the server using the socket and address we resolved
    rc = connect(sock, (struct sockaddr *) addrinfo, addr->ai_addrlen);
    if (rc != 0) {
        printf("Connection failed\n");
        exit(1);
    }

    // Clear the address struct
    freeaddrinfo(addr);

    // Write a test string to the server.
    // RobustIO::write_string(sock, "testing the new functions!!");
    std::cout << "Estabilished connection to server to " << port << "............ " << std::endl;

    int copysock = sock;
    // Send username to server
	RobustIO::write_string(sock, username);

    // a thread made to keep listening from server
    pthread_t thread;
	pthread_create(&thread, NULL, recieve, (void *) &copysock);

    std::string message;
    // for client input
    while(1){
        std::string message;
        std::getline (std::cin,message);
        if(message == "exit"){
            std::cout << "your message was mc " << message << std::endl;
            break;
        }else{
            RobustIO::write_string(sock,message);
        }
        
    }
    std::cout << "closed client" << std::endl;
	close(sock);
}
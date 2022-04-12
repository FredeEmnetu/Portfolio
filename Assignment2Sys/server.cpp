#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <queue>

#include "RobustIO.h"
// finished


struct client { // the information for each client
	int index; // index of client on list
	int sockID; //socket descriptor
	std::string username;
};

struct client ClientArray[1000]; // array to hold informatio for each client
pthread_t thread[1000]; // allow for 1024 clients
int clientCount = 0; // how many clients we have
std::string history[12];	// Holds 	 12 lines of history
int histCount = 0; // holds how many messages we currently have
int x; // index

void *handleNetworking(void *ClientDetail) {
	struct client* clientDetail = (struct client*) ClientDetail;
	std::string usr = clientDetail->username;

	std::cout <<"---- " << clientDetail->username << " has joined the chat ----" << std::endl;
	// std::string fromclient = RobustIO::read_string(ClientDetail.sockID);
	// std::cout << "going to print old messages"<< std::endl;
	for (x = 0; x < 12; x++) { // this wrties to the reciever function 
								// sends history to client
		std::string hist = history[x];
		if (hist.compare("") != 0) {
			RobustIO::write_string(clientDetail->sockID, hist);
		}
	}
	std::string fromclient;
	
	while(1){
		// std::string fromclient = RobustIO::read_string(clientDetail->sockID);
		fromclient = RobustIO::read_string(clientDetail->sockID);
		if(fromclient.empty() || fromclient == "exit"){
			break;
		}
		std::string fullmessage = usr + ": " + fromclient;
		
		if (histCount < 12) {
			// set one of the indices of history to a message
			history[histCount] = fullmessage;
			histCount++;
		}else{
			// move every message down by 1 index which deletes first message
			// set last message to new latest message
			// 1 2 3
			for (x = 0; x < 11; x++) {
				history[x] = history[x+1];
			}
			history[11] = fullmessage;
		}
		// std::cout << "in handle loop" << std::endl;
		if(fromclient == "exit"){	
			std::cout << "your message was hn " << fromclient << std::endl;
			std::cout << "---- " << clientDetail->username << " has left the chat ----" << std::endl;
			close(clientDetail->sockID);
			
			break;
		}else{
			for (x = 0; x < clientCount; x++) { // send message to all other users
				//printf("socket: %d\n", Client[i].sockID);
				if (ClientArray[x].sockID != 0 && (ClientArray[x].sockID != ClientArray[clientDetail->index].sockID)  ) {
					RobustIO::write_string(ClientArray[x].sockID, fullmessage);
				}
			}
			std::cout<<fullmessage << std::endl;
		}
		
	}


	// close(clientDetail->sockID);

	for (x = 0; x <= clientCount; x++) { // free the current index in the client array
		if (ClientArray[x].sockID == ClientArray[clientDetail->index].sockID) {
			ClientArray[x].sockID = 0;
			clientCount--;
			break;
		}
	}
	return NULL;

}

int main(int argc, char **argv) {
	int sock, conn;
	int i;
	int rc;
	struct sockaddr address;
	socklen_t addrLength = sizeof(address);
	struct addrinfo hints;
	struct addrinfo *addr;
	char buffer[512];
	int len;

	for(x = 0; x < 12; x++) {
		history[x] = "";
	}

	// Clear the address hints structure
    memset(&hints, 0, sizeof(hints));

    hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // IPv4/6, socket is for binding
	// Get address info for local host
	if((rc = getaddrinfo(NULL, "55555", &hints, &addr))) {
		printf("host name lookup failed: %s\n", gai_strerror(rc));
		exit(1);
	}

	// Create a socket
    sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if(sock < 0) {
		printf("Can't create socket\n");
		exit(1);
	}

	// Set the socket for address reuse, so it doesn't complain about
	// other servers on the machine.
    i = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

	// Bind the socket
    rc = bind(sock, addr->ai_addr, addr->ai_addrlen);
    if(rc < 0) {
		printf("Can't bind socket\n");
		exit(1);
	}

	// Clear up the address data
    freeaddrinfo(addr);

	// Listen for new connections, wait on up to five of them
    rc = listen(sock, 5);
    if(rc < 0) {
		printf("listen failed\n");
		exit(1);
	}

	// When we get a new connection, try reading some data from it!
	// conn = accept(sock, (struct sockaddr*) &address, &addrLength);
    while ((conn = accept(sock, (struct sockaddr*) &address, &addrLength)) >= 0) {
        // auto s = RobustIO::read_string(conn);
		// printf("Received from client: %s\n", s.c_str());
		// A loop to loop through all clients and find a new one baiscally
		for (x = 0; x <= clientCount; x++) {
			// if the current index of clientCount has a value of zero or NULL give it a
			// new Socked description
			if (ClientArray[x].sockID == 0 || ClientArray[x].sockID == NULL) {
				ClientArray[x].sockID = conn;
				break;
			}
		}
		// on client[x] sets its index value to x
		ClientArray[x].index  = x;
		// get client username
		// this is client's first write is a username so therefore first
		// read is username
		ClientArray[x].username = RobustIO::read_string(ClientArray[x].sockID);

		// create new thread index x
		int ret = pthread_create(&thread[x], NULL, handleNetworking, (void *) &ClientArray[x]);
		if ( ret == 1){ // returns 1 on fail
			printf("Error creating thread for client: %d", ClientArray[x].index);
			exit(1);
		}
		//other wise increase the number of clients
		clientCount++;
		std::cout << "\n";
		std::cout <<"Current number of participants: " << clientCount << std::endl;
		std::cout << "\n";
		// std::cout << "ended here" << std::endl;
    }
	// std::cout << 

	// wait for all threads to 
	for (i = 0; i < clientCount; i++){
		pthread_join(thread[i], NULL);
	}
		
	close(conn);
}
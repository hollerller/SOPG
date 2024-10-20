#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>




int main(){
	
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(21);
    server_address.sin_addr.s_addr = inet_addr("192.168.1.67");

    if (server_address.sin_addr.s_addr == INADDR_NONE) {
        fprintf(stderr, "ERROR invalid server IP\n");
        return 1;
    }

      // Ejecutamos connect()
    if (connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        fprintf(stderr, "ERROR connecting\n");
        close(network_socket);
        exit(EXIT_FAILURE);
    }

    char *username = "ftpserver";
    char *password = "ftpserver";

    


}

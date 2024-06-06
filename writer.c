#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define FIFO_NAME "myfifo"

int fd;

void sigusr1_handler(int sig){
    char *msg = "SIGN:1\n";
    if (write(fd, msg, strlen(msg)) == -1) {
        perror("Error writing to FIFO");
    }

}

void sigusr2_handler(int sig){
    char *msg = "SIGN:2\n";
    if (write(fd, msg, strlen(msg)) == -1){
        perror("Error writing to FIFO");
    }
}



int main(void)
{
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("Error creating FIFO");
    }
    
    printf("Writer PID %d\n", getpid());

    printf("waiting for readers...\n");

    fd = open(FIFO_NAME, O_WRONLY);

    printf("got a reader--type some stuff\n");


    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);


    char s[300];

    int num;
    while (1) {

        char text[300];

        if (fgets(s, 300, stdin) == NULL) {
            printf("EOF detected, closing file...\n");
            break;
        }


        strcpy(text, "DATA:");
        strcat(text, s);

        if ((num = write(fd, s, strlen(s))) == -1)
            perror("write");
        else {
            printf("writer: wrote %d bytes\n", num);
            
            
           if ( write(fd, text, strlen(text)) == -1 ) {
            perror("Error writing to FIFO\n");
           }
            
             }
        }


    close(fd);

}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "myfifo"

int main(void)
{
    mkfifo(FIFO_NAME, 0666);

    
    printf("waiting for writers...\n");
    int fd = open(FIFO_NAME, O_RDONLY);

    if (fd == -1){
        perror("Error opening FIFO\n");
    }

    FILE *signal_file = fopen("signals.txt", "a");

    FILE *logger_file = fopen("log.txt", "a");

    printf("got a writer\n");

    char s[300];
    int num;
    do {


        if ((num = read(fd, s, 300)) == -1)
            perror("read");
        else {


            s[num] = '\0';

            if (strncmp(s, "DATA:", 5) == 0) {
                write(fileno(logger_file), s, strlen(s));
            } else if (strncmp(s, "SIGN:", 5) == 0) {
                write(fileno(signal_file), s, strlen(s));
            }

        }
    }
    while (num > 0);


}

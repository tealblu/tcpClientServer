// Charles "Blue" Kent Hartsell III
// ckhartsell@gmail.com
#include <netdb.h>
#include <time.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 3600
#define SA struct sockaddr

  //function to reverse line and copy to file
void reverseline(char* file, char* msg);
// Function designed for chat between client and server.
void func(int sockfd)
{
// time construct so we can differentiate between clients
    printf("server: in func: sockfd:%d\n", sockfd);
    char buff[MAX];
    char serverfile[MAX];
    int n;
    bzero(buff, MAX);
     bzero(serverfile, MAX);
    //read filename sent from client and copy it to serverfile
    n = read(sockfd, buff, sizeof(buff));
    printf("server: read some data length:%d\n",n);
    //send ACK with file name if n > 0
    if(n > 0){
        printf("buff : %s\n", buff);
     //read serverfile name from client
     //add time to end of filename
        //write ACK and filename to socket

    }
else{
printf("Error.\nExiting...\n");
exit(-1);
}
bzero(buff, MAX);
    //create a string for the contents of file
    char tempstring[MAX];

    //somewhere, you need to open a file and store the received message
    for(;;){
     bzero(buff, MAX);
     n = read(sockfd, buff, sizeof(buff));
    printf("read %d bytes data\n",n);
if(n > 0){
if(strncmp(buff, "DONE", 4) == 0){

    printf("recv %d bytes data, send back ACK\n",n);

    }
    else{
printf("to call reverseline()\n");
     reverseline(serverfile, buff);
     break;
     }
    }
    else{
     printf("Error.\nExiting...\n");
exit(-1);
    }
    }

}

// Driver function
int main(int argc, char* argv[])
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

while(1){
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");
    pid_t pid = fork();
    if(pid==0){
     // Function for chatting between client and server
     printf("child process starts\n");
func(connfd);
    }
  }
    // After chatting close the socket
    //close(sockfd);
}
void reverseline(char* file, char* msg){
//open file to write contents from client
    printf("in reverseline, msg: %s\n", msg);
}

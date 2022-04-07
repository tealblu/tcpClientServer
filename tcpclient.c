// Charles "Blue" Kent Hartsell III
// ckhartsell@gmail.com
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr, my_addr;
    char myIP[16];
    unsigned int myPort;
    // socket create and varification
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
    servaddr.sin_addr.s_addr = inet_addr(argv[2]);
    servaddr.sin_port = htons(atoi(argv[1]));

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // Get my ip address and port
    bzero(&my_addr, sizeof(my_addr));
    int len = sizeof(my_addr);
    getsockname(sockfd, (struct sockaddr *) &my_addr, &len);
    inet_ntop(AF_INET, &my_addr.sin_addr, myIP, sizeof(myIP));
    myPort = ntohs(my_addr.sin_port);
    printf("Local ip address: %s\n", myIP);
    printf("Local port : %u\n", myPort);
    //get peer addr
    //here just reuse my_addr as the peer_addr
    if (getpeername(sockfd, (struct sockaddr *) &my_addr, &len) != 0)
    {

        printf("ERROR in getpeername()\n");
    }
    else
    {
        printf ("peer: ");
        printf ("family: %d\t", my_addr.sin_family);
        printf ("addr: %s\t", inet_ntoa(my_addr.sin_addr));
        printf ("port: %d\n", ntohs( ((struct sockaddr_in)my_addr).sin_port));
    }

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}

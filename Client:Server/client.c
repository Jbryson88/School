// John Bryson
// Network Programming
// CS 3013 - Dr. Zhao
// Due 10/27/2022

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX 1024

int main(int argc, char *argv[])
{

struct sockaddr_in remote_server;
int sock;
char input[MAX];
char output[MAX];
int len;

//creating socket
sock = socket(AF_INET, SOCK_STREAM, 0);

//checking socket was created or not
if(sock == -1)
{
perror("socket:");
exit(-1);
}

//remote server details like port and ip address
remote_server.sin_family = AF_INET;
remote_server.sin_port = htons(9999); //assigning 9999 as port address
remote_server.sin_addr.s_addr = inet_addr(argv[1]); /*IP Address will be taken from command line argument*/
bzero(&remote_server.sin_zero, 8);

//connecting to remote server
if( (connect(sock, (struct sockaddr *)&remote_server, sizeof(struct sockaddr_in))) == -1 )
{
perror("connect:");
exit(-1);
}

while(printf("Client:") && fgets(input, MAX, stdin)!=NULL)
{

send(sock, input, strlen(input),0); //sending the message to server

len = recv(sock, output, MAX,0); //message received from server
output[len] = '\0';
printf("Server: %s\n",output); // printing the message received from the server

}

printf("\n");
close(sock); //closing the socket descriptor
}
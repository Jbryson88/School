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
struct sockaddr_in server, client;
int sock, new;
int sockaddr_len = sizeof(struct sockaddr_in);
int data;
char buffer[MAX];

//creating socket and checking whether socket was created or not
if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
{
perror("socket");
exit(-1);
}

//server details
server.sin_family = AF_INET;
server.sin_port = htons(9999); //assigning 9999 as port address
server.sin_addr.s_addr = INADDR_ANY;
bzero(&server.sin_zero, 8);

//binding to the port
if( bind(sock,(struct sockaddr *)&server, sockaddr_len) == -1)
{
perror("bind");
exit(-1);
}


//listening for incoming connections
if((listen(sock, 5)) == -1)
{
perror("listen");
exit(-1);
}



while(1)
{
printf("Server is ready to talk.....\n");

//accept the incoming connection
if( (new = accept(sock, (struct sockaddr *)&client, &(sockaddr_len))) == -1)
{
perror("Listen");
exit(-1);
}

data = 1;


while(data)
{
data = recv(new, buffer, MAX, 0); //receiving message from client

if(data)
{
send(new,buffer, data, 0);//sending the same message to client
buffer[data] = '\0';
printf("sent messg : %s\n",buffer);//printing the sent message
}


}
printf("Client was disconnected\n\n");
close(new); //closing the file descriptor

}
}
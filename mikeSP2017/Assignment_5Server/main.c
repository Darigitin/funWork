/* A simple server in the internet domain using TCP
	 The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT_NUM 3004

//int cmpfunc (const void * a, const void * b){
//	const char **ia = (const char **) a;
//	const char **ib = (const char **) b;
//	return strcmp(*ia, *ib);
//}

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;


   /*STEP 1********************************************
	int socket(int domain, int type, int protocol);*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/*Make sure opening was successful*/
	if (sockfd < 0)
		error("ERROR opening socket");


   /*STEP 2********************************************
	0 out the server address*/
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	/*convert argument to int*/
	portno = PORT_NUM;
	/*this is always the same for this type of connection*/
	serv_addr.sin_family = AF_INET;
	/*INADDR_ANY is a macro that will find the current machine IP*/
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	/*make sure byte order is correct
	  may be a no-op, but better safe than sorry*/
	serv_addr.sin_port = htons((uint16_t) portno);


   /*STEP 3********************************************/
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0)
		error("ERROR on binding");


   /*STEP 4********************************************
		Open server up for listening, if you don't listen
	  you won't hear*/
	listen(sockfd,5);


   /*STEP 5******************************************/
	clilen = sizeof(cli_addr);
	/*Accept blocks until a connection with
	  a client is made. Returns a new socket
	  to communicate with the new connection.
	  Also receives address data about client*/
	newsockfd = accept(sockfd,
			(struct sockaddr *) &cli_addr,
			&clilen);
	if (newsockfd < 0)
		error("ERROR on accept");
	memset(buffer, 0, 256);

   /*Communicate************************************/
	n = read(newsockfd,buffer,255);
    while ((strcmp(buffer, "stop\n") != 0)){
        printf("I read %d\n",n);
        if (n < 0) error("ERROR reading from socket");
        printf("Here is the message: %s",buffer);
        n = write(newsockfd,"I got your message",18);
		memset(buffer, 0, 256);
        if (n < 0) error("ERROR writing to socket");
        n = read(newsockfd,buffer,255);
    }
    write(newsockfd,"stop",18);
	return 0;
}
/* A simple client in the internet domain using TCP
	 The hostname and port number is passed as arguments*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#define PORT_NUM 3011

int strcmp(const char *str1, const char *str2);

void error(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	/*set up ints for socket file descriptor
	  port number and return of read/write*/
	int sockfd, portno, n, len;
	/*structure for server info*/
	struct sockaddr_in serv_addr;
	/*used to hold the return of the function
	  that finds our server address, will
	  be copied into serv_addr*/
	struct hostent *server;

	/*for our message*/
	char buffer[256];
	/*convert our port number*/
	portno = PORT_NUM;
    len = 0;
	/*create the socket*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/*make sure it was made*/
	if (sockfd < 0)
		error("ERROR opening socket");
	/*gethostbyname takes our host domain name and
	  resolves it to an address, there is a similar
	  function, gethostbyaddr that takes an address
	  and returns the same struct, struct hostent*/
	server = gethostbyname("localhost");
	/*make sure the host exists*/
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	/*0 out the server address stuct and set members*/
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	/*copy the data returned from gethostbyname
	  into the server address struct*/
	memcpy((char *)server->h_addr_list,
			(char *)&serv_addr.sin_addr.s_addr,
		   (size_t) server->h_length);
	serv_addr.sin_port = htons((uint16_t) portno);
	/*Request a connection to the server through the socket we set up
	  make sure it connected, this function will also do the binding
	  of our socket and server info*/
	if (connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");
    do {
        printf("Enter next command> ");
        /*Retrieve a message to send from the user*/
        memset(buffer, 0, 256);
        fgets(buffer,255,stdin);
        /*send the message to the socket*/
        printf("length is %d\n", (int)strlen(buffer));
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0)
            error("ERROR writing to socket");
        memset(buffer, 0, 256);
        /*await an incoming message, read stops all process*/
        //ioctl(sockfd,FIONREAD, &len);
        //if (len > 0) {
		n = read(sockfd, buffer, 255);
		len = atoi(buffer);
		printf("%s\n", buffer);
		if (len > 0){
			write(sockfd, "OK", strlen("OK"));
			read(sockfd,buffer, len);
		}
			printf("%s\n", buffer);
		//}
        if (n < 0)
            error("ERROR reading from socket");
        printf("%s\n",buffer);
    } while((strcmp(buffer, "stop") != 0));
	return 0;
}
/* A simple server in the internet domain using TCP
    The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT_NUM 3011


int strncmp(const char *str1, const char *str2, size_t n);

typedef struct student {
    char lname[10], initial, fname[10];
    unsigned long SID;
    float GPA;
}SREC;

typedef struct node {
    struct student SREC;
    struct node *left, *right;
};

struct node *GPAroot, *SIDroot, *Lnameroot, *Fnameroot;
char* message;

struct node *newNode(char* lname, char* fname, char initial, unsigned long SID, float GPA){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    strncpy(temp->SREC.lname, lname, 9);
    strncpy(temp->SREC.fname, fname, 9);
    temp->SREC.initial = initial;
    temp->SREC.SID = SID;
    temp->SREC.GPA = GPA;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* LnameInsert(struct node* node, char* lname, char* fname, char initial, unsigned long SID, float GPA){
    if (!node)
        node = newNode(lname, fname, initial, SID, GPA);
    else if((strncmp(lname, node->SREC.lname, 9) < 0))
        node->left = LnameInsert(node->left, lname, fname, initial, SID, GPA);
    else
        node->right = LnameInsert(node->right, lname, fname, initial, SID, GPA);
    return node;
}

struct node* FnameInsert(struct node* node, char* lname, char* fname, char initial, unsigned long SID, float GPA){
    if (!node)
        node = newNode(lname, fname, initial, SID, GPA);
    else if((strncmp(fname, node->SREC.fname, 9) < 0))
        node->left = FnameInsert(node->left, lname, fname, initial, SID, GPA);
    else
        node->right = FnameInsert(node->right, lname, fname, initial, SID, GPA);
    return node;
}

struct node* SIDInsert(struct node* node, char* lname, char* fname, char initial, unsigned long SID, float GPA){
    if (!node)
        node = newNode(lname, fname, initial, SID, GPA);
    else if(SID < node->SREC.SID)
        node->left = SIDInsert(node->left, lname, fname, initial, SID, GPA);
    else
        node->right = SIDInsert(node->right, lname, fname, initial, SID, GPA);
    return node;
}

struct node* GPAInsert(struct node* node, char* lname, char* fname, char initial, unsigned long SID, float GPA){
    if (!node)
        node = newNode(lname, fname, initial, SID, GPA);
    else if(GPA < node->SREC.GPA)
        node->left = GPAInsert(node->left, lname, fname, initial, SID, GPA);
    else
        node->right = GPAInsert(node->right, lname, fname, initial, SID, GPA);
    return node;
}

void lNameInOrder(struct node *root, int messageSize, int sizeRemaining){
    char *temp, *tmp;
    int t;
    temp = calloc(48, sizeof(char));
    if(root != NULL){
        lNameInOrder(root->left, messageSize, sizeRemaining);
        snprintf(temp, 48, "| %05lu | %-9s | %-9s | %c | %.2f |\n", root->SREC.SID, root->SREC.lname,
                 root->SREC.fname, root->SREC.initial, root->SREC.GPA);
        if(sizeRemaining < 48){
            message =  realloc(message, messageSize * 2 * sizeof *message);
            t = messageSize - sizeRemaining;
            messageSize *= 2;
            sizeRemaining = messageSize - t;

        }
        strcat(message, temp);
        sizeRemaining -= 48;
        lNameInOrder(root->right, messageSize, sizeRemaining);
    }
}

void getLname(int messageSize){
    int sizeRemaining;
    strcpy(message, "| SID   | Lname     | Fname     | M | GPA  |\n");
    strcat(message, "+-------+-----------+-----------+---+------+\n");
    sizeRemaining = messageSize - 141;
    lNameInOrder(Lnameroot, messageSize, sizeRemaining);
    strcat(message, "+-------+-----------+-----------+---+------+\n");
}

void getFname(char* message){

}

void getSID(char* message){

}

void getGPA(char* message){

}

int put(char* lName, char* fName, char mi, int sid, double gpa){
    printf("lName: %s, fName: %s, mi: %c, sid: %d, gpa: %f\n", lName, fName, mi, sid, gpa);
    Lnameroot = LnameInsert(Lnameroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    Fnameroot = FnameInsert(Fnameroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    SIDroot = SIDInsert(SIDroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    GPAroot = GPAInsert(GPAroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    return 1;
}

int delete(int sid){
printf("sid: %d\n", sid);
return 1;
}

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
    GPAroot = SIDroot = Lnameroot = Fnameroot = NULL;


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
    n = (int) read(newsockfd, buffer, 255);
    while ((strcmp(buffer, "stop\n") != 0)) {
        size_t messageSize;
        messageSize = 255;
        message = calloc(messageSize, sizeof(char));
        printf("I read %d\n", n);
        if (n < 0) error("ERROR reading from socket");
        printf("Here is the message: %s", buffer);
        if (strncmp(buffer, "get", 3) == 0){
            strtok(buffer, " ");
            char* argument = strtok(NULL, " ");
            if (strcmp(argument, "lname\n") == 0)
                getLname(messageSize);
            else if (strcmp(argument, "fname\n") == 0)
                getFname(message);
            else if (strcmp(argument, "SID\n") == 0)
                getSID(message);
            else if (strcmp(argument, "GPA\n") == 0)
                getGPA(message);
//            else
//                message = "Not a valid argument";
        } else if (strncmp(buffer, "put", 3) == 0){
            strtok(buffer, " ");
            char* lName = strtok(NULL, ",");
            char* fName = strtok(NULL, ",");
            char* mi = strtok(NULL, ",");
            int sid =  atoi(strtok(NULL, ","));
            double gpa =  atof(strtok(NULL, ","));
            if(put(lName, fName, mi[0], sid, gpa))
                message = "Put Successful";
            else
                message = "Put failed";
        }
        else if (strncmp(buffer, "delete", 6) == 0){
            strtok(buffer, " ");
            int sid = atoi(strtok(NULL, " "));
//            if(delete(sid))
//                message = "delete successful";
//            else
//                message = "delete unsuccessful";
        } //else
        //  message = "Not a valid command";
        int t = strlen(message);
        sprintf(buffer, "%d", t);
        write(newsockfd, buffer, strlen(buffer));
        read(newsockfd,buffer,255);
        if (strcmp(buffer, "OK") == 0)
            n = (int) write(newsockfd, message, strlen(message));
        memset(buffer, 0, 256);
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd,buffer,255);
    }
    write(newsockfd,"stop",strlen("stop"));
    return 0;
}
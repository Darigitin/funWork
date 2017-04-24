#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT_NUM 3001


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

struct node *GPAroot, *SIDroot, *Lnameroot, *Fnameroot, *deleteNode;
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
    char *temp;
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

void fNameInOrder(struct node *root, int messageSize, int sizeRemaining){
    char *temp;
    int t;
    temp = calloc(48, sizeof(char));
    if(root != NULL){
        fNameInOrder(root->left, messageSize, sizeRemaining);
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
        fNameInOrder(root->right, messageSize, sizeRemaining);
    }
}

void SIDInOrder(struct node *root, int messageSize, int sizeRemaining){
    char *temp;
    int t;
    temp = calloc(48, sizeof(char));
    if(root != NULL){
        SIDInOrder(root->left, messageSize, sizeRemaining);
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
        SIDInOrder(root->right, messageSize, sizeRemaining);
    }
}

void GPAInOrder(struct node *root, int messageSize, int sizeRemaining){
    char *temp;
    int t;
    temp = calloc(48, sizeof(char));
    if(root != NULL){
        GPAInOrder(root->right, messageSize, sizeRemaining);
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
        GPAInOrder(root->left, messageSize, sizeRemaining);
    }
}

void getLname(int messageSize){
    int sizeRemaining;
    strcpy(message, "| SID   | Lname     | Fname     | M | GPA  |\n");
    strcat(message, "+-------+-----------+-----------+---+------+\n");
    sizeRemaining = messageSize - 141;
    lNameInOrder(Lnameroot, messageSize, sizeRemaining);
    strcat(message, "+-------+-----------+-----------+---+------+");
}

void getFname(int messageSize){
    int sizeRemaining;
    strcpy(message, "| SID   | Lname     | Fname     | M | GPA  |\n");
    strcat(message, "+-------+-----------+-----------+---+------+\n");
    sizeRemaining = messageSize - 141;
    fNameInOrder(Fnameroot, messageSize, sizeRemaining);
    strcat(message, "+-------+-----------+-----------+---+------+");
}

void getSID(int messageSize){
    int sizeRemaining;
    strcpy(message, "| SID   | Lname     | Fname     | M | GPA  |\n");
    strcat(message, "+-------+-----------+-----------+---+------+\n");
    sizeRemaining = messageSize - 141;
    SIDInOrder(SIDroot, messageSize, sizeRemaining);
    strcat(message, "+-------+-----------+-----------+---+------+");
}

void getGPA(int messageSize){
    int sizeRemaining;
    strcpy(message, "| SID   | Lname     | Fname     | M | GPA  |\n");
    strcat(message, "+-------+-----------+-----------+---+------+\n");
    sizeRemaining = messageSize - 141;
    GPAInOrder(GPAroot, messageSize, sizeRemaining);
    strcat(message, "+-------+-----------+-----------+---+------+");
}

int put(char* lName, char* fName, char mi, int sid, double gpa){
    printf("lName: %s, fName: %s, mi: %c, sid: %d, gpa: %f\n", lName, fName, mi, sid, gpa);
    Lnameroot = LnameInsert(Lnameroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    Fnameroot = FnameInsert(Fnameroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    SIDroot = SIDInsert(SIDroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    GPAroot = GPAInsert(GPAroot, lName, fName, mi, (unsigned long) sid, (float) gpa);
    return 1;
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node * minValueNode(struct node* node)
{
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

struct node* deleteSID(struct node* root, unsigned long sid)
{
    // base case
    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( sid < root->SREC.SID)
        root->left = deleteSID(root->left, sid);

        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
    else if (sid > root->SREC.SID)
        root->right = deleteSID(root->right, sid);

        // if key is same as root's key, then This is the node
        // to be deleted
    else
    {
        deleteNode = newNode("", "", 0, 0, 0);
        strncpy(deleteNode->SREC.lname, root->SREC.lname, 9);
        strncpy(deleteNode->SREC.fname, root->SREC.fname, 9);
        deleteNode->SREC.GPA = root->SREC.GPA;
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->SREC.SID = temp->SREC.SID;

        // Delete the inorder successor
        root->right = deleteSID(root->right, temp->SREC.SID);
    }
    return root;
}
struct node* deleteLname(struct node* root, char* lname)
{
    // base case
    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( (strncmp(lname, root->SREC.lname, 9) < 0))
        root->left = deleteLname(root->left, lname);

        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
    else if ((strncmp(lname, root->SREC.lname, 9) > 0))
        root->right = deleteLname(root->right, lname);

        // if key is same as root's key, then This is the node
        // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        strcpy(root->SREC.lname, temp->SREC.lname);

        // Delete the inorder successor
        root->right = deleteLname(root->right, temp->SREC.lname);
    }
    return root;
}

struct node* deleteFname(struct node* root, char* fname)
{
    // base case
    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( (strncmp(fname, root->SREC.lname, 9) < 0))
        root->left = deleteFname(root->left, fname);

        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
    else if ((strncmp(fname, root->SREC.lname, 9) > 0))
        root->right = deleteLname(root->right, fname);

        // if key is same as root's key, then This is the node
        // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        strcpy(root->SREC.fname, temp->SREC.fname);

        // Delete the inorder successor
        root->right = deleteLname(root->right, temp->SREC.fname);
    }
    return root;
}

struct node* deleteGPA(struct node* root, float GPA)
{
    // base case
    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( GPA < root->SREC.GPA)
        root->left = deleteGPA(root->left, GPA);

        // If the key to be deleted is greater than the root's key,
        // then it lies in right subtree
    else if (GPA > root->SREC.SID)
        root->right = deleteGPA(root->right, GPA);

        // if key is same as root's key, then This is the node
        // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->SREC.GPA = temp->SREC.GPA;

        // Delete the inorder successor
        root->right = deleteGPA(root->right, temp->SREC.GPA);
    }
    return root;
}

int delete(unsigned long sid){
    deleteSID(SIDroot, sid);
    deleteLname(Lnameroot, deleteNode->SREC.lname);
    deleteFname(Fnameroot, deleteNode->SREC.fname);
    deleteGPA(GPAroot, deleteNode->SREC.GPA);
    return 1;
}

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void preOrderTraversal(struct node* root,FILE *fp){

    if (root != NULL){
        fprintf(fp, "%lu,%s,%s,%c,%f\n", root->SREC.SID, root->SREC.lname,
                 root->SREC.fname, root->SREC.initial, root->SREC.GPA);
        preOrderTraversal(root->left, fp);
        preOrderTraversal(root->right, fp);
    }
}

void saveFile(){
    FILE *fp;

    fp = fopen("database.bin", "w");
    preOrderTraversal(SIDroot,fp);
    fclose(fp);
    return;
}

void loadFile(){
    FILE *fp;
    char* temp;
    temp = calloc(48, sizeof(char));
    fp = fopen("database.bin", "r");
    if (fp == NULL){
        return;
    }


    while(fgets(temp, 48, fp) != NULL) {
        int sid = atoi(strtok(temp, ","));
        char *lName = strtok(NULL, ",");
        char *fName = strtok(NULL, ",");
        char *mi = strtok(NULL, ",");
        double gpa = atof(strtok(NULL, ","));
        put(lName, fName, mi[0], sid, gpa);
    }

    fclose(fp);
    return;


}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    GPAroot = SIDroot = Lnameroot = Fnameroot = NULL;
    loadFile();

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
        if (n < 0) error("ERROR reading from socket");
        printf("Here is the message: %s", buffer);
        if (strncmp(buffer, "get", 3) == 0){
            strtok(buffer, " ");
            char* argument = strtok(NULL, " ");
            if (strcmp(argument, "lname\n") == 0)
                getLname((int) messageSize);
            else if (strcmp(argument, "fname\n") == 0)
                getFname((int) messageSize);
            else if (strcmp(argument, "SID\n") == 0)
                getSID((int) messageSize);
            else if (strcmp(argument, "GPA\n") == 0)
                getGPA((int) messageSize);
            else
                message = "Not a valid argument";
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
            unsigned long sid = (unsigned long) atoi(strtok(NULL, " "));
            if(delete(sid))
                message = "delete successful";
            else
                message = "delete unsuccessful";
        } else
            message = "Not a valid command";
        size_t t = sizeof(char) * strlen(message);
        memset(buffer, 0, 256);
        sprintf(buffer, "%d", (int) t);
        write(newsockfd, buffer, strlen(buffer));
        n = (int) write(newsockfd, message, t);
        memset(buffer, 0, 256);
        if (n < 0) error("ERROR writing to socket");
        n = (int) read(newsockfd, buffer, 255);
    }
    write(newsockfd,"stop",strlen("stop"));
    saveFile();
    return 0;
}
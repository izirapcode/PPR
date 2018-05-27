#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

//Zgłoszenie błędu
void error(char *msg) {
    perror(msg);
    exit(0);
}
//Utworzenie struktury addressu
void makeAddress(struct sockaddr_in *server,char *host,int portNumber){
    struct hostent *serverhost;
    bzero((char *) server, sizeof(server));
    serverhost = gethostbyname( host );
    server->sin_family      = AF_INET;          
    server->sin_port        = htons(portNumber);               
    bcopy( (char *) serverhost->h_addr, (char *) &server->sin_addr.s_addr, serverhost->h_length );
}
//Pętla wysyłania wiadomości
void sendMessage(int s,struct sockaddr_in *server){
    char buf[32];
    while(1){
        bzero( buf, 32 );
        if(read(STDIN_FILENO,buf,32)==1)
        break;
        if(sendto(s, buf, strlen(buf), 0, (struct sockaddr *)server, sizeof(*server))<0){
            error("ERROR sending UDP msg");
            exit(1);
        }
    }
}
//Połączenie portu z socketem
void bindSocket(int s,struct sockaddr_in *server){
    if (bind(s, (struct sockaddr *) server, sizeof(*server)) < 0) 
    error("ERROR on binding");
}
//Pętla odbierania wiadomości
void getMessages(int s,struct sockaddr_in *server){
    char buf[32];
    int size = sizeof(*server);
    while(1){
        bzero( buf, 32 );
        if(recvfrom(s, buf, 32, 0, (struct sockaddr *)server, &size )<0){
            error("ERROR reciving msg");
            exit(1);
        }
        printf("%s\n",buf);
    }
}
int main(int argc, char *argv[]) {
	int s;
    struct sockaddr_in server;
     if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
       error("ERROR opening socket");
       exit(1);
    }
    makeAddress(&server,"127.0.0.1",12345);
    bindSocket(s,&server);
    getMessages(s,&server);
   return 0;
   
}

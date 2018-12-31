#include "./local.h"

int main(int argc, char * argv[])
{
   int socket_servidor, bytes_recebidos;
   struct sockaddr_in servidor;
   char buffer[MAX_SIZE_BUFFER]="Recebeu isso?";

    socket_servidor = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servidor, sizeof(servidor));
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PORT);
    inet_aton(argv[1], &servidor.sin_addr.s_addr);

    connect(socket_servidor, (struct sockaddr*)&servidor, sizeof(servidor));

    send(socket_servidor,buffer,MAX_SIZE_BUFFER,0);
    bytes_recebidos=recv(socket_servidor,buffer,MAX_SIZE_BUFFER,0);
    printf("Cliente recebeu: %s\n",buffer);

    close(socket_servidor);
    return 0;
}


#include "./local.h"

int main(int argc, char * argv[])
{
   int socket_servidor, socket_cliente, tamanho_socket, bytes_recebidos;
   struct sockaddr_in cliente;
   struct sockaddr_in servidor;
   char buffer[MAX_SIZE_BUFFER];

   tamanho_socket=sizeof(struct sockaddr_in);

   socket_servidor = socket(AF_INET, SOCK_STREAM, 0);

   bzero(&servidor, sizeof(servidor));
   servidor.sin_family = AF_INET;
   servidor.sin_port = htons(PORT);
   servidor.sin_addr.s_addr = INADDR_ANY;
   
   bind(socket_servidor, (struct sockaddr *)&servidor, sizeof(servidor));
   
   listen(socket_servidor, 1);
   
   printf("Servidor aguardando mensagens na porta %d\n",PORT);

   while (1)
   {
     socket_cliente = accept(socket_servidor, (struct sockaddr *)&cliente, &tamanho_socket);
      
     bytes_recebidos=recv(socket_cliente,buffer,MAX_SIZE_BUFFER,0);
     buffer[bytes_recebidos]='\0';
     printf("Servidor recebeu: %s.\n",buffer);
     strcpy(buffer,"ACK");
     send(socket_cliente,buffer,MAX_SIZE_BUFFER,0);

     close(socket_cliente);
   }
   
   close(socket_servidor);
   return 0;
}


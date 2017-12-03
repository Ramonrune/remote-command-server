//=============================================================================
// CLIENTE.C 
// Exemplo de uso do mecanismo de comunicação por Socket - UDP
// Programa que envia e recebe uma mensagem para outro processo via socket
// Prof. Dr. Jose Luis Zem
//
// ALUNOS
// 0040481611003 RAMON LACAVA GUTIERREZ GONCALES
// 0040481611046 MARCIO GABBAI GONCALVES
// FACULDADE DE TECNOLOGIA DE AMERICANA ADS 4 SEMESTRE REDES DE COMPUTADORES
//
//=============================================================================

#include "./local.h"
main(int argc, char *argv[])
{
  int socket_servidor,bytes_enviados, bytes_recebidos;
  struct sockaddr_in servidor;
  int tamanho_servidor = sizeof(servidor);
  char buffer[MAX_SIZE_BUFFER]="qualquer coisa ...";
  char novo_buffer[MAX_SIZE_BUFFER]="qualquer coisa ...";

  system("clear");

  socket_servidor = socket(AF_INET, SOCK_DGRAM, 0);

  bzero(&servidor, sizeof(servidor));
  servidor.sin_family        = AF_INET;
  servidor.sin_port          = htons(PORT);
  servidor.sin_addr.s_addr = inet_addr(argv[1]);

  while ( strcmp(buffer,"shutdown") != 0 ) {

      printf("> ");
      gets(buffer);

      if ( strcmp(buffer,"exit") == 0 ) { 
         system("clear");
	 exit (0);
      }

      int client = 0;
      if ( strcmp(buffer,"help") == 0 ) { 
         client = 1;
  	 printf("------------------------------------------------------------------------------------\n");
	 printf("date: {remoto} retornar a data\n");
	 printf("time: {remoto} retornar a hora\n");
	 printf("nodename: {remoto} retornar o nome do no\n");
	 printf("sysname: {remoto} retornar o nome do sistema\n");
	 printf("release: {remoto} retornar a liberacao do sistema\n");
	 printf("version: {remoto} retornar a versao do sistema\n");
	 printf("machine: {remoto} retornar o nome da maquina\n");
	 printf("shutdown: {remoto} encerrar a execucao da aplicacao SERVIDOR\n");
	 printf("credits: {remoto} exibir o nome completo de todos os participantes da equipe\n");
	 printf("exit: {local} encerrar a execucao da aplicacao CLIENTE\n");
	 printf("help: {local} exibir um auxilio sobre os comandos existentes\n");
  	 printf("------------------------------------------------------------------------------------\n");

      }

      if(client == 0){
	  bytes_enviados=sendto(socket_servidor, buffer, MAX_SIZE_BUFFER, 0, (struct sockaddr *)&servidor, sizeof(servidor));
	
	  bytes_recebidos = recvfrom(socket_servidor, novo_buffer,MAX_SIZE_BUFFER, 0, (struct sockaddr *)&servidor, &tamanho_servidor);
	
	  printf("%s.\n", novo_buffer);
      }

  }

  close(socket_servidor);  

  system("clear");

  return 0;
}


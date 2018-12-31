//=============================================================================
// SERVIDOR.C 
// Exemplo de uso do mecanismo de comunicação por Socket - UDP
// Programa que recebe e envia uma mensagem para outro processo via socket
// Prof. Dr. Jose Luis Zem
//
// ALUNOS
// 0040481611003 RAMON LACAVA GUTIERREZ GONCALES
// 0040481611046 MARCIO GABBAI GONCALVES
// FACULDADE DE TECNOLOGIA DE AMERICANA ADS 4 SEMESTRE REDES DE COMPUTADORES
//
//=============================================================================

#include "./local.h"
#include <time.h>
#include <sys/utsname.h>

void date_and_time(char *arr);

void date_and_time(char *arr){
   time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   char dia[12], mes[12], ano[12], hora[12], minuto[12], segundo[12];
   sprintf(dia, "%02d", tm.tm_mday);
   sprintf(mes, "%02d", (tm.tm_mon + 1));
   sprintf(ano, "%02d", (tm.tm_year + 1900));
   sprintf(arr, "%s/%s/%s", dia, mes, ano);
	  
   sprintf(hora, "%02d", (tm.tm_hour));
   sprintf(minuto, "%02d", (tm.tm_min));
   sprintf(segundo, "%02d", (tm.tm_sec));
   strcat(arr, " ");
   strcat(arr, hora);
   strcat(arr, ":");
   strcat(arr, minuto);
   strcat(arr, ":");
   strcat(arr, segundo);

}

main(int argc, char * argv[])
{
  int socket_servidor, socket_cliente, bytes_recebidos, bytes_enviados;
  struct sockaddr_in servidor, cliente;
  int tamanho_cliente = sizeof(cliente);
  int tamanho_servidor = sizeof(servidor);
  char buffer[MAX_SIZE_BUFFER]="qualquer coisa";
  char novo_buffer[MAX_SIZE_BUFFER]="qualquer coisa";

  system("clear");
  
  socket_servidor = socket(AF_INET, SOCK_DGRAM, 0);
  
  bzero(&servidor, sizeof(servidor));
  servidor.sin_family      = AF_INET;
  servidor.sin_port        = htons(PORT);
  servidor.sin_addr.s_addr = htonl(INADDR_ANY);
  
  bind(socket_servidor,(struct sockaddr *)&servidor, tamanho_servidor); 

  printf("Servidor aguardando comandos na porta %d\n", PORT);
  printf("--------------------------------------------\n");

  while ( strcmp(buffer,"shutdown") != 0 ) {
  
      bytes_recebidos = recvfrom(socket_servidor, buffer, MAX_SIZE_BUFFER, 0,(struct sockaddr *)&cliente,&tamanho_cliente);

      printf("Comando Recebido: %s.\n", buffer);

      //strcpy(novo_buffer,"Resposta do seu comando ...");
      int found = 0;
      
      if(strcmp(buffer, "date") == 0){
	   found = 1;
	   time_t t = time(NULL);
	   struct tm tm = *localtime(&t);

	   char dia[12], mes[12], ano[12];
	   sprintf(dia, "%02d", tm.tm_mday);
	   sprintf(mes, "%02d", (tm.tm_mon + 1));
	   sprintf(ano, "%02d", (tm.tm_year + 1900));
           sprintf(novo_buffer, "%s/%s/%s", dia, mes, ano);
	 

	

      }

      if(strcmp(buffer, "time") == 0){
	   found = 1;

	   time_t t = time(NULL);
	   struct tm tm = *localtime(&t);

	   char hora[12], minuto[12], segundo[12];
	   sprintf(hora, "%02d", (tm.tm_hour));
	   sprintf(minuto, "%02d", (tm.tm_min));
	   sprintf(segundo, "%02d", (tm.tm_sec));
          
	   sprintf(novo_buffer, "%s:%s:%s", hora, minuto, segundo);


      }

      if(strcmp(buffer, "nodename") == 0){
	   found = 1;

           struct utsname uts;
	   uname(&uts);
	   strcpy(novo_buffer, uts.nodename);

      }
   
     if(strcmp(buffer, "sysname") == 0){
	   found = 1;

           struct utsname uts;
	   uname(&uts);
	   strcpy(novo_buffer, uts.sysname);

      }

     if(strcmp(buffer, "release") == 0){
	   found = 1;

           struct utsname uts;
	   uname(&uts);
	   strcpy(novo_buffer, uts.release);

      }

     if(strcmp(buffer, "version") == 0){
	   found = 1;

           struct utsname uts;
	   uname(&uts);
	   strcpy(novo_buffer, uts.version);

      }

     if(strcmp(buffer, "machine") == 0){
	   found = 1;

           struct utsname uts;
	   uname(&uts);
	   strcpy(novo_buffer, uts.machine);

      }

     if(strcmp(buffer, "credits") == 0){
	   found = 1;

        
	   strcpy(novo_buffer, "RA: 0040481611003 Ramon Lacava Gutierrez Goncales\nRA: 0040481611046 Marcio Gabbai Goncalves");

      }

      if(found == 0){
	   strcpy(novo_buffer, "Comando nao encontrado");

      }
 
      FILE *fptr;
      fptr = fopen("LOG.txt", "a");

      if(fptr == NULL){
         printf("Um erro ocorreu na criacao/leitura do arquivo LOG.txt");;
      }
      char arr[255];
      date_and_time(arr);
      fprintf(fptr, "%s %s\n", arr, buffer);
      fclose(fptr);


      bytes_enviados = sendto(socket_servidor, novo_buffer,MAX_SIZE_BUFFER, 0, (struct sockaddr *)&cliente, tamanho_cliente);

  }


  close(socket_servidor);  

  printf("\nO servidor esta desligando. Aguarde..... [OK]\n\n");
  
  return 0;
} 

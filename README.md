# Remote-Command-Server

Remote command server using TCP and UDP as transport protocol.
Client interact with server sending some specifics commands and server hold that, process, and send back to client an response. 
The server logs all the commands that were sent by the client.
## Differences between TCP and UDP
![alt text](https://microchip.wdfiles.com/local--files/tcpip:tcp-vs-udp/TCP_vs_UDP.JPG)

## File structure
--udp<br>
|---cliente.c<br>
|---local.h<br>
|---servidor.c<br>

--tcp<br>
|---cliente.c<br>
|---local.h<br>
|---servidor.c<br>

## Structure description

### local.h
Header file that include another headers and specify port and buffer size configurations.

### servidor.h
Server that receive commands and execute then.

### cliente.h
Client that send commands to the server.


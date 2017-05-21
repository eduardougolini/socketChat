#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char** argv) {
	struct sockaddr_in servidor;
	int meusocket, tsocket, numbytes, acceptedSocket;
	int porta = 9900;
	struct hostent *host;
	char buf[256];

	system("clear");
	printf("Iniciando servidor!\n");

	meusocket = socket(AF_INET, SOCK_STREAM, 0);

	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = INADDR_ANY;
	servidor.sin_port = htons(porta);
	memset(&(servidor.sin_zero), 0x00, sizeof(servidor.sin_zero));

	tsocket = sizeof(struct sockaddr_in);

	bind(meusocket, (struct sockaddr *)&servidor, sizeof (struct sockaddr));
	listen(meusocket, 5);
	printf(">> Servidor escutando na porta %d: \n\n", porta);

	while (1) {
		acceptedSocket = accept(meusocket, (struct sockaddr *) &servidor, &tsocket);

		if (!fork()) {
			while(numbytes = recv(acceptedSocket, buf, 256, 0 )) {
				buf[numbytes] = '\0';
				if (send(acceptedSocket, buf, 256, 0) == -1) {
					perror("send");
					close(acceptedSocket);
					exit(0);
				}

				printf("Enviou %s \n", buf);
			}
		}

	}

}

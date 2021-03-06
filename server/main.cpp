#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <vector>

void manageConnections(std::vector<int> *connections, int arrayAddress);

int main (int argc, char** argv) {
    struct sockaddr_in servidor;
    int meusocket, acceptedSocket;
    int porta = 9900;
    struct hostent *host;

    socklen_t tsocket;

    size_t size = 0;
    std::vector<int> connections(size);
    int arrayAddress = -1;
    int n;

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
        arrayAddress++;
        connections.resize(connections.size() + 1);
        connections[arrayAddress] = accept(meusocket, (struct sockaddr *) &servidor, &tsocket);

        std::thread (manageConnections, &connections, arrayAddress).detach();


    }

}

void manageConnections(std::vector<int> *connections, int arrayAddress) {
    int numbytes;
    char buf[256];

    while(numbytes = recv((*connections)[arrayAddress], buf, 256, 0 )) {
        buf[numbytes] = '\0';
        for(int i = 0; i < (connections->size() - 1); i++) {
            if (send((*connections)[i], buf, 256, 0) == -1) {
                perror("send");
                close((*connections)[i]);
                exit(0);
            }
        }

        printf("Enviou %s \n", buf);
    }
}

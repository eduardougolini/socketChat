#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include "mainpage.h"

void connectToServer();

int mySocket;

int main(int argc, char **argv) {
    QApplication app (argc, argv);

    MainPage window;

    window.setWindowTitle(QString::fromUtf8("Chat"));
    window.resize(500, 200);

    window.drawButton();
    window.drawMessagesBox();
    window.drawMessageInput();

//    connectToServer();

    window.showContent();
    return app.exec();
}

void connectToServer() {
        char ip[] = "127.0.0.1";
        int porta = 9901;
        struct sockaddr_in cliente;

        system("clear");
        printf(" Iniciando Cliente\n\n");

        mySocket = socket(AF_INET, SOCK_STREAM, 0);
        cliente.sin_family = AF_INET;
        cliente.sin_addr.s_addr = inet_addr(ip);
        cliente.sin_port = htons(porta);

        memset(&(cliente.sin_zero), 0x00, sizeof(cliente.sin_zero));

        if(connect(mySocket, (struct sockaddr *)&cliente, sizeof(struct sockaddr)) != 0) {
            puts("\n>> Servidor nao encontrado\nO cliente esta encerrado\n");

            exit(0);
        }

        printf(">> A conexao com o servidor %s foi estabelecida na porta %d \n\n", ip, porta);

        //descobrir quando dar o close(cliente);

//    send(int Meusocket, const void *msg, size_t len, int flags);
}

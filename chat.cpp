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
#include <thread>
#include <iostream>
#include <fcntl.h>
#include <netdb.h>
#include "mainpage.h"

#define STDIN 0

void connectToServer(MainPage *window);
void listenSocket(MainPage *window);

int main(int argc, char **argv) {
    QApplication app (argc, argv);

    MainPage window;

    window.setWindowTitle(QString::fromUtf8("Chat"));
    window.resize(500, 300);

    window.drawButton();
    window.drawMessagesBox();
    window.drawMessageInput();
    window.drawUserName();

    window.show();

    connectToServer(&window);
    std::thread (listenSocket, &window).detach();

    return app.exec();
}

void connectToServer(MainPage *window) {
    char ip[] = "127.0.0.1";
    int porta = 9900;
    struct sockaddr_in cliente;

    printf(" Iniciando Cliente\n\n");

    window->mySocket = socket(AF_INET, SOCK_STREAM, 0);
    cliente.sin_family = AF_INET;
    cliente.sin_addr.s_addr = inet_addr(ip);
    cliente.sin_port = htons(porta);
    bzero(&(cliente.sin_zero), 8);


    if(connect(window->mySocket,(struct sockaddr *)&cliente, sizeof(struct sockaddr)) ==-1) {
        puts("\n>> Servidor nao encontrado\nO cliente esta encerrado\n");

        exit(0);
    }

    printf(">> A conexao com o servidor %s foi estabelecida na porta %d \n\n", ip, porta);

}

void listenSocket(MainPage *window) {
    char buf[256];
    int numbytes;

    while(true) {
        if((numbytes = recv(window->mySocket, buf, 256, 0 )) == -1) {
            perror("recv");
            exit(0);
        } else {
            printf("oloco");
            buf[numbytes] = '\0';

            printf("recebi dados %s", buf);

            QString username = window->userNameObj->text();

            window->messagesBox->append(username + QString(" >> ") + QString(buf));
        }
    }
}

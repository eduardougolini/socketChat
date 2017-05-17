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
#include "mainpage.h"

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
    window.drawCloseSocketButton();

    window.show();

    connectToServer(&window);

    //std::thread(listenSocket, &window).join();

    return app.exec();
}

void listenSocket(MainPage *window) {
    char buf[256];
    int numbytes;

    while(numbytes = recv(window->mySocket, buf, 256, 0 )) {

        buf[numbytes] = '\0';

        QString oldText = window->messagesBox->toPlainText();
        window->messagesBox->setText(oldText + "\n" + buf);
    }
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

    memset(&(cliente.sin_zero), 0x00, sizeof(cliente.sin_zero));

    if(connect(window->mySocket, (struct sockaddr *)&cliente, sizeof(struct sockaddr)) != 0) {
        puts("\n>> Servidor nao encontrado\nO cliente esta encerrado\n");

        exit(0);
    }

    printf(">> A conexao com o servidor %s foi estabelecida na porta %d \n\n", ip, porta);

}

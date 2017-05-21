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
#include <sstream>
#include "mainpage.h"

void connectToServer(MainPage *window, std::string ip);
void listenSocket(MainPage *window);

int main(int argc, char **argv) {
    QApplication app (argc, argv);

    MainPage window;

    std::string ip = "";

    std::cout << "Insira o ip do servidor: ";
    std::getline(std::cin, ip);

    window.setWindowTitle(QString::fromUtf8("Chat"));
    window.resize(500, 300);

    window.drawButton();
    window.drawMessagesBox();
    window.drawMessageInput();
    window.drawUserName();

    window.show();

    connectToServer(&window, ip);
    std::thread (listenSocket, &window).detach();

    return app.exec();
}

void connectToServer(MainPage *window, std::string ipString) {
    const char* ip = ipString.c_str();
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
            buf[numbytes] = '\0';
            window->messagesBox->append(QString(buf));
        }
    }
}

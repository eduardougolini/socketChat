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

void drawButton(QWidget *window);
void drawMessagesBox(QWidget *window);
void drawMessageInput(QWidget *window);
void connectToServer();

QTextEdit *messagesBox;
QTextEdit *messageInput;

int main(int argc, char **argv) {
    QApplication app (argc, argv);
    QWidget window;
    window.setFixedSize(500, 200);

    drawButton(&window);
    drawMessagesBox(&window);
    drawMessageInput(&window);

    connectToServer();

    window.show();
    return app.exec();
}

void drawButton(QWidget *window) {
    QPushButton *button = new QPushButton("Enviar", window);
    button->setGeometry(410, 160, 80, 30);
}

void drawMessagesBox(QWidget *window) {
    messagesBox = new QTextEdit(window);
    messagesBox->setGeometry(10, 10, 480, 140);
}

void drawMessageInput(QWidget *window) {
    messageInput = new QTextEdit(window);
    messageInput->setGeometry(10, 160, 400, 30);
}

void connectToServer() {

    char ip[] = "127.0.0.1";
    int meusocket;
    int porta = 9900;
    struct sockaddr_in cliente;

    system("clear");
    printf(" Iniciando Cliente\n\n");

    meusocket = socket(AF_INET, SOCK_STREAM, 0);
    cliente.sin_family = AF_INET;
    cliente.sin_addr.s_addr = inet_addr(ip);
    cliente.sin_port = htons(porta);

    memset(&(cliente.sin_zero), 0x00, sizeof(cliente.sin_zero));

    if(connect(meusocket, (struct sockaddr *)&cliente, sizeof(struct sockaddr)) != 0) {
        puts("\n>> Servidor nao encontrado\nO cliente era encerrado\n");

        exit(0);
    }

    printf(">> A conexao com o servidor %s foi estabelecida na porta %d \n\n", ip, porta);

}

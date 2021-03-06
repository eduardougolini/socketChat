#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QString>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>

class MainPage: public QMainWindow
{
    Q_OBJECT

public:
    MainPage(){}
    ~ MainPage(){}

    QTextEdit *messagesBox;
    QTextEdit *messageInput;
    QLineEdit *userNameObj;
    int mySocket;

    void drawButton() {
        QPushButton *button = new QPushButton("Enviar", this);
        button->setGeometry(410, 160, 80, 30);

        QObject::connect(button, SIGNAL(clicked()), this, SLOT(clickedButton()));
    }

    void drawMessagesBox() {
        messagesBox = new QTextEdit(this);
        messagesBox->setGeometry(10, 10, 480, 140);
    }

    void drawMessageInput() {
        messageInput = new QTextEdit(this);
        messageInput->setGeometry(10, 160, 400, 30);
    }

    void drawUserName() {
        userNameObj = new QLineEdit(this);
        userNameObj->setGeometry(10, 200, 400, 30);
        userNameObj->setPlaceholderText(QString("Nome de usuário"));
    }

public slots:
    void clickedButton() {
        QString toSendMessage = messageInput->toPlainText();
        QString username = userNameObj->text();
        const char* convertedToSendMessage = new char[256];
        strcpy(const_cast<char*>(convertedToSendMessage), username.toStdString().c_str());
        strcat(const_cast<char*>(convertedToSendMessage), " >> ");
        strcat(const_cast<char*>(convertedToSendMessage), toSendMessage.toStdString().c_str());

        if (send(mySocket, convertedToSendMessage, 256, 0) == -1) {
            perror("send");
            ::close(mySocket);
            exit(0);
        }

        messageInput->setText("");
    }
};
#endif

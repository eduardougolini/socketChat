#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QTextEdit>
#include <string>

class MainPage: public QMainWindow
{
    Q_OBJECT

public:
    MainPage(){}
    ~ MainPage(){}

    QTextEdit *messagesBox;
    QTextEdit *messageInput;

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

    void showContent() {
        show();
    }

public slots:
    void clickedButton() {
        QString oldMessage = messagesBox->toPlainText();
        QString newMessage = messageInput->toPlainText();
        messagesBox->setText(oldMessage + newMessage + "\n");

        messageInput->setText("");
    }
};
#endif

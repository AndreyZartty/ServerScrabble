#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <json-c/json.h>
#include <json-c/debug.h>
#include <json-c/json_object.h>

#define PORT 3550
#define MAXDATASIZE 1000

string MainWindow::getCodigo() {
    return "0001";
}

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::SendJson(string boton)
{
    char* str;
    int fd, numbytes;
    struct sockaddr_in client;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    char buf[MAXDATASIZE];

    struct hostent *he;

    if (fd < 0)
    {
        printf("Error : Could not create socket\n");
        return 1;
    }
    else
    {
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);
        client.sin_addr.s_addr = inet_addr("192.168.100.17");
        memset(client.sin_zero, '\0', sizeof(client.sin_zero));
    }

    if (::connect(fd, (const struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("ERROR connecting to server\n");
        return 1;
    }

    json_object *jobj = json_object_new_object();


    json_object *jstringCodigo = json_object_new_string(getCodigo().c_str());
    json_object *jstring = json_object_new_string(boton.c_str());


    json_object_object_add(jobj,"CODIGO", jstringCodigo);
    json_object_object_add(jobj,"BOTON", jstring);



    if (strcpy(buf, json_object_to_json_string(jobj)) == nullptr) {
        printf("ERROR strcpy()");
        exit(-1);
    }

    if (write(fd, buf, strlen(buf)) == -1)
    {
        printf("ERROR write()");
        exit(-1);
    }

    printf("Written data\n");

    memset(buf, 0, MAXDATASIZE);

    ::close(fd);
}

void MainWindow::test(){
    cout << "Test" << endl;
}

void MainWindow::on_iniciarButton_clicked() {
    SendJson("Iniciar");
}

void MainWindow::on_comenzarButton_clicked() {
    SendJson("Comenzar");
}

void MainWindow::on_scrabbleButton_clicked() {
    SendJson("Scrabble!");
}

void MainWindow::on_pasarButton_clicked() {
    SendJson("Pasar");
}

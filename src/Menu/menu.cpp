#include "menu.h"
#include "./ui_menu.h"
#include <iostream>
#include <string>

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_joinMatchButton_clicked()
{
    QString item = ui->listWidget->currentItem()->text();
    //send "unirse" + item
    ui->textBrowser->setText("uniendose a " + item);
}

void Menu::on_createButton_clicked()
{
    QString name = ui->matchNameInput->toPlainText();
    name += " 1/";
    name += ui->nPlayers->text();
    ui->listWidget->addItem(name);
}

void Menu::on_refreshButton_clicked()
{
    //send "listar" to server
    //refresh listWidget  ui->listWidget->addItems();

}

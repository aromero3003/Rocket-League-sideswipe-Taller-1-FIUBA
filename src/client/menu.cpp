#include "menu.h"
#include "./ui_menu.h"


Menu::Menu(Socket* s, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->socket = s;
}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_joinMatchButton_clicked(){
    //GET MATCH NAME FROM LIST
    QString item = ui->listWidget->currentItem()->text();
    std::string aux = item.toStdString();
    std::string match = aux.substr(0, aux.find_last_of(" ")); //GET RID OF PLAYERS/TOTAL FROM STRING

    //SEND "UNIRSE " + MATCH NAME
    bool was_closed = false;
    std::string command = "UNIR " + match;
    int8_t length = command.size();
    this->socket->sendall(&length,1, &was_closed);
    this->socket->sendall(&(command[0]),length, &was_closed);


    //receive error code
    length = 0;
    this->socket->recvall(&length, sizeof(length), &was_closed);
    std::vector<char> buff;
    buff.resize(length);
    this->socket->recvall(buff.data(), length, &was_closed);
    std::string sresp(buff.data(), buff.size());
    if(sresp == "OK"){
         QApplication::exit();
    } else {
        // LA PARTIDA ESTA LLENA
    }

}

void Menu::on_createButton_clicked()
{
    bool was_closed = false;
    //CREATE STRING TO SEND
    QString name = "CREAR " + ui->nPlayers->text() + " " + ui->matchNameInput->toPlainText();
    
    //SEND "CREAR ", MATCH NAME AND N PLAYERS
    int8_t length = name.size();
    this->socket->sendall(&length,1, &was_closed);
    std::cout << name.toStdString() << std::endl;
    this->socket->sendall(&(name.toStdString()[0]),length, &was_closed);

    //RECEIVE ERROR CODE
    length = 0;
    this->socket->recvall(&length, sizeof(length), &was_closed);
    std::vector<char> buff;
    buff.resize(length);
    this->socket->recvall(buff.data(), length, &was_closed);
    std::string sresp(buff.data(), buff.size());
    if(sresp == "OK"){
         QApplication::exit();
    } else {
        // YA EXISTE PARTIDA CON ESE NOMBRE
    }
}

void Menu::on_refreshButton_clicked(){
    //SEND "LISTAR" TO SERVER
    bool was_closed = false;
    std::string listar_command = "LISTAR";
    int8_t length = listar_command.size();
    this->socket->sendall(&length,1, &was_closed);
    this->socket->sendall(&(listar_command[0]),length, &was_closed);
    
    //RECEIVE ALL MATCHES IN STRING
    length = 0;
    this->socket->recvall(&length, sizeof(length), &was_closed);
    std::vector<char> buff;
    buff.resize(length);
    this->socket->recvall(buff.data(), length, &was_closed);
    std::string sresp(buff.data(), buff.size());

    //CLEAR LIST OF MATCHES
    ui->listWidget->clear();

    //ADD MATCHES TO QtListWidget
    std::istringstream f(sresp);
    std::string match;
    std::getline(f, match);

    while(std::getline(f, match)){
        QString qstr = QString::fromStdString(match);
        ui->listWidget->addItem(qstr);
    }
}


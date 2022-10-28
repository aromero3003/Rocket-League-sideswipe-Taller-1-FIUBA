#include "ComandHandler.h"

ComandHandler::ComandHandler() { comand = nullptr; }

ComandHandler::~ComandHandler() {
  if (comand) delete comand;
}

void ComandHandler::createComand(std::istream& parameters) {
  std::string type;
  parameters >> type >> std::ws;

  if (type == "LISTAR") {
    comand = new ComandList();
  } else if (type == "CREAR") {
    comand = new ComandCreate(parameters);
  } else if (type == "UNIR") {
    comand = new ComandAdd(parameters);
  } else {
    throw std::invalid_argument("tipo de comando no encontrado :" + type);
  }
}

void ComandHandler::run(GameHandler& games) {
  if (comand != nullptr) comand->run(games);
}

std::string& ComandHandler::getResponse() { return comand->getResponse(); }

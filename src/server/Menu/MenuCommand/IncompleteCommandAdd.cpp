#include "IncompleteCommandAdd.h"
IncompleteCommandAdd::IncompleteCommandAdd(std::istream& o_paramenters):
   CommandWithParameters(),paramenters(o_paramenters) {}
void IncompleteCommandAdd::run(GameHandler &games) {
  //deveria tirar error
  //
}
std::istream& IncompleteCommandAdd::getParameters(){
    return this->paramenters;
}

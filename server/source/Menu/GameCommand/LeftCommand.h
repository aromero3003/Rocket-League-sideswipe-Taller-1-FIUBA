#ifndef __LEFTCOMMAND_H__
#define __LEFTCOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class LeftCommand: public GameCommand
{
private:
   
public:
  LeftCommand():GameCommand(){}
  void run(GameLogic& gameLogic) override;
  virtual ~LeftCommand(){}
};
#endif

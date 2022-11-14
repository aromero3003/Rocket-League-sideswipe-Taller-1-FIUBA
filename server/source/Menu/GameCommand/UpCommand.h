#ifndef __UPCOMMAND_H__
#define __UPCOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class UpCommand: public GameCommand
{
private:
   
public:
  UpCommand():GameCommand(id){}
  void run(GameLogic& gameLogic) override;
  virtual ~UpCommand(){}
};
#endif

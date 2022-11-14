#ifndef __DOWNCOMMAND_H__
#define __DOWNCOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class DownCommand: public GameCommand
{
private:
   
public:
  DownCommand():GameCommand(){}
  void run(GameLogic& gameLogic) override;
  virtual ~DownCommand(){}
};
#endif

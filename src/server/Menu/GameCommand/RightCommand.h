#ifndef __RIGHTCOMMAND_H__
#define __RIGHTCOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class RightCommand: public GameCommand
{
private:
   
public:
  RightCommand(size_t id);
  void run(GameLogic& gameLogic) override;
  virtual ~RightCommand(){}
};
#endif

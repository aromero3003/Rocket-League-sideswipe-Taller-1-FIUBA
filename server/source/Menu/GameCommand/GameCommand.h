#ifndef __GAMECOMMAND_H__
#define __GAMECOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../Games/GameLogic.h"
class GameCommand
{
private:
   
public:
  GameCommand()=default;
  virtual void run(GameLogic& gameLogic) =0;
  virtual ~GameCommand()=default;
};
#endif

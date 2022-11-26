
#ifndef __BADGAMECOMMAND_H__
#define __BADGAMECOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class BadGameCommand: public GameCommand {
public:
  BadGameCommand(size_t id);
  void run(GameLogic& gameLogic) override;
  virtual ~BadGameCommand(){}
};

#endif

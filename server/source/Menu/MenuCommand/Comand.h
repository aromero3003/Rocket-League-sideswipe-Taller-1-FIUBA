#ifndef __COMAND_H__
#define __COMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../../Game/GameHandler.h"

class Comand {
 protected:
  std::string response;

 public:
  Comand() : response() {}
  std::string& getResponse();
  virtual void run(GameHandler& gameHandler) = 0;
  virtual ~Comand() {}
};
// LIST
class ComandList : public Comand {
 public:
  ComandList() : Comand() {}
  void run(GameHandler& gameHandler) override;
  virtual ~ComandList() {}
};

class ComandWithParameters : public Comand {
 protected:
  std::string gameName;

 public:
  ComandWithParameters() : Comand(), gameName() {}
  virtual void run(GameHandler& gameHandler) override{};
  virtual ~ComandWithParameters() {}
};

////ADD
class ComandAdd : public ComandWithParameters {
 public:
  explicit ComandAdd(std::istream& paramenters);
  void run(GameHandler& gameHandler) override;
  virtual ~ComandAdd() {}
};

// CREATE
class ComandCreate : public ComandWithParameters {
 private:
  int capacity;

 public:
  explicit ComandCreate(std::istream& paramenters);
  void run(GameHandler& gameHandler) override;
  virtual ~ComandCreate() {}
};

#endif

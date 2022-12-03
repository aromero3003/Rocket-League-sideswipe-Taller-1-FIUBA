#ifndef __GMCEx_H__
#define __GMCEx_H__

#include <stdexcept>
#include <string>

class MenuCommandEx : public std::exception {
 public:
  MenuCommandEx() {}
  char* what() { return nullptr; }
};
#endif


#include "Snap.h"

#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstdint>
#include <vector>

SnapShot::SnapShot() {}

void SnapShot::add(float f) {
  unsigned char const *p = reinterpret_cast<unsigned char const *>(&f);
  for (std::size_t i = 0; i != sizeof(float); ++i) {
    this->data.push_back(p[i]);
  }
}

void SnapShot::add(uint8_t x) { this->data.push_back(x); }
bool SnapShot::isGoal() { return data[3]; }
bool SnapShot::isTimeZero() {
  return data[0] == 0; }
void SnapShot::setGoalTrue() { data[3]= true; }
std::vector<uint8_t> &SnapShot::getMsg() { return data; }

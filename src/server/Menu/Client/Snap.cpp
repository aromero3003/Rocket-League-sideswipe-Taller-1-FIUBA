
#include "Snap.h"

#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstdint>
#include <vector>

SnapShot::SnapShot() {}

void SnapShot::add(uint32_t f) {
  unsigned char const *p = reinterpret_cast<unsigned char const *>(&f);
  for (std::size_t i = 0; i != sizeof(uint32_t); ++i) {
    this->data.push_back(p[i]);
  }
}

void SnapShot::add(uint8_t x) { this->data.push_back(x); }

std::vector<uint8_t> &SnapShot::getMsg() { return data; }

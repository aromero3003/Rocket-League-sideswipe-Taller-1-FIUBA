
#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <vector>
#include "Snap.h"

void SnapShot::add(const float &f) {


unsigned char const * p = reinterpret_cast<unsigned char const *>(&f);

for (std::size_t i = 0; i != sizeof(float); ++i)
{
   this->data.push_back(p[i]);
}
        
}
void SnapShot::add(const uint8_t &x) {
        this->data.push_back(x);
}

std::vector<uint8_t> &SnapShot::getMsg() {
    return data;
}


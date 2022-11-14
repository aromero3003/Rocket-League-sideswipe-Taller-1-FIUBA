
#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <vector>
#include "Snap.h"

void SnapShot::add(const float &x) {
    uint32_t *float_addr_as_int_addr = (uint32_t *)&x;

    uint32_t float_converted = htonl(*float_addr_as_int_addr);
    for(int i = 0; i < 4; i++)
        this->data.push_back(((uint8_t *)&float_converted)[i]);
}
void SnapShot::add(const uint8_t &x) {
        this->data.push_back(x);
}

std::vector<uint8_t> &SnapShot::getMsg() {
    return data;
}


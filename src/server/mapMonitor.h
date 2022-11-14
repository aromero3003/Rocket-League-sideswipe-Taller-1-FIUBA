#ifndef MAPMONITOR_H
#define MAPMONITOR_H

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include "car.h"

class MapMonitor {
private:
    std::map<int, Car> cars;
    std::mutex mutex;

    bool contains(int key);

public:
    MapMonitor();

    void new_car(int i);

    ~MapMonitor();
};

#endif
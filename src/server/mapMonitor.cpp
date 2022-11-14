#include "mapMonitor.h"
#include <string>
using std::string;

MapMonitor::MapMonitor(){}

bool MapMonitor::contains(int key){
        return cars.find(key) != cars.end();
}

void MapMonitor::new_car(int i){
        Car car;
        this->cars[i] = car;
}

MapMonitor::~MapMonitor(){}

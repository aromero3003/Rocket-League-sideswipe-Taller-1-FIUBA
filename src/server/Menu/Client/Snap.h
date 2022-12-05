
#ifndef __SNAPSHOT_H__
#define __SNAPSHOT_H__

#include <cstdint>
#include <vector>

class SnapShot {
 private:
  std::vector<uint8_t> data;

 public:
  SnapShot();
  void add(uint8_t x);
  void add(float x); 
  bool isGoal();
  bool isTimeZero();
  void setGoalTrue();
  std::vector<uint8_t> &getMsg();
};

#endif  //  __SNAPSHOT_H__

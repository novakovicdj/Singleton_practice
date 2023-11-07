#ifndef _singleton_h_
#define _singleton_h_

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "my_logger.h"

using namespace std;

class MySingleton {
 private:
  MySingleton();
  // vector for number of accesses at each index
  vector<int> access;
  // history of thread ids at each index
  map<int, vector<thread::id>> thread_ids;
  static mutex mtx;
  static MyLogger my_logg;

 public:
  // prevent copying of singleton
  MySingleton(MySingleton &single) = delete;
  MySingleton &operator=(MySingleton &) = delete;

  static MySingleton &getInstance();

  void updateAccess(int num);
  void printAccessStatistics();
};

#endif
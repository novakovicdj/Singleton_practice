#include "singleton.h"

#define ACCESS_INDEXES 10

mutex MySingleton::mtx;

MySingleton::MySingleton() {
  // initialize these two vectores
  for (int i = 0; i < ACCESS_INDEXES; i++) {
    this->access.push_back(0);
    this->thread_ids.insert(make_pair(i, vector<thread::id>({})));
  }
}

MySingleton& MySingleton::getInstance() {
  // lock_guard<mutex> lock(mtx);
  // static variable so that only one copy of it exists
  static MySingleton singletonInstance;

  return singletonInstance;
}

void MySingleton::updateAccess(int num) {
  cout << this_thread::get_id() << " | ";
  // print message dependent of number of accesses before
  if (this->access[num] == 0) {
    cout << "No threads accessed index " << num << " before" << endl;
  } else {
    cout << this->access[num] << " thread(s) has accessed index " << num
         << " before: " << endl;
    for (auto& it : this->thread_ids[num]) {
      cout << "Th" << it << " ";
    }
    cout << endl;
  }
  // update number of accesses and add to access history
  // at the suitable index
  this->access[num]++;
  this->thread_ids[num].push_back(this_thread::get_id());
}

void MySingleton::printAccessStatistics() {
  cout << "--------------------"
       << "Access statistics"
       << "--------------------" << endl;
  // some prettier printing of those statistics
  for (int i = 0; i < ACCESS_INDEXES; i++) {
    cout << "\t" << this->access[i] << " accesses at the index " << i << endl;
    cout << "Access hisotry: ";
    for (auto& it : this->thread_ids[i]) {
      cout << "Th" << it << " ";
    }
    cout << endl;
  }
}

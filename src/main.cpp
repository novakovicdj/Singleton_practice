#include <thread>

#include "singleton.h"
#define NUM_OF_ITERATIONS 8
using namespace std;

mutex mtx_cout;

void printSingletonAddress() { cout << &(MySingleton::getInstance()) << endl; }

void t_body() {
  int num = 0;
  hash<thread::id> hasher;
  // calculate seed for rand based on threads id
  int seed = hasher(this_thread::get_id());
  srand(seed);
  mtx_cout.lock();
  cout << "Thread " << this_thread::get_id() << " is using singleton: ";
  // to see that every thread uses the same copy
  printSingletonAddress();
  mtx_cout.unlock();
  this_thread::sleep_for(500ms);
  // simulate accesses at random indexes for NUM_OF_ITERATIONS times
  for (int i = 0; i < NUM_OF_ITERATIONS; i++) {
    num = rand() % 10;
    mtx_cout.lock();
    MySingleton::getInstance().updateAccess(num);
    mtx_cout.unlock();
    // to slow down execution a little bit
    this_thread::sleep_for(500ms);
  }
}

int main() {
  thread t1(t_body);
  thread t2(t_body);
  thread t3(t_body);
  thread t4(t_body);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  MySingleton::getInstance().printAccessStatistics();

  return 0;
}

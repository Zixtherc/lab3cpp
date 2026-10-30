#include "work.h"

#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

void f(char x, int i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::osyncstream(std::cout) << "З набору " << x << " виконано дію " << i << ".\n";
}

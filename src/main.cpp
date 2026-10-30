#include <chrono>
#include <iomanip>
#include <iostream>
#include <latch>
#include <syncstream>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include "schedule.h"
#include "work.h"

using namespace std;

latch latch_a(7), latch_b(8), latch_c(8), latch_d(9), latch_e(8);
latch latch_g(5), latch_h(4), latch_i(8), latch_j(8), latch_k(4);

void wait_for_dependencies(char set) {
    switch (set) {
    case 'b': case 'c': case 'd':
        latch_a.wait();
        break;
    case 'e':
        latch_b.wait();
        break;
    case 'g': case 'h':
        latch_c.wait();
        break;
    case 'i':
        latch_d.wait();
        break;
    case 'j':
        latch_e.wait();
        latch_g.wait();
        break;
    case 'k':
        latch_h.wait();
        latch_i.wait();
        break;
    default:
        break;
    }
}

void action_done(char set) {
    switch (set) {
    case 'a': latch_a.count_down(); break;
    case 'b': latch_b.count_down(); break;
    case 'c': latch_c.count_down(); break;
    case 'd': latch_d.count_down(); break;
    case 'e': latch_e.count_down(); break;
    case 'g': latch_g.count_down(); break;
    case 'h': latch_h.count_down(); break;
    case 'i': latch_i.count_down(); break;
    case 'j': latch_j.count_down(); break;
    case 'k': latch_k.count_down(); break;
    default: break;
    }
}

void worker(int id) {
    for (const Task& t : PLANS[id]) {
        wait_for_dependencies(t.set);
        f(t.set, t.num);
        action_done(t.set);
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    osyncstream(cout) << "Обчислення розпочато.\n";
    auto start = chrono::steady_clock::now();

    vector<jthread> threads;
    for (int id = 0; id < NT; id++) {
        threads.emplace_back(worker, id);
    }
    for (auto& th : threads) {
        th.join();
    }

    chrono::duration<double> elapsed = chrono::steady_clock::now() - start;
    osyncstream(cout) << "Обчислення завершено. Тривалість обчислення "
                      << fixed << setprecision(2) << elapsed.count() << " секунд.\n";
}

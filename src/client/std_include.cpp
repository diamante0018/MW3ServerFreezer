#include "std_include.hpp"

extern "C" {
int s_read_arc4random(void*, std::size_t) { return -1; }

int s_read_getrandom(void*, std::size_t) { return -1; }

int s_read_urandom(void*, std::size_t) { return -1; }

int s_read_ltm_rng(void*, std::size_t) { return -1; }
}

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t counter = 0;

extern void cost_inc() { ++counter; }

extern uint64_t cost_read() { return counter; }

extern void exit_print_hook() {
  printf("[COST] %lu\n", counter);
  fflush(stdout);
}

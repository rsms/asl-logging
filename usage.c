#include "logging.h"

// This code is released in the Public Domain (no restrictions, no support 100% free).

int main(int argc, char * const *argv) {
  log_asl_client = asl_open(NULL, "com.your.program", 0);
  
  // -- your code here --
  
  asl_close(log_asl_client);
  return 0;
}

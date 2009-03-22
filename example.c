#include <stdio.h>  /* fprintf() */
#include <getopt.h> /* getopt_long() */
#include <stdlib.h> /* exit() */
#include <stdint.h> /* uint32_t */

#include "logging.h"

// This code is released in the Public Domain (no restrictions, no support 100% free).

static void usage(const char* prog) {
  fprintf(stderr,
          "usage: %s [options]\n"
          "ASL logging example program.\n"
          "Options:\n"
          "  -d/--debug       Enable sending INFO and DEBUG messages. Remote configuration\n"
          "                   may override this.\n"
          "  -s/--stderr      Enable printing log messages to stderr.\n"
          "  -n/--no-remote   Disable logging to syslog server. Only makes sense in\n"
          "                   combination with --stderr.\n"
          "  -h/--help        Print this help message and exit.\n"
          ,prog);
}


int main(int argc, char * const *argv) {
  uint32_t client_opts, send_level;
  const char *identity, *facility;
  
  // ASL client options
  client_opts = 0;
  
  // What level of messages are sent to syslogd
  send_level = ASL_LEVEL_NOTICE;
  
  // Sender identity. This should be NULL, as asl_open() will set this to the
  // name of the program. Only set this if you really need to.
  identity = NULL;
  
  // This should be your UTI
  facility = "se.hunch.asl.example";
  
  // Options accepted by our example program
  int ch;
  static struct option longopts[] = {
    { "debug", no_argument, NULL, 'd' },
    { "stderr", no_argument, NULL, 's' },
    { "no-remote", no_argument, NULL, 'n' },
    { "help", no_argument, NULL, 'h' },
    { NULL, 0, NULL, '\0' }
  };
  
  // Parse options
  while ((ch = getopt_long(argc, argv, "dsnh", longopts, NULL)) != -1) switch (ch) {
    
    case 'd':
      // Send all messages
      send_level = ASL_LEVEL_DEBUG;
      // This disables the remote-control mechanism for adjusting
      // filter levers for processes using e.g. syslog -c ...
      client_opts |= ASL_OPT_NO_REMOTE;
      break;
    
    case 's':
      // Print messages to stderr (adds stderr as an output file descriptor)
      client_opts |= ASL_OPT_STDERR;
      break;
    
    case 'n':
      // Send no messages at all. This does only affect what messages are sent
      // to the server and does not restrict which message are printed to
      // stderr, if enabled.
      send_level = -1;
      break;
    
    // Print usage and help
    default:
      usage(argv[0]);
      exit(1);
  }
  argc -= optind;
  argv += optind;
  
  // Setting ASL_OPT_NO_DELAY connects to the server immediately when calling asl_open()
  client_opts |= ASL_OPT_NO_DELAY;
  
  // Open connection to ASL (log_asl_client is defined in logging.h)
  // See /usr/include/asl.h for more details.
  log_asl_client = asl_open(identity, facility, client_opts);
  // The log_asl_client variable is used by the log_* and Log_* macros in logging.h
  
  // Handle errors from asl_open()
  if (log_asl_client == NULL) {
    perror("asl_open");
    exit(2);
  }
  
  // Set the level for which messages are sent to the server
  log_set_send_filter(send_level);
  
  // Emit one message for each level
  log_emerg("This is a emerg-level message -- this message may propagate "
            "to all TTYs and/or other user interfaces");
  log_alert("This is a alert-level message");
  log_crit("This is a crit-level message");
  log_err("This is a err-level message");
  log_warn("This is a warn-level message");
  log_notice("This is a notice-level message");
  log_info("This is a info-level message");
  log_debug("This message is a debug-level message");
  
  // Close connection to syslogd
  asl_close(log_asl_client);
  
  return 0;
}
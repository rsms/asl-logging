#import "ASLLogger.h"

int main(int argc, char * const *argv) {
  NSAutoreleasePool *autoreleasePool = [[NSAutoreleasePool alloc] init];
  ASLLogger *logger;
  
  // We need to set our facility before aquiring any loggers.
  // Although this is optional, it's highly recommended.
  [ASLLogger setFacility:@"se.notion.asl.objcexample"];
  
  // Aquire a logger for module "my module"
  logger = [ASLLogger loggerForModule:@"my module"];
  
  // Print messages to stderr
  [logger addFileHandle:[NSFileHandle fileHandleWithStandardError]];
  
  // Send all messages (however probably overridden by remote filters)
  logger.connection.level = ASLLoggerLevelDebug;
  
  // Emit one message for each level
  [logger emerg:@"This is a emerg-level message -- this message may propagate "
                @"to all TTYs and/or other user interfaces"];
  [logger alert:@"This is a alert-level message"];
  [logger crit:@"This is a crit-level message"];
  [logger err:@"This is a err-level message"];
  [logger warn:@"This is a warn-level message"];
  [logger notice:@"This is a notice-level message"];
  [logger info:@"This is a info-level message"];
  [logger debug:@"This message is a debug-level message"];
  
  // This is optional
  [ASLLogger releaseLoggers];
  
  [autoreleasePool drain];
  return 0;
}


#import <Foundation/Foundation.h>
#import <asl.h>

#define ASLLoggerLevelEmerg   ASL_LEVEL_EMERG
#define ASLLoggerLevelAlert   ASL_LEVEL_ALERT
#define ASLLoggerLevelCrit    ASL_LEVEL_CRIT
#define ASLLoggerLevelErr     ASL_LEVEL_ERR
#define ASLLoggerLevelWarning ASL_LEVEL_WARNING
#define ASLLoggerLevelNotice  ASL_LEVEL_NOTICE
#define ASLLoggerLevelInfo    ASL_LEVEL_INFO
#define ASLLoggerLevelDebug   ASL_LEVEL_DEBUG

@interface ASLConnection : NSObject {
  uint32_t filter;
@public
  aslclient aslc;
}
@property(assign) uint32_t filter;
@property(assign) uint32_t level;
- (id)initWithOptions:(uint32_t)options;
@end

@interface ASLLogger : NSObject {
  NSString *module;
  ASLConnection *connection;
}

@property(readonly) ASLConnection *connection;

+ (void)setIdentity:(NSString *)s;
+ (void)setFacility:(NSString *)facility;

+ (ASLLogger *)loggerForModule:(NSString *)ident;
+ (ASLLogger *)defaultLogger;
+ (void)releaseLoggerForModule:(NSString *)ident;
+ (void)releaseLoggers;

- (id)initWithModule:(NSString *)module;
- (BOOL)addFileDescriptor:(int)fd;
- (BOOL)addFileHandle:(NSFileHandle *)fh;
- (BOOL)removeFileDescriptor:(int)fd;
- (BOOL)removeFileHandle:(NSFileHandle *)fh;
- (void)emit:(int)level format:(NSString *)format arguments:(va_list)args;

- (void)emerg:(NSString *)format, ...;
- (void)alert:(NSString *)format, ...;
- (void)crit:(NSString *)format, ...;
- (void)error:(NSString *)format, ...;
- (void)err:(NSString *)format, ...;
- (void)warn:(NSString *)format, ...;
- (void)warning:(NSString *)format, ...;
- (void)notice:(NSString *)format, ...;
- (void)info:(NSString *)format, ...;
- (void)debug:(NSString *)format, ...;

@end

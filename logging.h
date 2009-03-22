#ifndef LOGGING_H
#define LOGGING_H
/*
ASL logging convenience functionality.

MACRO        LEVEL         DESCRIPTION
------------ ------------- -------------------------------------------------------------------
log_emerg    Emergency     A serious, unexpected, and often dangerous situation requiring
                           immediate action.
log_alert    Alert         Danger, threat, or problem, typically with the intention of having
                           it avoided or dealt with.
log_crit     Critical      Having the potential to become disastrous; at a point of crisis.
log_err      Error         The state or condition of being wrong in conduct or judgment.
log_warn     Warning       A statement or event that indicates a possible or impending danger,
                           problem, or other unpleasant situation.
log_notice   Notice        The act of notifying, or something by which notice is given.
log_info     Information   Facts provided or learned about something.
log_debug    Debug         Intended for debugging and development. (Only used when building in
                           DEBUG mode).

For logging using NSStrings, the macros begin with a Capital letter L (i.e. Log_notice).

Copyright (c) 2009 Rasmus Andersson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#import <asl.h>
#ifndef ASL_KEY_FACILITY
#   define ASL_KEY_FACILITY "Facility"
#endif

#ifndef __FILENAME__
  #import <string.h>
  #define __FILENAME__ ((strrchr(__FILE__, '/') ?: __FILE__ - 1) + 1)
#endif

#ifdef SRC_MODULE
  #undef SRC_MODULE
#endif
#define SRC_MODULE __FILENAME__

/* Set this yourself using: log_asl_client = asl_open(...) */
extern aslclient log_asl_client;

#define log_set_send_filter(level) asl_set_filter(log_asl_client, ASL_FILTER_MASK_UPTO(level));

#define log1_(int_level, const_chars_fmt, ...) \
  asl_log(log_asl_client, NULL, int_level, "[%s] " const_chars_fmt, SRC_MODULE, ##__VA_ARGS__)
#define log2_(int_level, const_chars_fmt, ...) \
  asl_log(log_asl_client, NULL, int_level, "[%s] " const_chars_fmt " (%s:%d)", \
          SRC_MODULE, ##__VA_ARGS__, __FILENAME__, __LINE__)

#define log_emerg(fmt, ...)  log2_(ASL_LEVEL_EMERG,  fmt, ##__VA_ARGS__)
#define log_alert(fmt, ...)  log2_(ASL_LEVEL_ALERT,  fmt, ##__VA_ARGS__)
#define log_crit(fmt, ...)   log2_(ASL_LEVEL_CRIT,   fmt, ##__VA_ARGS__)
#define log_err(fmt, ...)    log2_(ASL_LEVEL_ERR,    fmt, ##__VA_ARGS__)
#define log_error(fmt, ...)  log2_(ASL_LEVEL_ERR,    fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...)   log1_(ASL_LEVEL_WARNING,fmt, ##__VA_ARGS__)
#define log_notice(fmt, ...) log1_(ASL_LEVEL_NOTICE, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)   log1_(ASL_LEVEL_INFO,   fmt, ##__VA_ARGS__)
#if DEBUG
  #define log_debug(fmt, ...) log2_(ASL_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#else
  #define log_debug(fmt, ...) ((void)0)
#endif

// Objective-C convenience macros
#ifdef __OBJC__
  #define Log1_(int_level, NSString_fmt, ...) \
    asl_log(log_asl_client, NULL, int_level, "[%s] %s", SRC_MODULE, \
            [[NSString stringWithFormat:NSString_fmt, ##__VA_ARGS__] UTF8String])
  #define Log2_(int_level, NSString_fmt, ...) \
    asl_log(log_asl_client, NULL, int_level, "[%s] %s (%s:%d)", SRC_MODULE, \
            [[NSString stringWithFormat:NSString_fmt, ##__VA_ARGS__] UTF8String],\
            __FILENAME__, __LINE__)

  #define Log_emerg(fmt, ...)  Log2_(ASL_LEVEL_EMERG,  fmt, ##__VA_ARGS__)
  #define Log_alert(fmt, ...)  Log2_(ASL_LEVEL_ALERT,  fmt, ##__VA_ARGS__)
  #define Log_crit(fmt, ...)   Log2_(ASL_LEVEL_CRIT,   fmt, ##__VA_ARGS__)
  #define Log_err(fmt, ...)    Log2_(ASL_LEVEL_ERR,    fmt, ##__VA_ARGS__)
  #define Log_error(fmt, ...)  Log2_(ASL_LEVEL_ERR,    fmt, ##__VA_ARGS__)
  #define Log_warn(fmt, ...)   Log1_(ASL_LEVEL_WARNING,fmt, ##__VA_ARGS__)
  #define Log_notice(fmt, ...) Log1_(ASL_LEVEL_NOTICE, fmt, ##__VA_ARGS__)
  #define Log_info(fmt, ...)   Log1_(ASL_LEVEL_INFO,   fmt, ##__VA_ARGS__)
  #if DEBUG
    #define Log_debug(fmt, ...) Log2_(ASL_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
  #else
    #define Log_debug(fmt, ...) ((void)0)
  #endif
#endif

#endif

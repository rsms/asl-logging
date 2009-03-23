# Logging with ASL -- Apple System Logger

## Convenience functions

`logging.h` and `logging.c` includes convenience functionality suitable for
most small-to-medium scale programs. Have a look at `usage.c` for a
minimalistic example or `example.c` for a more complete program.

You can build and test the `example.c` program by running make:

    make
    ./example --help

When logging.h is used in Objective-C, there are an extra set of macros defined for logging with NSStrings and related arguments. These macros begin with a capital letter L (i.e. Log_info).

## Objective-C ASLLogger

The `objc` directory contain a Objective-C OOP library, designed in Apple Foundation fashion. The ASLLogger provide, in contrast to the `logging.h` convenience macros, thread safety. ASLLoggers and ASLConnections are stored in thread-local space. However; passing instances of ASLLogger between threads will cause problems. You should instead aquire new loggers for each thread using `+(ASLLogger *)loggerForModule:(NSString *)m`.

You can build and test the `objc/example.m` program:

    cd objc
    make
    ./example

## About

By [Rasmus Andersson](http://hunch.se/)

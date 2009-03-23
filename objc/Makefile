CFLAGS=-c -Wall -DDEBUG=1
LDFLAGS=-framework Foundation
SOURCES=example.m ASLLogger.m
OBJECTS=$(SOURCES:.m=.o)
EXECUTABLE=example

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

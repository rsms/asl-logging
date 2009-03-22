CFLAGS=-c -Wall -DDEBUG=1
LDFLAGS=
SOURCES=example.c logging.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=example

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

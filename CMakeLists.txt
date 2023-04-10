CC=g++
CFLAGS=-c -Wall
LDFLAGS=

SOURCES=createHashTable.cpp helpers.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=practica1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)


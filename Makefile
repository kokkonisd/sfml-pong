CC = g++
CFLAGS = -Wall -g -std=c++11
SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
CLIBS = -L/usr/local/include/SFML -lsfml-graphics  -lsfml-window -lsfml-system -lsfml-audio
INCDIR = -I/usr/local/include/SFML
TARGET = Pong

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CLIBS) -o $(TARGET)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCDIR) -c $<

%.cc: %.hh

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

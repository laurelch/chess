SOURCES := main.cpp
CC = g++
CPPFLAGS = -std=c++11
chess: 
	$(CC) $(CPPFLAGS) $(SOURCES) -o chess

clean:
	$(RM) chess


CFLAGS = -DDEBUG
SRCS   = main.cpp tree.cpp inst.cpp
OBJS   = $(SRCS:.cpp=.o)
TARGET = ws

default: $(TARGET)

main.o: main.cpp tree.h inst.h Stack.h
	g++ $(CFLAGS) -c main.cpp

tree.o: tree.cpp tree.h
	g++ $(CFLAGS) -c tree.cpp

inst.o: inst.cpp inst.h
	g++ $(CFLAGS) -c inst.cpp

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET)

.PHONY: clean
clean:
	-rm -f *~ *.o

.PHONY: clean_all
clean_all: clean
	-rm -f $(TARGET)


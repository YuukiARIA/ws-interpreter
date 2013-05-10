

CFLAGS = -DDEBUG
SRCS   = main.cpp tree.cpp inst.cpp VM.cpp
OBJS   = $(SRCS:.cpp=.o)
TARGET = ws

default: $(TARGET)

main.o: main.cpp tree.h inst.h VM.h
	g++ $(CFLAGS) -c main.cpp

tree.o: tree.cpp tree.h
	g++ $(CFLAGS) -c tree.cpp

inst.o: inst.cpp inst.h
	g++ $(CFLAGS) -c inst.cpp

VM.o: VM.cpp VM.h inst.h Stack.h Heap.h
	g++ $(CFLAGS) -c VM.cpp

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET)

.PHONY: clean
clean:
	-rm -f *~ *.o

.PHONY: clean_all
clean_all: clean
	-rm -f $(TARGET)


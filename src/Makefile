
CXX    = g++
DEPINC = ./depends.inc
CFLAGS = -DDEBUG -Wall -ansi
SRCS   = main.cpp tree.cpp inst.cpp VM.cpp
OBJS   = $(SRCS:.cpp=.o)
TARGET = ws

.PHONY: default depends clean clean_all

default: $(TARGET)

.cpp.o:
	$(CXX) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

depends:
	$(CXX) -MM $(SRCS) > $(DEPINC)

clean:
	-rm -f *~ *.o

clean_all: clean
	-rm -f $(TARGET)

-include $(DEPINC)


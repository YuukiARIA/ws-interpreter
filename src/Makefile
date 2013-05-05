

CFLAGS = -DDEBUG
SRCS   = main.c tree.c
OBJS   = $(SRCS:.c=.o)
TARGET = wsp

default: $(TARGET)

main.o: main.c tree.h
	gcc $(CFLAGS) -c main.c

tree.o: tree.c tree.h
	gcc $(CFLAGS) -c tree.c

$(TARGET): $(OBJS)
	gcc $(OBJS) -o $(TARGET)

.PHONY: clean
clean:
	-rm -f *~ *.o


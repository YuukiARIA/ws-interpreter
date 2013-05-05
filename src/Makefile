

CFLAGS = -DDEBUG
SRCS   = main.c tree.c inst.c
OBJS   = $(SRCS:.c=.o)
TARGET = ws

default: $(TARGET)

main.o: main.c tree.h
	gcc $(CFLAGS) -c main.c

tree.o: tree.c tree.h
	gcc $(CFLAGS) -c tree.c

inst.o: inst.c inst.h
	gcc $(CFLAGS) -c inst.c

$(TARGET): $(OBJS)
	gcc $(OBJS) -o $(TARGET)

.PHONY: clean
clean:
	-rm -f *~ *.o


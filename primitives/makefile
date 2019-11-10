CC = mpicc
CFLAGS = -Wall

TARGET = 20141510
SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ -lm

$(OBJS) : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<  

main.o : main.c gen_random.h
gen_random.o : gen_random.c gen_random.h

.PHONY: clean  
clean:  
	rm -f *.o $(TARGET)

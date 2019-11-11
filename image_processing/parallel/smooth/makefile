CC = mpicc
CFLAGS = -Wall

TARGET = 20141510
SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^

$(OBJS) : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<  
  
.PHONY: clean  
clean:  
	rm -f *.o $(TARGET)

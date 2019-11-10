CC = gcc
CFLAGS = -Wall -std=c99

TARGET = 20141510
SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^

$(OBJS) : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<  
  
# Generating dependency files
%.d : %.c
	@$(CC) -MM $< > $@
  
# Include dependency file to have gcc recompile necessary sources  
-include $(SRCS:%.c=%.d)
  
.PHONY: clean  
clean:  
	rm -f *.o *.d $(TARGET)

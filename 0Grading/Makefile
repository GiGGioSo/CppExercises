
CC=g++
CFLAGS=-g -Wall
OBJS=grading.o
BIN=grader

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BIN) *.o *.dSYM

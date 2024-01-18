CC = gcc
CFLAGS = -Wall -g

TARGET = shake128
TEST_TARGET = test
SRC = shake128.c utils.c padding.c keccakp.c
TEST_SRC = test.c utils.c padding.c keccakp.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

test: $(TEST_TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(TEST_TARGET): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ) $(TEST_TARGET)

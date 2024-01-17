CC = gcc
CFLAGS = -Wall -g

TARGET = shake128

all: $(TARGET)

$(TARGET): myShake128.c
	$(CC) $(CFLAGS) -o $(TARGET) myShake128.c

clean:
	rm -f $(TARGET)

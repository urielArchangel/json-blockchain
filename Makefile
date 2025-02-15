CC = gcc
CFLAGS = -Wall -Wextra -O2 -lssl -lcrypto -ljson-c -pthread

SRC = main.c blockchain.c transaction.c wallet.c network.c json_storage.c
OBJ = $(SRC:.c=.o)
EXEC = blockchain

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)

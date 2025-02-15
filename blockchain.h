#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <time.h>

#define MAX_HASH_LEN 65
#define DIFFICULTY 4

typedef struct Transaction {
    char sender[256];
    char receiver[256];
    double amount;
    char signature[256]; // Digital signature
    struct Transaction* next;
} Transaction;

typedef struct Block {
    int index;
    time_t timestamp;
    char previous_hash[MAX_HASH_LEN];
    char hash[MAX_HASH_LEN];
    int nonce;
    Transaction* transactions;
    struct Block* next;
} Block;

typedef struct {
    Block* head;
} Blockchain;

Blockchain* create_blockchain();
void add_block(Blockchain* blockchain, Transaction* transactions);
void print_blockchain(Blockchain* blockchain);
void free_blockchain(Blockchain* blockchain);
void mine_block(Block* block);
int validate_block(Block* block, Block* prev_block);

#endif

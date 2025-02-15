#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void compute_hash(int index, time_t timestamp, char* prev_hash, int nonce, char* output_hash) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char input[256];
    snprintf(input, sizeof(input), "%d%ld%s%d", index, timestamp, prev_hash, nonce);
    SHA256((unsigned char*)input, strlen(input), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", hash[i]);
    }
    output_hash[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void mine_block(Block* block) {
    char target[MAX_HASH_LEN] = {0};
    memset(target, '0', DIFFICULTY);
    do {
        block->nonce++;
        compute_hash(block->index, block->timestamp, block->previous_hash, block->nonce, block->hash);
    } while (strncmp(block->hash, target, DIFFICULTY) != 0);
}

Blockchain* create_blockchain() {
    Blockchain* blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    blockchain->head = (Block*)malloc(sizeof(Block));
    blockchain->head->index = 0;
    blockchain->head->timestamp = time(NULL);
    strcpy(blockchain->head->previous_hash, "0");
    blockchain->head->nonce = 0;
    mine_block(blockchain->head);
    blockchain->head->next = NULL;
    return blockchain;
}

void add_block(Blockchain* blockchain, Transaction* transactions) {
    Block* current = blockchain->head;
    while (current->next != NULL) {
        current = current->next;
    }
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->index = current->index + 1;
    new_block->timestamp = time(NULL);
    strcpy(new_block->previous_hash, current->hash);
    new_block->nonce = 0;
    new_block->transactions = transactions;
    mine_block(new_block);
    current->next = new_block;
}

void print_blockchain(Blockchain* blockchain) {
    Block* current = blockchain->head;
    while (current) {
        printf("\nBlock %d\n", current->index);
        printf("Timestamp: %ld\n", current->timestamp);
        printf("Previous Hash: %s\n", current->previous_hash);
        printf("Hash: %s\n", current->hash);
        printf("Nonce: %d\n", current->nonce);
        printf("------------------------------\n");
        current = current->next;
    }
}

void free_blockchain(Blockchain* blockchain) {
    Block* current = blockchain->head;
    while (current) {
        Block* temp = current;
        current = current->next;
        free(temp);
    }
    free(blockchain);
}

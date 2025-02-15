#include "transaction.h"
#include <stdlib.h>
#include <string.h>

Transaction* create_transaction(const char* sender, const char* receiver, double amount, const char* signature) {
    Transaction* transaction = (Transaction*)malloc(sizeof(Transaction));
    strcpy(transaction->sender, sender);
    strcpy(transaction->receiver, receiver);
    transaction->amount = amount;
    strcpy(transaction->signature, signature);
    transaction->next = NULL;
    return transaction;
}

void free_transaction(Transaction* transaction) {
    free(transaction);
}

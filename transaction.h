#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "blockchain.h"

Transaction* create_transaction(const char* sender, const char* receiver, double amount, const char* signature);
void free_transaction(Transaction* transaction);

#endif

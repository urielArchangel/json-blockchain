#ifndef JSON_STORAGE_H
#define JSON_STORAGE_H

#include "blockchain.h"

void save_blockchain(Blockchain* blockchain);
Blockchain* load_blockchain();

#endif

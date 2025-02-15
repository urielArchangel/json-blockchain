#include "json_storage.h"
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_blockchain(Blockchain* blockchain) {
    FILE* file = fopen("blockchain.json", "w");
    if (!file) return;

    json_object* json_chain = json_object_new_array();
    Block* current = blockchain->head;

    while (current) {
        json_object* json_block = json_object_new_object();
        json_object_object_add(json_block, "index", json_object_new_int(current->index));
        json_object_object_add(json_block, "timestamp", json_object_new_int64(current->timestamp));
        json_object_object_add(json_block, "previous_hash", json_object_new_string(current->previous_hash));
        json_object_object_add(json_block, "hash", json_object_new_string(current->hash));
        json_object_object_add(json_block, "nonce", json_object_new_int(current->nonce));

        json_object_array_add(json_chain, json_block);
        current = current->next;
    }

    fprintf(file, "%s", json_object_to_json_string(json_chain));
    fclose(file);
    json_object_put(json_chain);
}

Blockchain* load_blockchain() {
    FILE* file = fopen("blockchain.json", "r");
    if (!file) return create_blockchain();

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    char* data = malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);
    data[fsize] = '\0';

    json_object* json_chain = json_tokener_parse(data);
    free(data);

    Blockchain* blockchain = create_blockchain();
    Block* prev_block = NULL;
    int array_len = json_object_array_length(json_chain);

    for (int i = 0; i < array_len; i++) {
        json_object* json_block = json_object_array_get_idx(json_chain, i);

        Block* new_block = (Block*)malloc(sizeof(Block));
        new_block->index = json_object_get_int(json_object_object_get(json_block, "index"));
        new_block->timestamp = json_object_get_int64(json_object_object_get(json_block, "timestamp"));
        strcpy(new_block->previous_hash, json_object_get_string(json_object_object_get(json_block, "previous_hash")));
        strcpy(new_block->hash, json_object_get_string(json_object_object_get(json_block, "hash")));
        new_block->nonce = json_object_get_int(json_object_object_get(json_block, "nonce"));
        new_block->next = NULL;

        if (prev_block) prev_block->next = new_block;
        else blockchain->head = new_block;
        prev_block = new_block;
    }

    json_object_put(json_chain);
    return blockchain;
}

// main.c - Entry point of the blockchain project
#include "blockchain.h"
#include "transaction.h"
#include "wallet.h"
#include "network.h"
#include "json_storage.h"

int main() {
    Blockchain* blockchain = create_blockchain();

    // Create a wallet
    generate_wallet("private.pem", "public.pem");

    // Create and sign a transaction
    unsigned char signature[256];
    unsigned int sig_len;
    sign_transaction("private.pem", "Alice -> Bob: 10 BTC", signature, &sig_len);

    Transaction* transaction = create_transaction("Alice", "Bob", 10.0, signature);
    add_block(blockchain, transaction);

    // Save blockchain
    save_blockchain(blockchain);

    // Start P2P networking
    start_server();

    print_blockchain(blockchain);
    free_blockchain(blockchain);
    return 0;
}

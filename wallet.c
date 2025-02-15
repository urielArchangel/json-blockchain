#include "wallet.h"
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
#include <openssl/pem.h>
#include <string.h>
#include <stdio.h>

void generate_wallet(char* private_key_file, char* public_key_file) {
    EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_generate_key(key);

    FILE *priv_file = fopen(private_key_file, "w");
    PEM_write_ECPrivateKey(priv_file, key, NULL, NULL, 0, NULL, NULL);
    fclose(priv_file);

    FILE *pub_file = fopen(public_key_file, "w");
    PEM_write_EC_PUBKEY(pub_file, key);
    fclose(pub_file);

    EC_KEY_free(key);
}

void sign_transaction(char* private_key_file, char* data, unsigned char* signature, unsigned int* sig_len) {
    FILE *file = fopen(private_key_file, "r");
    EC_KEY *key = PEM_read_ECPrivateKey(file, NULL, NULL, NULL);
    fclose(file);

    ECDSA_sign(0, (unsigned char*)data, strlen(data), signature, sig_len, key);
    EC_KEY_free(key);
}

int verify_transaction(char* public_key_file, char* data, unsigned char* signature, unsigned int sig_len) {
    FILE *file = fopen(public_key_file, "r");
    EC_KEY *key = PEM_read_EC_PUBKEY(file, NULL, NULL, NULL);
    fclose(file);

    int result = ECDSA_verify(0, (unsigned char*)data, strlen(data), signature, sig_len, key);
    EC_KEY_free(key);

    return result;
}

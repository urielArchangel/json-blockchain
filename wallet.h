#ifndef WALLET_H
#define WALLET_H

void generate_wallet(char* private_key_file, char* public_key_file);
void sign_transaction(char* private_key_file, char* data, unsigned char* signature, unsigned int* sig_len);
int verify_transaction(char* public_key_file, char* data, unsigned char* signature, unsigned int sig_len);

#endif

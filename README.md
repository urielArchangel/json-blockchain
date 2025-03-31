# C-Chain: A Secure and Lightweight Blockchain Implementation in C

## 📌 Project Overview
C-Chain is a fully functional blockchain system written in C, featuring **Proof-of-Work (PoW), digital signatures, peer-to-peer networking, and JSON-based storage**. This project demonstrates the core principles of blockchain technology, including decentralized transaction validation, cryptographic security, and distributed ledger storage.

## 🚀 Features
- **Blockchain Core:** Implements block creation, mining, and validation.
- **Proof-of-Work (PoW):** Blocks are mined using a difficulty-based hashing mechanism.
- **Transactions & Digital Signatures:** Uses elliptic curve cryptography (ECC) for transaction security.
- **Wallet System:** Allows users to generate key pairs, sign transactions, and verify signatures.
- **Peer-to-Peer Networking (P2P):** Nodes communicate and exchange blockchain data.
- **JSON-Based Storage:** The blockchain is persisted and retrieved from a JSON file.
- **Modular Structure:** Clean separation of blockchain, transactions, networking, and storage.

## 🏗️ Project Structure
📂 c-chain ├── blockchain.c # Blockchain logic (PoW, block validation) ├── blockchain.h
├── transaction.c # Transaction system with digital signatures ├── transaction.h ├── wallet.c # Wallet implementation (key generation, signing) ├── wallet.h ├── network.c # Peer-to-peer networking for blockchain nodes ├── network.h ├── json_storage.c # Blockchain storage in JSON format ├── json_storage.h ├── main.c # Entry point for the blockchain node ├── Makefile # Build automation ├── blockchain.json # Stores blockchain data (generated at runtime) ├── README.md # Project documentation

## 🛠️ Installation & Compilation
### 1️⃣ Install Dependencies  
Ensure you have **OpenSSL** and **JSON-C** installed:  
```sh
sudo apt install libssl-dev libjson-c-dev
```

## 2️⃣ Compile the Project
Run the following command:
```sh
make
```
## 3️⃣ Run the Blockchain Node
Start the blockchain application:

```sh
./blockchain
```

## 🔗 Usage
The system starts with a genesis block.
New transactions can be created, signed, and added to blocks.
Blocks are mined using Proof-of-Work before being appended to the blockchain.
Nodes can connect to peers and broadcast blockchain data.
The blockchain is saved and loaded using a JSON file.
🛡️ Security & Validation
Digital Signatures ensure transactions are authentic.
PoW Mining prevents spamming and secures consensus.
Hash Validation ensures data integrity across blocks.
🌟 Future Enhancements
Command-Line Interface (CLI)
Multiple Transactions Per Block
Advanced P2P Network Synchronization
Blockchain Explorer for Visualizing Transactions
🤝 Contributing
Feel free to fork this repository and suggest improvements. Contributions are always welcome!
📜 License
This project is open-source and licensed under the MIT License.

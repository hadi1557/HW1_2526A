#pragma once

#include <string>
#include <fstream>

#include "Transaction.h"

using std::string;
using std::ifstream;
using std::ofstream;

typedef unsigned int (*updateFunction)(unsigned int);

struct Node {
 Transaction transaction;
 string timestamp;
 Node* next;
};

struct BlockChain {
 Node* root;
 Node* tail;
 int size;
};

BlockChain BlockChainInit();

void BlockChainDestroy(BlockChain& blockChain);

int BlockChainGetSize(const BlockChain& blockChain);

int BlockChainPersonalBalance(const BlockChain& blockChain, const string& name);

void BlockChainAppendTransaction(
        BlockChain& blockChain,
        unsigned int value,
        const string& sender,
        const string& receiver,
        const string& timestamp
);

void BlockChainAppendTransaction(
        BlockChain& blockChain,
        const Transaction& transaction,
        const string& timestamp
);

BlockChain BlockChainLoad(ifstream& file);

void BlockChainDump(const BlockChain& blockChain, ofstream& file);

void BlockChainDumpHashed(const BlockChain& blockChain, ofstream& file);

bool BlockChainVerifyFile(const BlockChain& blockChain, std::ifstream& file);

void BlockChainCompress(BlockChain& blockChain);

void BlockChainTransform(BlockChain& blockChain, updateFunction function);

#include <string>
#include <fstream>
#include <vector>

#include "Transaction.h"
#include "BlockChain.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using namespace std;

typedef unsigned int (*updateFunction)(unsigned int);

BlockChain BlockChainInit() {
    BlockChain chain;
    Node* dummy = new Node();
    dummy->transaction.sender = "";
    dummy->transaction.receiver = "";
    dummy->transaction.value = 0;
    dummy->timestamp = "";
    dummy->next = nullptr;

    chain.root = dummy;
    chain.tail = dummy;
    chain.size = 0;

    return chain;
}

void BlockChainDestroy(BlockChain& blockChain) {
    Node* cur = blockChain.root;
    while (cur != nullptr) {
        Node* to_delete = cur;
        cur = cur->next;
        delete to_delete;
    }
    blockChain.root = nullptr;
    blockChain.tail = nullptr;
    blockChain.size = 0;
}

int BlockChainGetSize(const BlockChain& blockChain) {
    return blockChain.size;
}

int BlockChainPersonalBalance(const BlockChain& blockChain, const string& name) {
    int sum = 0;
    Node* cur = blockChain.root->next;

    while (cur != nullptr) {
        if (name == cur->transaction.sender)
            sum -= cur->transaction.value;
        if (name == cur->transaction.receiver)
            sum += cur->transaction.value;
        cur = cur->next;
    }
    return sum;
}

void BlockChainAppendTransaction(BlockChain& blockChain,
                                 unsigned int value,
                                 const string& sender,
                                 const string& receiver,
                                 const string& timestamp) {
    Node* newNode = new Node();
    newNode->transaction.value = value;
    newNode->transaction.sender = sender;
    newNode->transaction.receiver = receiver;
    newNode->timestamp = timestamp;
    newNode->next = nullptr;

    blockChain.tail->next = newNode;
    blockChain.tail = newNode;
    blockChain.size++;
}

void BlockChainAppendTransaction(BlockChain& blockChain,
                                 const Transaction& transaction,
                                 const string& timestamp) {
    BlockChainAppendTransaction(blockChain,
                                transaction.value,
                                transaction.sender,
                                transaction.receiver,
                                timestamp);
}

BlockChain BlockChainLoad(ifstream& file) {
    BlockChain chain = BlockChainInit();

    string sender, receiver, timestamp;
    unsigned int value;

    while (file >> sender >> receiver >> value >> timestamp) {
        BlockChainAppendTransaction(chain, value, sender, receiver, timestamp);
    }

    return chain;
}

void BlockChainDump(const BlockChain& blockChain, ofstream& file) {
    file << "BlockChain Info:" << endl;

    vector<Node*> nodes;
    Node* cur = blockChain.root->next;

    while (cur != nullptr) {
        nodes.push_back(cur);
        cur = cur->next;
    }

    int index = 1;
    for (int i = (int)nodes.size() - 1; i >= 0; --i) {
        file << index++ << "." << endl;
        TransactionDumpInfo(nodes[i]->transaction, file);
        file << "Transaction timestamp: " << nodes[i]->timestamp << endl;
    }
}

void BlockChainDumpHashed(const BlockChain& blockChain, ofstream& file) {
    vector<Node*> nodes;
    Node* cur = blockChain.root->next;

    while (cur != nullptr) {
        nodes.push_back(cur);
        cur = cur->next;
    }

    for (int i = (int)nodes.size() - 1; i >= 0; --i) {
        file << TransactionHashedMessage(nodes[i]->transaction);
        if (i != 0)
            file << endl;
    }
}

bool BlockChainVerifyFile(const BlockChain& blockChain, std::ifstream& file) {
    vector<Node*> nodes;
    Node* cur = blockChain.root->next;

    while (cur != nullptr) {
        nodes.push_back(cur);
        cur = cur->next;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    if (lines.size() != nodes.size())
        return false;

    int n = (int)nodes.size();
    for (int i = 0; i < n; ++i) {
        Node* node = nodes[n - 1 - i];
        if (!TransactionVerifyHashedMessage(node->transaction, lines[i]))
            return false;
    }

    return true;
}

void BlockChainCompress(BlockChain& blockChain) {
    Node* first = blockChain.root->next;
    if (!first) return;

    while (first != nullptr) {
        Node* current = first;
        Node* next = current->next;
        unsigned int sum = current->transaction.value;

        while (next &&
               next->transaction.sender == first->transaction.sender &&
               next->transaction.receiver == first->transaction.receiver) {
            sum += next->transaction.value;
            current = next;
            next = current->next;
        }

        if (current != first) {
            first->transaction.value = sum;
            first->timestamp = current->timestamp;

            Node* del = first->next;
            while (del != next) {
                Node* tmp = del->next;
                delete del;
                del = tmp;
                blockChain.size--;
            }

            first->next = next;
            if (next == nullptr)
                blockChain.tail = first;
        }

        first = first->next;
    }
}

void BlockChainTransform(BlockChain& blockChain, updateFunction function) {
    Node* cur = blockChain.root->next;

    while (cur != nullptr) {
        cur->transaction.value = function(cur->transaction.value);
        cur = cur->next;
    }
}

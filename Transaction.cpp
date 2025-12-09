#include "Utilities.h"
#include "Transaction.h"
#include <fstream>

using std::string;
using std::ofstream;

void TransactionDumpInfo(const Transaction& transaction, ofstream& file) {
    file << "Sender Name: " << transaction.sender << std::endl;
    file << "Receiver Name: " << transaction.receiver << std::endl;
    file << "Transaction Value: " << transaction.value << std::endl;
}

string TransactionHashMessage(const Transaction& transaction) {
    int key = transaction.value;
    const string value1 = transaction.sender;
    const string value2 = transaction.receiver;
    return hash(key, value1, value2);
}

bool TransactionVerifyHashedMessage(const Transaction& transaction, string hashedMessage) {
    string StrValue = TransactionHashMessage(transaction);
    return hashedMessage == StrValue;
}
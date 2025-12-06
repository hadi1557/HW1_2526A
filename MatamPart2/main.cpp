#pragma once

#include <string>
#include <fstream>

using std::string;
using std::ofstream;


/**
*
 * Transaction - Defining the new Transaction Type
 *
*/
struct Transaction {
    unsigned int value;
    string sender;
    string receiver;
};


/**
 * TransactionDumpInfo - Prints the data of the transaction to a given file
 *
 * The data is printed in the following format:
 * Sender Name: <name>
 * Receiver Name: <name>
 * Transaction Value: <value>
 *
 * @param transaction Transaction to print
*/
void TransactionDumpInfo(const Transaction& transaction, ofstream& file) {
 file <<"Sender Name: "<<transaction.sender<< std::endl;
 file <<"Receiver Name: "<<transaction.receiver<< std::endl;
 file <<"Transaction Value: "<<transaction.value<< std::endl;

}


/**
 * TransactionHashMessage - Hashs the message of the transaction
 *
 * @param transaction Transaction to hash
 *
 * @return The hashed message
*/
string TransactionHashedMessage(const Transaction& transaction) {
 string StrValue = std::to_string(transaction.value);
 string hash = transaction.sender + transaction.receiver + StrValue;
 return hash;
}


/**
 * TransactionVerifyHashedMessage - Verifies that a given transaction suits a given hashed message
 *
 * @param transaction Given transaction
 * @param hashedMessage Hashed message to verify
 *
 * @return true if the message given is suitable to this transaction, false otherwise
 *
*/
bool TransactionVerifyHashedMessage(
        const Transaction& transaction,
        string hashedMessage
);
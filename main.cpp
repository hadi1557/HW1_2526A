#include <cstring>
#include <string>
#include <iostream>
#include <fstream>

#include "BlockChain.h"
#include "Utilities.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << getErrorMessage();
        return 0;
    }

    const char* op = argv[1];
    if (strcmp(op, "format") != 0 &&
        strcmp(op, "hash") != 0 &&
        strcmp(op, "compress") != 0 &&
        strcmp(op, "verify") != 0) {
        cerr << getErrorMessage();
        return 0;
    }

    ifstream source(argv[2]);
    if (!source) {
        cerr << "Error opening/closing file for reading.\n";
        return 1;
    }

    BlockChain blockChain = BlockChainLoad(source);

    if (strcmp(op, "format") == 0) {
        ofstream target(argv[3]);
        if (!target) {
            cerr << "Error opening/closing file for reading.\n";
            BlockChainDestroy(blockChain);
            return 1;
        }
        BlockChainDump(blockChain, target);
    } else if (strcmp(op, "hash") == 0) {
        ofstream target(argv[3]);
        if (!target) {
            cerr << "Error opening/closing file for reading.\n";
            BlockChainDestroy(blockChain);
            return 1;
        }
        BlockChainDumpHashed(blockChain, target);
    } else if (strcmp(op, "compress") == 0) {
        ofstream target(argv[3]);
        if (!target) {
            cerr << "Error opening/closing file for reading.\n";
            BlockChainDestroy(blockChain);
            return 1;
        }
        BlockChainCompress(blockChain);
        BlockChainDump(blockChain, target);
    } else if (strcmp(op, "verify") == 0) {
        ifstream target(argv[3]);
        if (!target) {
            cerr << "Error opening/closing file for reading.\n";
            BlockChainDestroy(blockChain);
            return 1;
        }
        if (BlockChainVerifyFile(blockChain, target)) {
            cout << "Verification passed\n";
        } else {
            cout << "Verification failed\n";
        }
    }

    BlockChainDestroy(blockChain);
    return 0;
}

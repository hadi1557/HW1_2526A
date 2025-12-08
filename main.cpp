//
// Created by tmlk1 on 12/8/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BlockChain.h"


int main() {
    BlockChain blockchain = BlockChainInit();
    Transaction tr;
    tr.value = 13;
    tr.sender = "Sender";
    tr.receiver = "Receiver";
    BlockChainAppendTransaction(blockchain, 10,"hamodi", "Kayan","10Dec");
    BlockChainAppendTransaction(blockchain, 2,"Kayan", "Marwan","11Dec");
    BlockChainAppendTransaction(blockchain, 3,"Marwan", "Kayan","12Dec");
     int size =       BlockChainGetSize(blockchain);
    BlockChainAppendTransaction(blockchain,tr, "Test" );
    BlockChainDestroy(blockchain);


}

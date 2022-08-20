#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"

extern uint32_t user_id;
extern ST_database_t accountDB[ACC_DB_MAX_SIZE];
extern ST_transaction_t transData;

void appStart(void) {
    // Load data from database (accountsDB.csv File)
    loadData(accountDB);

    // Set max transaction amount to default value
    transData.terminalData.maxTransAmount = DEFAULT_MAX_TRANSACTION;

    /***  Card Module  ***/
    // Collect User Data
    while(getCardHolderName(&(transData.cardHolderData)) != CARD_OK);
    while(getCardPAN(&(transData.cardHolderData)) != CARD_OK);
    while(getCardExpiryDate(&(transData.cardHolderData)) != CARD_OK);
    
    /***  Terminal Module  ***/
    if (isCardExpired(transData.cardHolderData) == EXPIRED_CARD) {
        printError("Expired Card");
        exit(0);
    }

    while(getTransactionAmount(&(transData.terminalData)) != TERMINAL_OK);
    getTransactionDate(&(transData.terminalData));

    /***  Server Module  ***/
    transData.transState = recieveTransactionData(&transData);

    saveTransaction(&transData);

    if (transData.transState == APPROVED){
        saveAccountData(accountDB);
        printSuccess("Successful Transaction");
    }
}

int main () {
    appStart();
}
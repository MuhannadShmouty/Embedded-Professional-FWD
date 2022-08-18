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

ST_accountsDB_t accountDB[ACC_DB_MAX_SIZE];
ST_transaction_t transData;

void appStart(void) {
    // Load data from database (accountsDB.csv File)
    loadData(accountDB);

    // Set max transaction amount to default value
    transData.terminalData.maxTransAmount = DEFAULT_MAX_TRANSACTION;
    // Check if max transaction value is needed to be changed
    printf("Set maximum transaction Amount? [Default 5000](y/n):");
    char response;

    scanf(" %c", &response);

    //while(response != 'Y' && response != 'y' && response != 'n' && response != 'N');
    if (response == 'y' || response == 'Y'){
        while(setMaxAmount(&(transData.terminalData)) != OK);
    }

    // Collect User Data
    while(getCardHolderName(&(transData.cardHolderData)) != OK);
    while(getCardPAN(&(transData.cardHolderData)) != OK);
    while(getCardExpiryDate(&(transData.cardHolderData)) != OK);


    EN_terminalError_t terminalError = getTransactionAmount(&(transData.terminalData));
    

    getTransactionDate(&(transData.terminalData));
    transData.transState = recieveTransactionData(&transData, accountDB);

    saveTransaction(&transData);

    if (transData.transState == APPROVED){
        saveAccountData(accountDB);
        printSuccess("Successful Transaction");
    }
}

int main () {
    char program_token;

    printf("Perform transaction (T) or get Transaction Data (D)?\n");
    scanf(" %c", &program_token);

    if (program_token == 'T' || program_token == 't') {
        appStart();
    }else if (program_token == 'D' || program_token == 'd') {
        int num;
        printf("Transaction Sequence Number:\n");
        scanf("%d", &num);
        if (getTransaction(num, &transData) == OK) {
            char state[50];
            switch (transData.transState) {
                case APPROVED:
                    strcpy(state, "APPROVED");
                    break;
                case DECLINED_INSUFFECIENT_FUND:
                    strcpy(state, "DECLINED_INSUFFECIENT_FUND");
                    break;
                case DECLINED_STOLEN_CARD:
                    strcpy(state, "DECLINED_STOLEN_CARD");
                    break;
                case EXCEEDED_MAX_AMOUNT:
                    strcpy(state, "DECLINED_EXCEEDED_MAX_AMOUNT");
                    break;
                case DECLINED_EXPIRED_CARD:
                    strcpy(state, "DECLINED_EXPIRED_CARD");
                    break;
                case INTERNAL_SERVER_ERROR:
                    strcpy(state, "DECLINED_INTERNAL_SERVER_ERROR");
                    break;
            }
            printf("Transaction Sequence Number: %d\n", transData.transactionSequenceNumber);
            printf("User ID: %d\n", transData.user_id);
            printf("Transaction Amount: %f\n", transData.terminalData.transAmount);
            printf("TransactionDate: %s\n", transData.terminalData.transactionDate);
            printf("Transaction State: %s\n", state);
        }
        else {
            printError("Transaction Not Fount");
        }
    } else {
        printError("Invalind Input");
    }
}
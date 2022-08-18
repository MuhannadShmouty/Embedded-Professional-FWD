#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"

EN_transState_t recieveTransactionData(ST_transaction_t *transData, ST_accountsDB_t accountDB[]) {
    if (isValidAccount(transData, accountDB) == OK) {
        if(isCardExpired(transData->cardHolderData) == EXPIRED_CARD) {
            printError("Declined\nExpired Card");
            return DECLINED_EXPIRED_CARD;
        }

        if(accountDB[transData->user_id].isStolen == true) {
            printError("Declined\nStolen Card");
            return DECLINED_STOLEN_CARD;
        }
        if(isBelowMaxAmount(&(transData->terminalData)) == EXCEED_MAX_AMOUNT) {
            printError("Exceeded Maximum Transaction Amount");
            return EXCEEDED_MAX_AMOUNT;
        }
        else if (transData->terminalData.transAmount > accountDB[transData->user_id].Balance) {
            // Insufficient balance amount
            printError("Declined\nInsufficient Funds");
            
            return DECLINED_INSUFFECIENT_FUND;
        } 

        // Amount is available
        // update the database with the new balance
        accountDB[transData->user_id].Balance -= transData->terminalData.transAmount;
        return APPROVED;
    }
    else {
        printError("Declined\nStolen card");
        transData->user_id = -1;
        return DECLINED_STOLEN_CARD;
    }
}

EN_serverError_t isValidAccount(ST_transaction_t *transData, ST_accountsDB_t accountDB[]) {
    // check if account exists
    // printf("db: %s\nentry: %s\n", accountDB[24].PAN, transData->cardHolderData.primaryAccountNumber);

    for (int8_t i = 0; i < ACC_DB_MAX_SIZE ; i++) {
        if (((strcmp(accountDB[i].PAN, transData->cardHolderData.primaryAccountNumber) == 0)) &&
            ((strcmp(accountDB[i].CardHolderName, transData->cardHolderData.cardHolderName)) == 0) &&
            ((strcmp(accountDB[i].CardExpirationDate, transData->cardHolderData.cardExpirationDate)) == 0)) {
                // Account exists
                transData->user_id = i;
                return OK;
            }
    }
    return ACCOUNT_NOT_FOUND; 
}


int32_t getTransactionSequenceNumber() {
    FILE *transFilePtr = fopen("../Server/transactionsDB.csv", "r");
    // Skip first line
    fseek(transFilePtr, 94, SEEK_SET);
    
    if (fgetc(transFilePtr) == EOF) {
        // file is empty
        fclose(transFilePtr);
        return 0;
    }
        
    fseek(transFilePtr, -1, SEEK_CUR);

    int32_t lastID;
    int8_t rest[100];

    int32_t index = 0;
    int8_t buffer[100];
    
    while (fgets(buffer, 100, transFilePtr) != NULL) {
        sscanf(buffer, "%d,%s", &lastID, rest);
        index++;
        // clear buffer
        memset(buffer, 0, 100);
    }
    fclose(transFilePtr);
    return lastID + 1;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData) {
    
    FILE *transFilePtr;
    transFilePtr = fopen("../Server/transactionsDB.csv", "a");
    fseek(transFilePtr, 2, SEEK_CUR);

    // Writing transactionsDB.csv file
    int8_t state[50];
    switch (transData->transState) {
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

    
    getTransactionDate(&(transData->terminalData));

    
    fprintf(transFilePtr, "\n%d, %d, %f, %s, %s", getTransactionSequenceNumber(), transData->user_id,
            transData->terminalData.transAmount, transData->terminalData.transactionDate, state);

    fclose(transFilePtr);
}


EN_serverError_t loadData(ST_accountsDB_t accountDB[]) {
    FILE *accountsDbPtr = fopen("../Server/accountsDB.csv", "r");

    int32_t index = 0;
    int8_t buffer[100];

    // To skip first line
    while (fgetc(accountsDbPtr) != '\n');

    while (fgets(buffer, 100, accountsDbPtr) != NULL) {
        sscanf(buffer, "%hd, %[^,], %[^,], %[^,], %f, %hhd", &(accountDB[index].id), accountDB[index].CardHolderName,
        accountDB[index].PAN, accountDB[index].CardExpirationDate, &(accountDB[index].Balance), &(accountDB[index].isStolen));
        index++;
        // clear buffer
        memset(buffer, 0, 100);
    }
    fclose(accountsDbPtr);
}

EN_serverError_t saveAccountData(ST_accountsDB_t accountDB[]) {

    FILE *accFilePtr;
    // Saving accountDB.csv file
    accFilePtr = fopen("../Server/accountsDB.csv", "w");
    
    // To skip first line
    int8_t buffer[100];

    // printf("%d, %s, %s, %s, %f\n", accountDB[22].id, accountDB[22].CardHolderName,
    //             accountDB[22].PAN, accountDB[22].CardExpirationDate, accountDB[22].Balance);
    fprintf(accFilePtr, "id, Card Holder Name, PAN, Card Expiration Date, Balance, isStolen\n");

    for (int i = 0; i < ACC_DB_MAX_SIZE; i++) {
        if (accountDB[i].CardHolderName[0] == 0)
            break;
        
        fprintf(accFilePtr, "%d, %s, %s, %s, %f, %d\n", accountDB[i].id, accountDB[i].CardHolderName,
                accountDB[i].PAN, accountDB[i].CardExpirationDate, accountDB[i].Balance, accountDB[i].isStolen);
    }
    fclose(accFilePtr);
}


EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData) {
    // search for a transaction in database by transactionSequenceNumber
    FILE *transFilePtr = fopen("../Server/transactionsDB.csv", "r");

    // Skip first line
    fseek(transFilePtr, 94, SEEK_SET);
    
    if (fgetc(transFilePtr) == EOF) {
        // file is empty
        fclose(transFilePtr);
        return TRANSACTION_NOT_FOUND;
    }
    
    int8_t buffer[100];
    int8_t rest[100];
    uint32_t currentSequenceNumber;
    fseek(transFilePtr, -1, SEEK_CUR);

    while (fgets(buffer, 100, transFilePtr) != NULL) {
        sscanf(buffer, "%d, %s", &currentSequenceNumber, rest);

        if (currentSequenceNumber == transactionSequenceNumber) {
            // printf("Transaction:\n%s\n", buffer);
            sscanf(buffer, "%u, %d, %f, %[^,], %d", &transData->transactionSequenceNumber,
                    &transData->user_id, &transData->terminalData.transAmount,
                    transData->terminalData.transactionDate, (int *)&transData->transState);
            fclose(transFilePtr);
            return OK;
        }
    }
    fclose(transFilePtr);
    return TRANSACTION_NOT_FOUND;
}
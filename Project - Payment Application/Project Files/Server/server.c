#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"


uint32_t user_id;
ST_database_t accountDB[ACC_DB_MAX_SIZE];
ST_transaction_t transData;


EN_transState_t recieveTransactionData(ST_transaction_t *transData) {
    
    // id PANs don't match return FRAUD_CARD
    bool found = false;
    // search through database array using the name
    for (int16_t i = 0; i < ACC_DB_MAX_SIZE ; i++) {
        if (found)
            break;
        if (strcmp(transData->cardHolderData.cardHolderName, accountDB[i].CardHolderName) == 0) {
            // Account exists
            // get the id of that name
            user_id = i;
            found = true;
        }
    }

    if (!found){
        // Entry name is not found in database array
        printError("Declined\nIncorrect Name");
        user_id = ERROR_NUM;
        return FRAUD_CARD;
    }

    if (isValidAccount(transData->cardHolderData, accountDB[user_id].accountData) == ACCOUNT_NOT_FOUND) {
        // entry PAN not found in database array
        printError("Declined\nIncorrect PAN");
        user_id = ERROR_NUM;
        return FRAUD_CARD;
    }

    if (strcmp(accountDB[user_id].CardExpirationDate, transData->cardHolderData.cardExpirationDate) != 0) {
        // entry expiration date does not match card expiration date in database array
        printError("Declined\nIncorrect Expiration Date");
        user_id = ERROR_NUM;
        return FRAUD_CARD;
    }

    if (isBelowMaxAmount(&(transData->terminalData)) == EXCEED_MAX_AMOUNT) {
        printError("Exceeded Max Amount");
        return INTERNAL_SERVER_ERROR;
    }

    if(accountDB[user_id].accountData.state == BLOCKED) {
        // Account exists in database array, but it is blocked
        printError("Declined\nStolen Card");
        return DECLINED_STOLEN_CARD;
    }
    
    if (isAmountAvailable(&(transData->terminalData)) == LOW_BALANCE) {
        // Insufficient balance amount
        printError("Declined\nInsufficient Funds");
        
        return DECLINED_INSUFFECIENT_FUND;
    }

    // Amount is available
    // update the database array with the new balance
    accountDB[user_id].accountData.balance -= transData->terminalData.transAmount;
    printSuccess("Valid Account");
    return APPROVED;

}

EN_serverError_t isValidAccount(ST_cardData_t cardData, ST_accountsDB_t accountRefrence) {
    // check if account PAN is correct with respect to database
    
    if (strcmp(accountRefrence.primaryAccountNumber, cardData.primaryAccountNumber) == 0) {
            // Account exists
            return SERVER_OK;
    }

    return ACCOUNT_NOT_FOUND; 
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData) {
    if(termData->transAmount > accountDB[user_id].accountData.balance)
        return LOW_BALANCE;
    return SERVER_OK;
}



int32_t getTransactionSequenceNumber() {
    FILE *transFilePtr = fopen("../Server/transactionsDB.csv", "r");
    // Skip first line
    fseek(transFilePtr, SIZE_OF_TITLE_LINE, SEEK_SET);
    
    if (fgetc(transFilePtr) == EOF) {
        // file is empty
        fclose(transFilePtr);
        return 0;
    }
        
    fseek(transFilePtr, -1, SEEK_CUR);

    int32_t lastID;
    int8_t rest[SIZE_OF_BUFFER];

    int32_t index = 0;
    int8_t buffer[SIZE_OF_BUFFER];
    
    while (fgets(buffer, SIZE_OF_BUFFER, transFilePtr) != NULL) {
        // Repeat until end of file is reached
        sscanf(buffer, "%d,%s", &lastID, rest);
        index++;
        // clear buffer
        memset(buffer, 0, SIZE_OF_BUFFER);
    }
    // Close file
    fclose(transFilePtr);
    return lastID + 1;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData) {
    
    FILE *transFilePtr;
    transFilePtr = fopen("../Server/transactionsDB.csv", "a");
    // Seek to a new line
    fseek(transFilePtr, 2, SEEK_CUR);

    // Writing transactionsDB.csv file
    int8_t transaction_state[SIZE_OF_STATE];
    switch (transData->transState) {
        case APPROVED:
            strcpy(transaction_state, "APPROVED");
            break;
        case DECLINED_INSUFFECIENT_FUND:
            strcpy(transaction_state, "DECLINED_INSUFFECIENT_FUND");
            break;
        case DECLINED_STOLEN_CARD:
            strcpy(transaction_state, "DECLINED_STOLEN_CARD");
            break;
        case FRAUD_CARD:
            strcpy(transaction_state, "DECLINED_FRAUD_CARD");
            break;
        case INTERNAL_SERVER_ERROR:
            strcpy(transaction_state, "DECLINED_INTERNAL_SERVER_ERROR");
            break;
    }

    
    getTransactionDate(&(transData->terminalData));

    uint32_t transSeqNum = getTransactionSequenceNumber();    
    fprintf(transFilePtr, "\n%d, %d, %f, %s, %s", transSeqNum, user_id,
            transData->terminalData.transAmount, transData->terminalData.transactionDate, transaction_state);

    fclose(transFilePtr);

    if(getTransaction(transSeqNum, transData) == TRANSACTION_NOT_FOUND){
        return SAVING_FAILED;
    }
}


EN_serverError_t loadData() {
    FILE *accountsDbPtr = fopen("../Server/accountsDB.csv", "r");

    int32_t index = 0;
    int8_t buffer[SIZE_OF_BUFFER];
    int8_t state[STATE_SIZE];

    // To skip first line
    while (fgetc(accountsDbPtr) != '\n');

    while (fgets(buffer, 100, accountsDbPtr) != NULL) {
        sscanf(buffer, "%hd, %[^,], %[^,], %[^,], %f, %[^\n]", &(accountDB[index].id), accountDB[index].CardHolderName,
        accountDB[index].accountData.primaryAccountNumber, accountDB[index].CardExpirationDate, &(accountDB[index].accountData.balance),
        (char *)&state);

        if (strcmp(state, "RUNNING") == 0) {
            accountDB[index].accountData.state = RUNNING;
        } else {
            accountDB[index].accountData.state = BLOCKED;
        }
        index++;

        // clear buffer
        memset(buffer, 0, SIZE_OF_BUFFER);
    }
    fclose(accountsDbPtr);
}

EN_serverError_t saveAccountData(ST_database_t accountDB[]) {

    FILE *accFilePtr;
    // Saving accountDB.csv file
    accFilePtr = fopen("../Server/accountsDB.csv", "w");
    
    // To skip first line
    int8_t buffer[SIZE_OF_BUFFER];
    int8_t state[STATE_SIZE];
    fprintf(accFilePtr, "id, Card Holder Name, PAN, Card Expiration Date, Balance, Transaction State\n");

    for (int i = 0; i < ACC_DB_MAX_SIZE; i++) {
        if (accountDB[i].CardHolderName[0] == 0)
            break;
        
        if (accountDB[i].accountData.state == RUNNING) {
            strcpy(state, "RUNNING");
        } else {
            strcpy(state, "BLOCKED");
        }
        
        fprintf(accFilePtr, "%d, %s, %s, %s, %f, %s\n", accountDB[i].id, accountDB[i].CardHolderName,
                accountDB[i].accountData.primaryAccountNumber, accountDB[i].CardExpirationDate,
                accountDB[i].accountData.balance, state);
    }
    fclose(accFilePtr);
}


EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData) {
    // search for a transaction in database by transactionSequenceNumber
    FILE *transFilePtr = fopen("../Server/transactionsDB.csv", "r");

    // Skip first line
    fseek(transFilePtr, SIZE_OF_TITLE_LINE, SEEK_SET);
    
    if (fgetc(transFilePtr) == EOF) {
        // file is empty
        fclose(transFilePtr);
        return TRANSACTION_NOT_FOUND;
    }
    // Seek back 1 character
    fseek(transFilePtr, -1, SEEK_CUR);

    int8_t buffer[SIZE_OF_BUFFER];
    int8_t rest[SIZE_OF_BUFFER];
    uint32_t currentSequenceNumber;

    

    while (fgets(buffer, SIZE_OF_BUFFER, transFilePtr) != NULL) {
        sscanf(buffer, "%d, %s", &currentSequenceNumber, rest);
        if (currentSequenceNumber == transactionSequenceNumber) {
            sscanf(buffer, "%u, %d, %f, %[^,], %d", &transData->transactionSequenceNumber,
                    &user_id, &transData->terminalData.transAmount,
                    transData->terminalData.transactionDate, (int *)&transData->transState);
            fclose(transFilePtr);
            return SERVER_OK;
        }
    }
    fclose(transFilePtr);
    return TRANSACTION_NOT_FOUND;
}

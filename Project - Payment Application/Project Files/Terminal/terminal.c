#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#include "../Card/card.h"
#include "terminal.h"



EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
    // Get current date from the OS
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    uint8_t dd = tm.tm_mday;
    uint8_t mm = tm.tm_mon+1;
    uint16_t yy = tm.tm_year+1900;

    // Create the date string in the fromat DD/MM/YYYY
    sprintf(termData->transactionDate, "%02d/%02d/%04d", dd, mm, yy);
    return OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData) {
    // Get current date from the OS
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // uint8_t dd = tm.tm_mday;
    int currentMonth = tm.tm_mon+1;
    long currentYear = tm.tm_year+1900;
    
    long cardExpYear;
    int cardExpMonth;

    // Extract the date from the strings
    sscanf(cardData.cardExpirationDate, "%02d/%02ld", &cardExpMonth, &cardExpYear);

    // Adding 2000 as the expected year is 2 digit only
    cardExpYear += THE_YEAR_TWO_THOUSAND;

    if (cardExpYear >= currentYear){
        if (cardExpYear > currentYear)
        {
            // Future year
            
            return OK;
        }
        if (cardExpMonth > currentMonth)
        {
            // Future month
            return OK;
        }
    }
    return EXPIRED_CARD;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData) {
    float buffer;
    printf("Transaction Amount: ");
    scanf("%f", &buffer);

    if (buffer <=0) {
        printError("Invalid Transaction Amount");
        termData->transAmount = buffer;
        return INVALID_AMOUNT;
    }

    if (buffer > termData->maxTransAmount) {
        termData->transAmount = buffer;
        return EXCEED_MAX_AMOUNT;
    }
    termData->transAmount = buffer;
    return OK;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {
    if (termData->transAmount > termData->maxTransAmount) {
        return EXCEED_MAX_AMOUNT;
    }
    return OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData) {
    float buffer;
    printf("Max Transaction amount: ");
    scanf("%f", &buffer);

    if (buffer <= 0) {
        printError("Invalid Max Amount");
        return INVALID_MAX_AMOUNT;
    }

    termData->maxTransAmount = buffer;
    return OK;
}
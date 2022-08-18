#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "card.h"


bool isNumber(uint8_t *string) {
    // Takes String and check if all it contains are numbers
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (isdigit(string[i]) == 0)
              return 0;
    }
    return 1;
}

bool isCorrectCardNumber(uint8_t *string) {
    /* Checks if the PAN is a Luhn number or not */


    unsigned long long cc_number = 0;

    int PAN_size = strlen(string);

    sscanf(string, "%llu", &cc_number);
    int sum = 0;
    int parity = (PAN_size - 2) % 2;

    for (int i = 0; i < PAN_size; i++) {
        int digit = cc_number % 10;

        if (i % 2 != 0)
            digit = digit * 2;

        if (digit > 9)
            digit = digit - 9;

        sum = sum + digit;
        cc_number /= 10;
    }

    return (sum % 10 == 0);
}


EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {

    // Request cardholder's name
    uint8_t buffer[MAX_NAME_BUFFER_SIZE];
    
    // Using scanset to get input string with spaces
    printf("Card Holder Name: ");
    scanf(" %25[^\n]", buffer); 
    
    // Check if the name is valid
    uint16_t cardHolderName_len;


    cardHolderName_len = strlen(buffer);

    if (cardHolderName_len > MAX_CARD_HOLDER_NAME_LEN ||
        cardHolderName_len < MIN_CARD_HOLDER_NAME_LEN) 
    {
        // Invalid Card Holder Name
        printError("Invalid Card Holder Name");
        return WRONG_NAME;
    }
    else {
        // Valid Card Holder Name
        strcpy (cardData->cardHolderName, buffer);
        return OK;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
    // Request card's expiry date
    uint8_t buffer[MAX_DATE_BUFFER_SIZE];
    printf("Expiry date (MM/YY): ");
    scanf(" %6s", buffer);
    
    int mm,yy;

    if ((buffer[2] == '/') &&
        (sscanf(buffer, "%d/%d", &mm, &yy) == 2) &&
        (strlen (buffer) == EXPIRY_DATE_SIZE) &&
        mm <= MAX_VALID_MONTH && mm > 0){
        
        // TODO : is it neccesary to check if the card actually expired?

        // Date format is Valid [MM/YY]
        // Month is between 1 - 12
        // Year is not older than the current year
        
        strcpy (cardData->cardExpirationDate, buffer);
        return OK;
    }else {
        printError("Invalid Expiry Date");
        return WRONG_EXP_DATE;
    } 
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData) {
    // Request card's PAN
    uint8_t buffer[MAX_PAN_BUFFER_SIZE];
    printf("Primary Account Number: ");
    scanf(" %20s", buffer);

    if (isNumber(buffer) && (strlen(buffer) >= MIN_PAN_SIZE) 
    && (strlen(buffer) <= MAX_PAN_SIZE) && isCorrectCardNumber(buffer)){

        // is a number
        // correct size
        // correct format
        strcpy (cardData->primaryAccountNumber, buffer);
        return OK;
    }else {
        printError("Invalid Primary Account Number");
        return WRONG_PAN;
    }
    
}

void printError(char *errorMessage) {
    printf(RED);
    printf("%s\n", errorMessage);
    printf(RESET);
}

void printSuccess(char *Message) {
    printf(GREEN);
    printf("%s\n", Message);
    printf(RESET);
}
#ifndef CARD_H
#define CARD_H


#define MIN_CARD_HOLDER_NAME_LEN 20
#define MAX_CARD_HOLDER_NAME_LEN 24

#define MAX_NAME_BUFFER_SIZE     26
#define MAX_DATE_BUFFER_SIZE     7
#define MAX_PAN_BUFFER_SIZE      22
#define MIN_PAN_SIZE             16
#define MAX_PAN_SIZE             19


#define EXPIRY_DATE_SIZE         5
#define MAX_VALID_MONTH          12
#define MIN_VALID_YEAR           21

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m" 


typedef enum EN_cardError_t
{
    OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
void printError(char *errorMessage);
void printSuccess(char *Message);

bool isNumber(uint8_t *string);
bool isCorrectCardNumber(uint8_t *string);

#endif
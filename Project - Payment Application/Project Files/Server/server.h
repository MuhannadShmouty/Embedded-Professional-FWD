#ifndef SERVER_H
#define SERVER_H


#define SIZE_OF_BUFFER 100
#define ACC_DB_MAX_SIZE 255
#define TRANS_DB_MAX_SIZE 255

typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, EXCEEDED_MAX_AMOUNT, DECLINED_EXPIRED_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    int32_t user_id;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
    Alright, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, FILE_ERROR
}EN_serverError_t ;



typedef struct ST_accountsDB_t {
    uint16_t id;
    int8_t CardHolderName[25];
    uint8_t PAN[MAX_PAN_SIZE + 1];
    int8_t CardExpirationDate[6];
    float Balance;
    uint8_t isStolen;
} ST_accountsDB_t;


EN_transState_t recieveTransactionData(ST_transaction_t *transData, ST_accountsDB_t accountDB[]);
EN_serverError_t isValidAccount(ST_transaction_t *transData, ST_accountsDB_t accountDB[]);
// EN_serverError_t isAmountAvailable(float transAmount, float balance);
int32_t getTransactionSequenceNumber();
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);
EN_serverError_t loadData(ST_accountsDB_t accountDB[]);
EN_serverError_t saveAccountData(ST_accountsDB_t accountDB[]);

#endif
#include<stdio.h>
#include<stdlib.h>
struct Node{
    int transactionId;
    int transactionAmount;
    struct Node *next;
} *start= NULL;
//function to insert transactions with their id and amount in Linked List
void insertTransactions(int transacId,int transacAmount){
    //dyanmically allocating memory 
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->transactionId = transacId;
    temp->transactionAmount = transacAmount;
    temp->next= NULL;
    if(start == NULL){//if start is null update start
        start=temp;
    }
    else{
        struct Node *curr=start;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next=temp;
    }
}
// Function to delete fraudulent transactions  
void deleteFraudulentTransactions(int fraudulentTransactionId){
    struct Node *curr=start;
    //if you want to delete first Node 
    if(fraudulentTransactionId==start->transactionId){
        start=start->next; //update start
        free(curr);//free is used to deallocate memory
    }
    else{//if the node to be deleted is not first you have to maintain prev with respect to curr
        struct Node *prev = start;
        curr = start->next;
        while(curr != NULL){
            if(curr->transactionId == fraudulentTransactionId){
                prev->next = curr->next;
                free(curr);
                break;
            }
            else{
                prev = prev->next;
                curr = curr->next;
            }
        }
        if(curr == NULL){
            printf("Fraudulent Transaction Id not found");
        }
    }
}
//Function to print all transactions free from fraudulent transactions
void printTransactions() {
    struct Node* curr = start;
    while (curr!= NULL) {
        printf("%d,%d\n", curr->transactionId, curr->transactionAmount);
        curr= curr->next;
    }
}
int main() {
    FILE* fptr = fopen("Test01.txt", "r");
    //checking if text file exists or not
    if (fptr == NULL) {
        printf("Error opening the input file.\n");
        return -1;
    }
    int numberOfTransactions, numberOfFraudulentTransactions;
    int transacId, transacAmount;

    //reading no of transactions and no of fraudulant transaction from first line of file 
    fscanf(fptr, "%d %d", &numberOfTransactions, &numberOfFraudulentTransactions);

    // Reading all transactions from file and then insertTransactions function is called to insert transactions in Linked List
    for (int i = 1; i <= numberOfTransactions; i++) {
        fscanf(fptr, "%d,%d", &transacId, &transacAmount);
        insertTransactions(transacId, transacAmount);
    }
    
    // Reading Fraudulent Transactions from file and deleteFradulentTransactions() function is called to delete fraudulant transactions 
    for (int i = 1; i <= numberOfFraudulentTransactions; i++) {
        int fraudulentTransactionId;
        fscanf(fptr, "%d", &fraudulentTransactionId);
        deleteFraudulentTransactions(fraudulentTransactionId);
    }

    
    // Print the updated list of transactions
    printTransactions(); // printTransaction functions is called to print all valid transactions with their ids and amount

    fclose(fptr);
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//using single linked list
struct Node{
    int customer;
    struct Node *next;      //holds the address of next node
} *start= NULL;             //initially the list will be null/empty (global variable declaration)

//to insert a node
void addCustomers(int customerNo){
    //dyanmically allocating memory 
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->customer = customerNo;
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
// to print the list of customers
void printLinkedList(){
    struct Node *curr = start;
    printf("List of customers is: \n");
    while (curr!=NULL)
    {
        printf("%d -> ",curr->customer);
        curr=curr->next;
    }
    if(curr == NULL){
        printf("null\n");
    }
}


void deleteCustomer() {
    if (start == NULL) {
        return; // List is empty, nothing to delete
    }

    if (start->next == NULL) {
        // If there's only one node in the list, delete it
        free(start);
        start = NULL;
    } else {
        // Traverse the list to find last node
        struct Node *prev = start;
        while (prev->next->next != NULL) {
            prev = prev->next;
        }

        // Free the last node and set the previous node's next to NULL
        free(prev->next);
        prev->next = NULL;
    }
}

//function to find the winner using two pointers 
void getTrump(){
    struct Node *curr = start;      //curr is pointing to start of Linked list
    struct Node *temp = start;      //temp is also pointing to start of Linked

    while (curr->next != NULL && curr->next->next != NULL) {
        temp = temp->next;          //value of temp is updated
        curr = curr->next->next;    //value of curr is update
    }
    //curr->next == NULL
    if (curr->next == NULL) {
        // if nodes are odd then middle value will be winner
        if (curr == start || curr->next == NULL) {
            //if only one node is left then print that node as winner
            printf("Winner is customer %d",temp->customer);
        }
    }
    else {
        // if nodes are even then middle 2 values will be winners
        printf("Winners are customers %d and %d",temp->customer,temp->next->customer);
    }
}

int main(){
    FILE *fptr;
    char command[10];
    int customerNo;

    fptr=fopen("Test01.txt","r");

    //to check if file exists or not
    if(fptr==NULL){
        printf("File doesn't exists\n");
    }
    //looping till end Of file occurs
    while (fscanf(fptr, "%s", command) != EOF) {
         //if command is equal to ADD then read the string from file and call addValue(value) function to insert value in Linked list
        if (strcmp(command, "ADD") == 0) {
            fscanf(fptr, "%d", &customerNo);
            addCustomers(customerNo);
        } //if command is equal to DELETE then deleteValue() func is called to delete node
        else if (strcmp(command, "DELETE") == 0) {
            deleteCustomer();
        } //if command is equal to END then break loop file is ended
        else if (strcmp(command, "END") == 0) {
            break;
        }
    }
    // printLinkedList();  //to display Customers list call printLinkedList Function
    getTrump();         //call getTrump() to get winners
    fclose(fptr);       //close file
    return 0;
}
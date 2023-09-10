#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    int numbers;
    struct Node *next;  //holds the address of next node
} *start= NULL;         //initially the list will be null/empty (global variable declaration)

//to insert a node
void addNumbers(int numbers){
    //dyanmically allocating memory 
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->numbers = numbers;
    temp->next= NULL;
    if(start == NULL){  //if start is null update start
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
// Function to sort linked list in ascending order
void sortLinkedList(){
    struct Node *curr = start;
    struct Node *temp;

    while (curr != NULL) {
        temp = curr->next;
        while (temp != NULL) {
            if (curr->numbers > temp->numbers) {
                int tempNum = curr->numbers; //value in curr will be stored in tempNum location
                curr->numbers = temp->numbers; //value in temp will be stored in curr
                temp->numbers = tempNum; //value stored in tempNum location will be stored in temp 
            }
            temp = temp->next;
        }
        curr = curr->next;
    }
}

// Function to return median as middle number if Linked list has even Nodes and average of middle two numbers if Linked List has odd Nodes
float MedianOfTheStream(){
    struct Node *curr = start;      //curr is pointing to start of Linked list
    struct Node *temp = start;      //temp is also pointing to start of Linked

    while (curr->next != NULL && curr->next->next != NULL) {
        temp = temp->next;          //value of temp is updated
        curr = curr->next->next;    //value of curr is update
    }
    //curr->next == NULL
    if (curr->next == NULL) {
        // if nodes are odd then middle value will be median
        return temp->numbers;
    }  
    else {
        // if nodes are even then average of middle 2 values will be median
        return (temp->numbers+temp->next->numbers)/2.0;
    }
}

int main(){
    FILE *fptr;
    int numbers;

    fptr=fopen("Test01.txt","r");

    //to check if file exists or not
    if(fptr==NULL){
        printf("File doesn't exists\n");
    }
    while(fscanf(fptr,"%d",&numbers) != EOF ){
        addNumbers(numbers);
        if(0 > numbers <= 100){//integers should be greater than 0 and less than 100
            sortLinkedList();
            printf("%.1f\n",MedianOfTheStream());
        }
    }
    fclose(fptr);
    return 0;
}
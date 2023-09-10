#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// using single linked list
struct Node{
    int numbers;
    struct Node *next;  //holds the address of next node
} *start= NULL;         //initially the list will be null/empty (global variable declaration)

//to insert a node
void insert(int numbers){
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
//Function to return the third last element in linked list 
int thirdLastElement()
{
    struct Node *curr=start;    //curr points to the start(first node) in the list
    int len = 0;                // initially taking len=0
    
    // Counting the number of nodes in Linked List
    while (curr != NULL) {
        len=len+1; // len will be incremented to find total length of list
        curr = curr->next;
    }
    //if length is less than -3 then we will return -1
    if (len < 3){
        printf("-1");
        return -1;
    }
    curr = start;
 
    // Get the (len-3+1)th node from the beginning
    //eg len=6 (6+3+1)=4 then 3rd last element from list will be returned
    for (int i = 1; i < len - 3 + 1; i++){
        curr = curr->next;
    }
    printf("%d", curr->numbers); 
}

int main(){
    FILE *fptr;
    int numbers;

    fptr=fopen("Test01.txt","r");

    //to check if file exists or not
    if(fptr==NULL){
        printf("File doesn't exists\n");
    }
    //read all integer values till the end of file
    while(fscanf(fptr,"%d",&numbers) != EOF ){
        insert(numbers);
    }
    //All numbers must be greater than 0
    if(numbers>0){
        thirdLastElement(); // calling function to print third last element from linked list
    }

    fclose(fptr);
    return 0;
}
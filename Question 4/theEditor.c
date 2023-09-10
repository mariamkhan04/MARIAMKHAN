#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Node{
    int number;
    struct Node *prev;  //pointer to maintain a link to previous node
    struct Node *next;  //holds the address of next node
} *start= NULL;         //initially the list will be null/empty (global variable declaration)
struct Node *cursor=NULL;//cursor pointer to maintain cursor position

//Function to add number at the end of list
void addAtEnd(int number){
    //dyanmically allocating memory 
    struct Node *temp=(struct Node *)malloc(sizeof(struct Node));
    temp->number = number;
    temp->next= NULL;
    if(start == NULL){//if start is null update start
        start=temp;
        cursor=temp;//cursor position updated
    }
    else{
        struct Node *curr=start;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next=temp; //last node's next will point to new node(temp)
        temp->prev=curr; //new node's prev will point to last node
    }
}
//function to delete the tail of list
void deleteTail(){
    struct Node *curr=start;
    if(start == NULL){
        printf("Empty list\n");
        return;
    }
    while (curr->next!=NULL)
    {
        curr = curr->next;
    }
    if(curr->prev==NULL){//if only one node is left
        start=NULL;
    }else{
        curr->prev->next=NULL;//tail of list will be deleted 
    }
    free(curr);//free mem for curr
}
// Function to add a node at a specific index
void addAtSpecificIndex(int index,int number) {
    if (index == 0) {   //if index number is 0 then call addAtEnd() function to add at start of list
        addAtEnd(number);
    return;
    }
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node)); //dynamically allocate memory for new node
    temp->number = number;
    temp->next = NULL;
    struct Node *curr = start;  //curr is pointing to start
    // loop is used to traverse the linked list until it reaches the node just before the desired index
    for (int i = 0; i < index - 1; i++) {
        curr = curr->next;
    }
    temp->prev = curr;
    temp->next = curr->next;
    curr->next->prev = temp;
    curr->next = temp;
}
//Function to delete a node at specific index
void deleteAtSpecificIndex(int index){
    if(start == NULL){
        printf("Empty list\n");
        return;
    }
    struct Node *curr=start; // curr points to the current node
    struct Node *prev = NULL; //prev points to the previous node
    // loop is used to traverse the linked list until it reaches the node just before the desired index
    for (int i = 0; i < index ; i++) {
        curr = curr->next;
    }
    // If the node is not found, return.
    if (curr == NULL) {
        printf("element not found");
        return;
    }
    if(curr == start){      //if node to be deleted is first node 
        start = start->next; //update start
        start->prev = NULL;
    }
    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    if(curr->next==NULL){
        if(index == 0){//if only one node left
            curr=NULL;
        }else{
            curr->prev->next = NULL;
        }
    }
    // Free the memory allocated for the node.
    free(curr);
}
// Function to move the cursor forward by a certain number of steps
void moveForwardsteps(int steps) {
    struct Node *curr = cursor;//curr is pointing to cursor
    struct Node *prev = NULL;
    for (int i = 0; i < steps; i++) {
        if (curr == NULL) {
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cursor = curr;//cursor is updated by given no of steps
    printf("cursor moved forward by %d steps\n",steps);
}

// Function to move the cursor backward by a certain number of steps
void moveBackwardsteps(int steps) {
  struct Node *curr = cursor;
  for (int i = 0; i < steps; i++) {
    if (curr == NULL) {
      return;
    }
    curr= curr->prev;
  }
  cursor = curr;
  printf("cursor moved backwards by %d steps\n",steps);
}
// Function to add value just after the cursor's position
void addImmediateNumber(int number) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->number = number;
    temp->next = NULL;

    // Check if the cursor is at the end of the list.
    if (cursor == NULL ) {
        addAtEnd(number);
        return;
    }

    // Get the node after the cursor.
    struct Node *next = cursor->next;

    // Insert the new node after the cursor.
    temp->next = next;
    next->prev = temp;
    temp->prev = cursor;
    cursor->next = temp;
}
//Function to delete the value on which cursor is pointing at
void deleteImmediateNumber() {
    if (cursor == NULL || cursor->next == NULL) {
        return;
    }

    // Get the node where the cursor is present
    struct Node *curr = cursor;

    // Delete the cursor node
    cursor=cursor->next;
    curr->next->prev = NULL;
    free(curr);
}
//function to print value where the cursor is pointing at
void printCursorNode() {
    if(cursor==NULL){
        printf("cursor is at the end of list\n");
    }
    printf("%d\n",cursor->number);
}
//Function to update the value of specified index number with new value
void updateIndexNumber(int index, int number) {
    if (start == NULL || index < 0) {
        return;
    }

    // Get the node at the specified index.
    struct Node *curr = start;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

  // Update the data of the node.
  curr->number = number;
}
// Function to update the value of immediate number where cursor is pointing to with new value
void updateImmediateNumber(int number) {
    if (start == NULL) {
        return;
    }

    // Get the cursor node.
    struct Node *CursorNode = cursor;

    // Update the data of the cursor node.
    CursorNode->number = number;
}
//Function to shift the value at specified index with value at which the cursor is pointing at
void shiftIndex(int index) {
    if (start == NULL || index < 0) {
        return;
    }

    // Get the node at the specified index.
    struct Node *curr = start;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    // Get the data of the node at the specified index.
    int number = curr->number;

    // Update the data of the cursor node.
    curr->number = start->number;

    // Update the data of the node at the beginning of the list.
    start->number = number;
}
//Function to print the whole list
void printLinkedList() {
  struct Node *curr = start;
  printf("List: [");
  while (curr != NULL) {
    if (curr != start) {
      printf(", ");
    }
    printf("%d", curr->number);
    curr = curr->next;
  }
  printf("]\n");
}
int main() {
    FILE *fptr = fopen("Test01.txt", "r");
    //check if file exists or not
    if (fptr == NULL) {
        printf("Error opening the file");
        return -1;
    }

    char command[100];
    int number, index, steps;
    // int lastOperation=0;

   while(fscanf(fptr,"%s",&command)!= EOF){
        if (strcmp(command, "Add") == 0) {
            fscanf(fptr,"%d",&number);
            addAtEnd(number);
            printLinkedList();
        } else if(strcmp(command, "Delete") == 0) {
            deleteTail();  
            printLinkedList();
        } else if(strcmp(command, "AddSpecific") == 0) {
            fscanf(fptr,"%d %d",&index,&number);
            addAtSpecificIndex(index,number); 
            printLinkedList();
        } else if(strcmp(command, "DeleteSpecific") == 0) {
            fscanf(fptr,"%d",&index);
            deleteAtSpecificIndex(index); 
            printLinkedList();
        } else if(strcmp(command,"MoveForward")==0){
            fscanf(fptr,"%d",&steps);
            moveForwardsteps(steps);
        } else if(strcmp(command,"MoveBackward")==0){
            fscanf(fptr,"%d",&steps);
            moveBackwardsteps(steps);
        } else if(strcmp(command,"AddImmediate")==0){
            fscanf(fptr,"%d",&number);
            addImmediateNumber(number);
            printLinkedList();
        } else if(strcmp(command,"DeleteImmediate")==0){
            deleteImmediateNumber();
            printLinkedList();
        } else if(strcmp(command,"Print")==0){
            printCursorNode();
        } else if(strcmp(command,"Update")==0){
            fscanf(fptr,"%d %d",&index,&number);
            updateIndexNumber(index,number);
            printLinkedList();
        } else if(strcmp(command,"UpdateImmediate")==0){
            fscanf(fptr,"%d",&number);
            updateImmediateNumber(number);
            printLinkedList();
        } else if(strcmp(command,"Shift")==0){
            fscanf(fptr,"%d",&index);
            shiftIndex(index);
        // } else if(strcmp(command,"Undo")==0){
        //     undo();
        //     printLinkedList();
        }else{
            printf("invalid operation\n");
        }
    }
    fclose(fptr);
    return 0;
}
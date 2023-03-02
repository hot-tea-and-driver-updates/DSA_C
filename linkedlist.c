#include <stdio.h>
#include <stdlib.h>

//Let us write the code so that it can be passed by pointer instead of using global var or by reference.
struct Node{
  int data;
  struct Node *next;
};

void Insert_Front(struct Node **pointertoHead, int x);
void Print(struct Node **pointertoHead);



//using a pointer to a pointer, keep in mind we are using this to pass by pointer a POINTER to head, not actual head
void Insert_Front(struct Node **pointertoHead, int x){ //think of just passing struct Node *head not, **pointertohead
  struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
  if(temp == NULL){
    printf("Malloc failed.\n");
    return;
  }
  temp->data = x;
  temp->next = *pointertoHead;   //sets our new node to point to the value at pointertohead, which is the address of head, so new node = head
                                 //where head points to NULL if it's an empty list or to the current head of the list
  *pointertoHead = temp;         //sets head to point to the new node, thus our new node is inserted into the list at the front
}

//passes head by pointer and traverses list, printing data variables
void Print(struct Node **pointertoHead){
  printf("List is: ");
  struct Node * temp = *pointertoHead; //temp is currently pointing to what head is pointing to which is either NULL or a node
  
  /*while(temp->next != NULL); why not this? bc then it's while the value of the next node is not null, print
   the value of the current node, thus if there is only one node in which case it will point only to null, the first value will not get printed out!*/
  
  while(temp != NULL){      //while our pointer variable does not point to an empty list or traversal has not completed
    printf(" %d",temp->data);  //print the current node's data
    temp = temp->next;        //traverse to next node
  }
  printf("\n");
}
  
int main(void){
  struct Node *head = NULL; //empty list
  printf("How many numbers?\n");
  int n, i, x;
  scanf("%d",&n);
  for(i = 0; i < n; i++){
    printf("Enter the number \n");
    scanf("%d",&x);
    Insert_Front(&head,x); //if we want to pass the pointer to head by pointer, we have to send the address of our head pointer
    Print(&head);
  }
  return 0;
}

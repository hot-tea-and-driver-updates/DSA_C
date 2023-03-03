#include <stdio.h>
#include <stdlib.h>

//Let us write the code so that it can be passed by pointer instead of using global var or by reference.
struct Node{
  int data;
  struct Node *next;
};

void Insert_Front(struct Node **pointertoHead, int data);
void Insert_End(struct Node **pointertoHead, int data);
void Delete(struct Node **pointertoHead, int npos);
void Insert_Nth(struct Node **pointertohead, int data, int npos);
void Print(struct Node **pointertoHead);
int Count(struct Node **pointertoHead);



void Insert_End(struct Node **pointertoHead, int data){
  struct Node *temp =  (struct Node *)malloc(sizeof(struct Node));
  struct Node *temp2 = *pointertoHead;
  temp->data = data;
  temp->next = NULL;
  if(temp2 == NULL){
    temp->next = *pointertoHead;
    *pointertoHead = temp;
    return;
  }
  while(temp2->next != NULL){
    temp2 = temp2->next;
  }
  //temp2 should now point to the last node
  temp->next = temp2->next;
  temp2->next = temp;
}

void Delete(struct Node **pointertoHead, int npos){
  struct Node *temp = *pointertoHead; //temp points to head
  if(npos == 1){
    *pointertoHead = temp->next;
    free(temp);
    return;
  }
  int i;
  for(i = 0; i <(npos-2);i++){
    temp = temp->next; 
  }
  //temp1 now points to the node before the one we want to delete
  struct Node *temp2 = temp->next;
  //temp2 now points to the node that we are going to delete
  temp->next = temp2->next;
  //temp1 now points to the node after temp2, this is fine even if it's NULL or another node
  free(temp2);
  //the node is now deleted.
}


void Insert_Front(struct Node **pointertoHead, int data){ //think of just passing struct Node *head not, **pointertohead
  struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
  if(temp == NULL){
    printf("Malloc failed.\n");
    return;
  }
  temp->data = data;
  temp->next = *pointertoHead;   //sets our new node to point to the value at pointertohead, which is the address of head, so new node = head
                                 //where head points to NULL if it's an empty list or to the current head of the list
  *pointertoHead = temp;         //sets head to point to the new node, thus our new node is inserted into the list at the front
}

void Insert_Nth(struct Node **pointertohead, int data, int npos){   //works for insertion at front, nth, or end, but does not account for n value that is out of bounds currently

  int boundary_check = Count(pointertohead);
  if(((npos-1) > boundary_check)||(npos < 0)){
    printf("ERROR: invalid nth position\n");
    return;
  }
  
  struct Node *temp = (struct Node*)malloc(sizeof(struct Node)); //allocating memory to create a node
  temp->data = data;
  temp->next = NULL; //initializing next node to NULL for convenience
  if(npos == 1){        //inserting node at the head
    temp->next = *pointertohead; //temp->next now points to whatever head is pointing to, this could be a node or NULL
    
    *pointertohead = temp;       //head now points to temp, so list goes head = new_node -> previous_head/NULL
    return;
  }
  struct Node *temp2 = *pointertohead; //temp2 currently points to what head points to (0th index in node/1st node)
  for(int i = 0; i < (npos-2); i++){   //npos-2 bc we want to get to the node before npos (n-1) in a 1th index -> (n-2) in 0th
    temp2 = temp2->next; 
  }
  temp->next = temp2->next;
  temp2->next = temp;
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

int Count(struct Node **pointertoHead){
  int count = 0;
  struct Node *temp = *pointertoHead;            //points to what head is pointing to
  if((temp) == NULL){                            //if head points to NULL 
    printf("empty list.\n");
    return count;
  }
  while(temp != NULL){
    count += 1;
    temp = temp->next;
  }
  return count;
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
  Insert_Nth(&head, 15, 3);
  Print(&head);
  struct Node *secondlist = NULL;
  Insert_Front(&secondlist, 5);
  Insert_Front(&secondlist, 6);
  printf("Second list operations: \n");
  Print(&secondlist);
  int count = Count(&secondlist);
  printf("Second linked list length is: %d\n",count);

  struct Node *thirdlist = NULL;
  printf("Third linked list operations: \n");
  Insert_End(&thirdlist, 10);
  Insert_End(&thirdlist, 20);
  Insert_End(&thirdlist, 30);
  Insert_End(&thirdlist, 40);
  Print(&thirdlist);
  Delete(&thirdlist, 1);
  Delete(&thirdlist, 1);
  printf("Current Third List after Deletion(): \n");
  Print(&thirdlist);
  return 0;
}

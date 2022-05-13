// CS 141 Lab 14 - Linked Lists

#include<bits/stdc++.h>
using namespace std;

// Node class for implementing a Linked List
class Node {
    public:
        int data;
        Node* next;
};
void displayLL(Node* node);
void addNode(Node* &head, int newData);

// Task 1: Insert a new node to the designated position of linked list head,
// that are passed through paramaters
void insertNode(Node* &head, int position, int newData){
   // Create a new node containing the required data
      Node* aNode = new Node;
      Node* temp = head; 
      aNode->data = newData;
      aNode->next = NULL; 
   // Iterate to the node right behind the position at which you want
   // to insert the new node
      if (position = 1) { 
         aNode->next = head;
         head = aNode; 
      } else {
         for (int i = 1; i < position; i++) {
            if (i == position - 1) {
               aNode->next = temp->next; 
               temp->next = aNode; 
            }
            temp = temp->next; 
         }
      }
         
   // Set the next value of both current node and the newly added node as per the task
   
   // Hint: Not clearing all test cases? Are you missing any edge case?
   
}

// Task 2: Swap the nodes at poisitons pos1 and pos2
void swapNodes(Node* &head, int pos1, int pos2){
   // Create two temporary pointers to the head of list, temp1 and temp2
   
   // Iterate first pointer to the node behind pos1
   
   // Iterate second pointer to the node behind pos2
   
   // Set the next value of the nodes pointed to by temp1 and temp2 as per the task
   // Hint: You may use a temorary pointer to perform this task
   
   // Set the next value of the nodes to swap as per the task
   // Hint: You may use a temorary pointer to perform this task
   
}

// Task 3: Reverse the Linked List
void reverseLL(Node* &head) {
   /* The logic is -
   We iterate through each node of the linked list and set its next value to point
   at its previous node's value. 
   In addition, we use a temporary variable to hold the original next value of the node 
   and use it to iterate to the next node in the Linked List
   */
   
   // Initialise the required pointers 
   Node *current = head; // Pointer to current node in iteration
   Node *temp = NULL; // Holds pointer to the next node to iterate to 
   Node *prev = NULL; // Holds pointer to previous node
   
   // Iterate and perform the required steps to reverse the list
   //while(current != NULL) {
      // Write your code here
   // }
   
   // Change head to the new head of the linked list (fill in the ???)
   // head = ???;
}




int main(){
   Node *head = NULL;
   int numOfNode;
   cout << "*****Node Initialization*****" << endl;
   cout << "Enter the Number of Nodes : " ;
   cin >> numOfNode;
   for(int i=0;i<numOfNode;i++){
       int data;
       cin >> data;
       addNode(head,data);
   }
   displayLL(head);
   cout << "*****Node Initialization Done*****" << endl;
   
   
   // Pick a task 
   int task;
   cout << "Enter the task Number (-1 for Exit): ";
   cin >> task;
  
   // Execute the selected task
   if(task==1) {
       cout << "Enter the position where a new node is inserted: ";
       int position;
       cin >> position;
       cout << "Enter the data for a new node: ";
       int data;
       cin >> data;
       insertNode(head,position,data);
       displayLL(head);
   }
   else if(task==2){
       cout << "Enter the positions to swap nodes at: ";
       int pos1, pos2;
       cin >> pos1 >> pos2;
       swapNodes(head,pos1, pos2);
       displayLL(head);
   }
   else if(task==3){
       reverseLL(head);
       displayLL(head);
   }
}
void displayLL(Node* node)
{
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
}

void addNode(Node* &head, int newData) 
{ 
   
    // 1. allocate node
    Node* newNode = new Node();
   
    // Used in step 5
    Node *last = head;
   
    // 2. Put in the data
    newNode->data = newData; 
   
    // 3. This new node is going to be 
    // the last node, so make next of 
    // it as NULL
    newNode->next = NULL; 
   
    // 4. If the Linked List is empty,
    // then make the new node as head
    if (head == NULL) 
    { 
        head = newNode; 
        return; 
    } 
   
    // 5. Else traverse till the last node
    while (last->next != NULL)
    {
        last = last->next; 
    }
   
    // 6. Change the next of last node
    last->next = newNode; 
    return; 
} 


/*Title: Stack.cpp
  Author: Shariq Moghees
  Date: 12/1/2024
  Description: This class defines a templated stack using a linked list
*/
#include <iostream>
#include <stdexcept>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
  m_data = data;
  m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
  return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData(const T& data ) {
  m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
  return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
  m_next = next;
}

//**********Stack Class Declaration***********
template <typename T> //Indicates linked list is templated
class Stack {
public:
  // Name: Stack (Default constructor)
  // Description: Creates a new Stack object
  // Preconditions: None
  // Postconditions: Creates a new Stack object
  Stack();
  // Name: ~Stack
  // Description: Stack destructor - deallocates all nodes in linked list
  // Preconditions: None
  // Postconditions: All nodes are deleted. Size is 0. No memory leaks.
  ~Stack();
  // Name: Stack (Copy constructor)
  // Description: Creates a new Stack object based on existing stack
  // Preconditions: None
  // Postconditions: Creates a new Stack object from existing stack
  //                 in separate memory space
  Stack(const Stack& source);
  // Name: Stack<T>& operator= (Assignment operator)
  // Description: Makes two stacks identical based on source.
  // Preconditions: None
  // Postconditions: Two stacks with same number of nodes and same values
  //                 in each node in a separate memory space
 Stack<T>& operator=(const Stack& other);
  // Name: Push
  // Description: Adds a new node to the top of the stack
  // Preconditions: None
  // Postconditions: Adds a new node to the top of the stack
  void Push(const T& value);
  // Name: Pop
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Temporarily stores data from node at the top of the stack.
  //              Removes the node from the top of the stack. Returns the stored data.
  // Preconditions: Stack has at least one node
  // Postconditions: See description
  T Pop();
  // Name: Peek
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Returns the stored data from top node.
  // Preconditions: Stack has at least one node
  // Postconditions: See description
 T Peek() const;
  // Name: At
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Returns stored data from number of the node passed to function.
  //              At(3) would return the data from the fourth node.
  // Preconditions: Stack has at least one node
  // Postconditions: Returns data from number of node starting at m_top
  T At(int num);
  // Name: IsEmpty
  // Description: Returns if the stack has any nodes.
  // Preconditions: Stack has at least one node
  // Postconditions: If stack has no nodes, returns true. Else false.
  bool IsEmpty() const;
  // Name: RemoveBottom
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Temporarily stores data from node at the bottom of the sta\
ck.
  //              Removes node from bottom of the stack. Returns the stored data.
  //              Similar to Pop but opposite end of stack
  // Preconditions: Stack has at least one node
  // Postconditions: Removes node from bottom of stack and returns data
  T RemoveBottom();
// Name: Display
  // Description: If stack is empty, outputs that the stack is empty
  //              Otherwise, iterates through stack and displays data in each node
  // Preconditions: Stack has at least one node
  // Postconditions: Displays data from each node in stack
  void Display();
  // Name: GetSize
  // Description: Returns the number of nodes in the stack
  // Preconditions: None
  // Postconditions: Returns the number of nodes in the stack.
  size_t GetSize() const;
private:
  Node<T>* m_top; //Top node in stack
  size_t m_size; //Number of nodes in stack
};

//*********************STACK FUNCTIONS IMPLEMENTED HERE******************

// Name: Stack (Default constructor)
// Description: Creates a new Stack object
// Preconditions: None
// Postconditions: Creates a new Stack object
template <typename T>
Stack<T>::Stack(){
  m_top = nullptr;
  m_size = 0;
}

// Name: ~Stack (Destructor)
// Description: Stack destructor - deallocates all nodes in linked list
// Preconditions: None
// Postconditions: All nodes are deleted. Size is 0. No memory leaks.
template <typename T>
Stack<T>::~Stack(){
  Node<T>* curr = m_top;
  while(curr != nullptr){ //loop trough entire stack
    Node<T>* temp = curr; 
    curr = curr->GetNext();
    delete temp; //delete the previous node
  }
  m_top = nullptr; //free m_top ptr
  m_size = 0; //reset size
}

// Name: Stack (Copy constructor)
// Description: Creates a new Stack object based on existing stack
// Preconditions: None
// Postconditions: Creates a new Stack object from existing stack
//                 in separate memory space
template <typename T>
Stack<T>::Stack(const Stack& source){
  //start with an empty stack
  m_top = nullptr;
  m_size = 0;

  if(source.m_top != nullptr){ //first make sure the original isn't empty also

    //First node copy
    m_top = new Node<T>(source.m_top->GetData()); //creates the first node in the copy stack
    m_size++; //increment size to 1

    //Every node that follows
    Node<T>* curr = m_top;
    Node<T>* sourceCurr = source.m_top->GetNext();
    while (sourceCurr != nullptr){
      Node<T>* newNode = new Node<T>(sourceCurr->GetData()); //mkae a new node
      curr->SetNext(newNode); //insert the node into the copy stack
      //traverse one node over in both stacks
      curr = newNode;
      sourceCurr = sourceCurr->GetNext();
      //incerement size of copy stack
      m_size++;
    }
  }
}

// Name: Stack<T>& operator= (Assignment operator)
// Description: Makes two stacks identical based on source.
// Preconditions: None
// Postconditions: Two stacks with same number of nodes and same values
//                 in each node in a separate memory space
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other){
  //first make sure they already aren't the same stack already
  if (this == &other){ //compare memory addresses
    return *this;
  }
  else{
    //clear current stack (reference the destructor)
    Node<T>* curr = m_top;
    while(curr != nullptr){ //loop trough entire stack
      Node<T>* temp = curr; 
      curr = curr->GetNext();
      delete temp; //delete the previous node
    }
    m_top = nullptr; //free m_top ptr
    m_size = 0; //reset size

    //Copy the current stack from other (reference the copy constructor)
    //First node copy
    m_top = new Node<T>(other.m_top->GetData()); //creates the first node in the copy stack
    m_size++; //increment size to 1

    //Every node that follows
    curr = m_top;
    Node<T>* otherCurr = other.m_top->GetNext();
    while (otherCurr != nullptr){
      Node<T>* newNode = new Node<T>(otherCurr->GetData()); //mkae a new node
      curr->SetNext(newNode); //insert the node into the copy stack
      //traverse one node over in both stacks
      curr = newNode;
      otherCurr = otherCurr->GetNext();
      //incerement size of copy stack
      m_size++;
    }
  }
  return *this;
}
  
// Name: Push
// Description: Adds a new node to the top of the stack
// Preconditions: None
// Postconditions: Adds a new node to the top of the stack
template <typename T>
void Stack<T>::Push(const T& value){
  Node<T>* newNode = new Node<T>(value); //create new node
  newNode->SetNext(m_top); //insert it at the top
  m_top = newNode; //reassign the new top of the stack
  m_size++; //increment size
}

// Name: Pop
// Description: If stack is empty, throw runtime_error("Stack is empty");
//              Temporarily stores data from node at the top of the stack.
//              Removes the node from the top of the stack. Returns the stored data.
// Preconditions: Stack has at least one node
// Postconditions: See description
template <typename T>
T Stack<T>::Pop(){
  T data;
  if (m_top == nullptr){ //If empty error
    throw runtime_error("Stack is empty.");
  }
  else{
    Node<T>* temp = m_top;
    data = temp->GetData(); //store data at the top of the stack
    m_top = m_top->GetNext(); //move top ptr down one (which will be the top node after deletion)
    delete temp; //delete the top node
    temp = nullptr; //free temp
  }
  return data;
}

// Name: Peek
// Description: If stack is empty, throw runtime_error("Stack is empty");
//              Returns the stored data from top node.
// Preconditions: Stack has at least one node
// Postconditions: See description
template <typename T>
T Stack<T>::Peek() const{
  if (m_top == nullptr){
    throw runtime_error("Stack is empty");
  }
  return m_top->GetData();
}
  
// Name: At
// Description: If stack is empty, throw runtime_error("Stack is empty")
//              Returns stored data from number of the node passed to function.
//              At(3) would return the data from the fourth node.
// Preconditions: Stack has at least one node
// Postconditions: Returns data from number of node starting at m_top
template <typename T>
T Stack<T>::At(int num){
  if (m_top == nullptr){ //if empty
    throw runtime_error("Stack is empty");
  }
  Node<T>* curr = m_top;
  for (int i = 0; i < num; i++){ //iterate unitl we get to index num
    curr = curr->GetNext(); //go one down the stack
  }
  return curr->GetData();
}

// Name: IsEmpty
// Description: Returns if the stack has any nodes.
// Preconditions: Stack has at least one node
// Postconditions: If stack has no nodes, returns true. Else false.
template <typename T>
bool Stack<T>::IsEmpty() const{return m_top == nullptr;}

// Name: RemoveBottom
// Description: If stack is empty, throw runtime_error("Stack is empty")
//              Temporarily stores data from node at the bottom of the stack.
//              Removes node from bottom of the stack. Returns the stored data.
//              Similar to Pop but opposite end of stack
// Preconditions: Stack has at least one node
// Postconditions: Removes node from bottom of stack and returns data
template <typename T>
T Stack<T>::RemoveBottom(){
  T data; //varaible to store deleted data
  if (m_top == nullptr){ //if empty
    throw runtime_error("Stack is empty");
  }
  else if(m_top->GetNext() == nullptr){ //if theres only 1 node in the stack
    data = m_top->GetData();
    delete m_top; //delete the only node in the stack
    m_top = nullptr;
    m_size = 0; //size will be 0 as the stack is empty now
    return data;
  }
  Node<T>* prev = m_top;
  Node<T>* temp = m_top->GetNext();
  while (temp->GetNext() != nullptr){ //iterate unitl bottom node of the stack
    prev = temp;
    temp = temp->GetNext();
  }
  data = temp->GetData(); //store last node data
  delete temp; //delete the last node
  prev->SetNext(nullptr); //set the second-to-last (new bottm node) ptr to nullptr
  m_size--; //decrement size
  return data;
}

// Name: Display
// Description: If stack is empty, outputs that the stack is empty
//              Otherwise, iterates through stack and displays data in each node
// Preconditions: Stack has at least one node
// Postconditions: Displays data from each node in stack
template <typename T>
void Stack<T>::Display(){
  if (IsEmpty()) //if the stack is empty
    cout << "the stack is empty" << endl;
  else{
    Node<T>* temp = m_top;
    int i = 1; //for printing node numbers in a list format
    while(temp != nullptr){
      cout << i << ". " << temp->GetData() << endl; //display the data of the node
      temp = temp->GetNext(); //move down the stack one
      i++;
    }
  }
}

// Name: GetSize
// Description: Returns the number of nodes in the stack
// Preconditions: None
// Postconditions: Returns the number of nodes in the stack.
template <typename T>
size_t Stack<T>::GetSize() const{return m_size;}

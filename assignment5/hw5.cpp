/* @Author
Student Name: Burak Bozdað
Student ID : 150170110
Date: 22.12.2018 */

#include <fstream> //ifstream
#include <iostream> //cout
#include <sstream> //istringstream
#include <string> //string

using namespace std;

struct node { //Stack nodes
    unsigned long int value;
    node* next;
};

struct stack_of_nodes { //Stack
    node* head;
    void push(unsigned long int value);
    unsigned long int pop();
    int searchPath(unsigned long int* tree, unsigned long int index, long int subsum, unsigned long int counter);
    void result(); //Prints the result if a path is found
};

void stack_of_nodes::push(unsigned long int value)
{ //Pushes values into the stack
    node* temp = new node; //New value for stack
    temp->value = value;
    temp->next = head;
    head = temp;
}

unsigned long int stack_of_nodes::pop()
{ //Pops values from the stack
    node* temp = head;
    unsigned long int popped = temp->value;
    head = head->next;
    delete temp;
    return popped;
}

int stack_of_nodes::searchPath(unsigned long int* tree, unsigned long int index, long int subsum, unsigned long int counter)
{
    if (index >= counter) { //Root check
        if (subsum == 0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        push(tree[index]);
        int checker = 0;
        long int subsubsum = subsum - tree[index];
        if (subsubsum == 0) //Path found
            return 1;
        if (subsubsum < 0) { //Wrong path
            pop();
            return 0;
        }
        if ((index + 1) * 2 - 1 < counter) //Go left
            checker = checker || searchPath(tree, (index + 1) * 2 - 1, subsubsum, counter);
        if ((index + 1) * 2 < counter) //Go right
            checker = checker || searchPath(tree, (index + 1) * 2, subsubsum, counter);
        if (checker == 0) //Wrong path
            pop();
        return checker;
    }
}

void stack_of_nodes::result()
{
    stack_of_nodes stack; //New stack for reversal order
    stack.head = new node;
    stack.head->value = pop();
    stack.head->next = NULL;
    while (head != NULL) {
        node* creator = new node;
        creator->value = pop();
        creator->next = stack.head;
        stack.head = creator;
    }
    cout << "Path Found: ";
    while (stack.head != NULL) { //Printing the reversed stack
        cout << stack.pop() << " ";
    }
    cout << endl;
}

int main(int argc, char** argv)
{
    ifstream readFile(argv[1]); //Opening file
    string line;
    getline(readFile, line); //Reading the first line of the file

    istringstream values(line);
    unsigned long int counter = 0, value;
    while (values >> value) //Counting the number of elements in the tree
        counter++;
    values.clear();
    values.seekg(0, ios::beg);

    unsigned long int* tree = new unsigned long int[counter]; //New array to store the tree

    for (unsigned long int i = 0; values >> value; i++) //Reading values of the tree
        tree[i] = value;

    unsigned long int sum;
    readFile >> sum;
    long int subsum = sum - tree[0]; //Path always includes root

    stack_of_nodes stack; //New stack to store results
    stack.head = new node;
    stack.head->value = tree[0];
    stack.head->next = NULL;

    unsigned long int index = 1; //Left sub-tree
    if (stack.searchPath(tree, index, subsum, counter)) {
        stack.result();
    } else {
        cout << "No Path Found" << endl;
    }

    while (stack.head != NULL) //Resetting stack
        stack.pop();
    stack.head = new node;
    stack.head->value = tree[0];
    stack.head->next = NULL;

    index = 2; //Right sub-tree
    if (stack.searchPath(tree, index, subsum, counter)) {
        stack.result();
    } else {
        cout << "No Path Found" << endl;
    }

    delete[] tree;
    readFile.close();
    return 0;
}

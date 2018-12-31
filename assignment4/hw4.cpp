/* @Author
Student Name: Burak Bozdað
Student ID : 150170110
Date: 04.12.2018 */

#include <fstream> //ifstream
#include <iostream> //cout

using namespace std;

struct queueAnt { //queue
    unsigned long int value;
    queueAnt* next;
};

struct stackAnt { //stack
    unsigned long int value;
    stackAnt* next;
};

struct Ants {
    queueAnt* ants; //first ant
    queueAnt* holeDepths; //first hole
    stackAnt* hole; //head of stacked ants
    void ReadFile(char*); //reads the file dynamically
    void ShowContents(bool); //output creator
    void CrossRoad(); //the main process of the program
};

void Ants::ReadFile(char* argv)
{
    ifstream readFile(argv); //opening file

    ants = new queueAnt; //creating a new queue for ants
    ants->value = 0;
    ants->next = NULL;
    unsigned long int temp = 0;
    readFile >> temp; //reading the ant count
    queueAnt* previous = ants;
    for (unsigned long int i = 1; i <= temp; i++) { //creating the ant queue
        if (ants->value == 0) { //for the first ant
            ants->value = i;
        } else {
            queueAnt* creator = new queueAnt;
            creator->value = i;
            creator->next = NULL;
            previous->next = creator;
            previous = creator;
        }
    }

    holeDepths = new queueAnt; //creating a new queue for hole depths
    holeDepths->value = 0;
    holeDepths->next = NULL;
    previous = holeDepths;
    while (!readFile.eof()) {
        readFile >> temp; //reading hole depths
        if (readFile.eof()) { //until end of file
            break;
        }
        if (holeDepths->value == 0) { //the first hole depth inserting
            holeDepths->value = temp;
        } else {
            queueAnt* creator = new queueAnt;
            creator->value = temp;
            creator->next = NULL;
            previous->next = creator;
            previous = creator;
        }
    }
}

void Ants::ShowContents(bool queue)
{
    queueAnt* temp = queue ? ants : holeDepths; //selecting a queue to print
    do {
        cout << temp->value << " ";
        temp = temp->next;
    } while (temp != NULL);
    cout << endl;
}

void Ants::CrossRoad()
{
    while (holeDepths != NULL) { //continue until all holes are passed
        unsigned long int depth = holeDepths->value; //getting ready for the next hole
        queueAnt* deleter = holeDepths;
        holeDepths = holeDepths->next;
        delete deleter;

        hole = new stackAnt; //creating stack for incoming hole
        hole->value = 0;
        hole->next = NULL;
        for (unsigned long int i = 0; i < depth; i++) { //inserting ants to the stack
            if (hole->value == 0) { //for the first time
                hole->value = ants->value;
                queueAnt* temp = ants;
                ants = ants->next;
                delete temp;
            } else {
                stackAnt* creator = new stackAnt;
                creator->value = ants->value;
                creator->next = hole;
                hole = creator;
                queueAnt* temp = ants;
                ants = ants->next;
                delete temp;
            }
        }

        queueAnt* traverse = ants;
        while (hole != NULL) { //rescuing ants from the stack
            while (traverse->next != NULL)
                traverse = traverse->next; //finding the last ant in the queue
            queueAnt* creator = new queueAnt;
            creator->value = hole->value;
            creator->next = NULL;
            traverse->next = creator;
            stackAnt* deleter = hole;
            hole = hole->next;
            delete deleter;
        }
    }
}

int main(int argc, char** argv)
{
    Ants a;
    a.ReadFile(argv[1]); // store the number of ants and depths of holes
    cout << "The initial Ant sequence is: ";
    a.ShowContents(1); // list ant sequence (initially: 1, 2, ..., N)
    cout << "The depth of holes are: ";
    a.ShowContents(0); // list depth of holes
    a.CrossRoad();
    cout << "The final Ant sequence is: ";
    a.ShowContents(1);

    return 0;
}

/*
 * main.cpp
 *
 *      Author: Burak Bozdað
 *      Number: 150170110
 */

#include <fstream> // ifstream
#include <iostream> //cout

using namespace std;

struct cardStack {
    long int cards[1000] = { 0 };
    int top = -1;

    void push(long int card);
    long int pop();
    long int peek();
    bool isEmpty();
};

void cardStack::push(long int card)
{
    cards[++top] = card; //Adds a card to the stack
}

long int cardStack::pop()
{
    if (isEmpty())
        return 0;
    long int card = cards[top];
    cards[top--] = 0; //Deletes a card from the stack
    return card; //Returns the deleted card
}

long int cardStack::peek()
{
    if (isEmpty())
        return 0;
    return cards[top]; //Returns the top of the stack
}

bool cardStack::isEmpty()
{
    if (top < 0)
        return true; //Returns that stack is empty
    return false; //Returns that stack is not empty
}

void theGame(cardStack* tableDeck, cardStack* player1Deck, cardStack* player2Deck)
{
    int bin = 0;
    bool turn = true; //Player turn indicator
    while (!tableDeck->isEmpty()) {
        if (turn) { //First player's turn
            long int card = tableDeck->pop(); //Taking a card from table
            if (card < 0) { //First player gives card
                for (long int i = 0; i < card * -1 && !player1Deck->isEmpty(); i++) {
                    if (player1Deck->peek() > player2Deck->peek()) { //Checking cards
                        player2Deck->push(player1Deck->pop());
                    } else {
                        player1Deck->pop();
                        bin++; //Throwing the card to the bin
                    }
                }
            } else { //First player takes card
                for (long int i = 0; i < card && !player2Deck->isEmpty(); i++) {
                    if (player2Deck->peek() > player1Deck->peek()) { //Checking cards
                        player1Deck->push(player2Deck->pop());
                    } else {
                        player2Deck->pop();
                        bin++; //Throwing the card to the bin
                    }
                }
            }
            turn = !turn; //The next turn
        } else { //Second player's turn
            long int card = tableDeck->pop(); //Taking a card from table
            if (card < 0) { //Second player gives card
                for (long int i = 0; i < card * -1 && !player2Deck->isEmpty(); i++) {
                    if (player2Deck->peek() > player1Deck->peek()) { //Checking cards
                        player1Deck->push(player2Deck->pop());
                    } else {
                        player2Deck->pop();
                        bin++; //Throwing the card to the bin
                    }
                }
            } else { //Second player takes card
                for (long int i = 0; i < card && !player1Deck->isEmpty(); i++) {
                    if (player1Deck->peek() > player2Deck->peek()) { //Checking cards
                        player2Deck->push(player1Deck->pop());
                    } else {
                        player1Deck->pop();
                        bin++; //Throwing the card to the bin
                    }
                }
            }
            turn = !turn; //The next turn
        }
    }
    cout << bin << endl; //The number of cards in the bin
}

int main(int argc, char** argv)
{
    if (argc != 2) //Argument error check
        return 1;

    ifstream readFile(argv[1]); //Opening file

    int tableDeckCount, playerDeckCount; //Max 1000
    readFile >> tableDeckCount >> playerDeckCount;

    cardStack* tableDeck = new cardStack;
    long int card;
    for (int i = 0; i < tableDeckCount; i++) {
        readFile >> card;
        tableDeck->push(card); //Adding cards to the table
    }

    cardStack* player1Deck = new cardStack;
    for (int i = 0; i < playerDeckCount; i++) {
        readFile >> card;
        player1Deck->push(card); //Selecting cards for 1st player
    }

    cardStack* player2Deck = new cardStack;
    for (int i = 0; i < playerDeckCount; i++) {
        readFile >> card;
        player2Deck->push(card); //Selecting cards for 2nd player
    }

    theGame(tableDeck, player1Deck, player2Deck); //Starting the game

    return 0;
}

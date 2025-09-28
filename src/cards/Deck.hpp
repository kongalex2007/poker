#ifndef DECK_HPP
#define DECK_HPP
#include <array>
#include "Card.hpp"
#include <string>

using namespace std;

class Deck {
public:


    Deck(); //initialzes deck to A-K of Spades Hearts Clubs Diamonds in that order

    Deck(std::istream& pack_input);

    Card deal_one();

    void faro_shuffle();

    void cut();

    Card deal();
    
    void reset();

    bool empty() const;



private:
    static const int DECK_SIZE = 52;
    array<Card, DECK_SIZE> cards;
    int next;   //next deal


};

#endif
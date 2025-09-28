#include "Deck.hpp"
using namespace std;
#include <array>



Deck::Deck(){
    next = 0;
    for(int j = 0; j < 4; j++){
        for(int i = 7; i < 13; i++){
            Card c(static_cast<Rank>(i),static_cast<Suit>(j));
            cards.at(j*6 + (i-7)) = c;
        }
    }
}

Card Deck::deal_one(){
    Card c = cards.at(next);
    next++;
    return c;
}

void Deck::reset(){
    next = 0;
}

void Deck::faro_shuffle(){
    array<Card, Deck::DECK_SIZE> copy;
    int half = Deck::DECK_SIZE / 2;
    // Interleave the two halves
    for (int i = 0; i < half; ++i) {
        copy[2 * i] = cards[i];
        copy[2 * i + 1] = cards[i + half];
    }
    // Copy back to the deck
    for (int i = 0; i < DECK_SIZE; ++i) {
        cards[i] = copy[i];
    }
    // Reset next to 0 after shuffle (optional)
    next = 0;
}

void Deck::cut(){
    array<Card, Deck::DECK_SIZE> copy;
    int half = Deck::DECK_SIZE / 2;
    for(int i = 0; i < half; i++){
        copy[i] = cards[i + half];
        copy[i + half] = cards[i];
    }
    for (int i = 0; i < DECK_SIZE; i++) {
        cards[i] = copy[i];
    }
    next = 0;
}




bool Deck::empty() const{
    if(next == cards.size()){
        return true;
    }
    return false;
}
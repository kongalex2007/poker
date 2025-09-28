#ifndef RANGE_HPP
#define RANGE_HPP

#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"
#include <vector>

using namespace std;


struct HandPair{
    Card c1;
    Card c2;
    double prob;
    double suitedprob;
    double offsuitprob;
    array<double, 16> suit_combo_probs;
    HandPair(Card card1, Card card2, double probability)
        : c1(card1), c2(card2), prob(probability), suitedprob(0.0), offsuitprob(0.0) {
            suit_combo_probs.fill(0.0);
        }
    
    HandPair() : c1(Card()), c2(Card()), prob(0.0), suitedprob(0.0), offsuitprob(0.0) {
            suit_combo_probs.fill(0.0);
        }

};



class Range {
public:
    static const int NUM_CARDS = 52;
    static const int NUM_HANDS = 1326;
    static const int NUM_RANKS = 13;
    static const int NUM_SUITS = 4;
    static const int NUM_COMBO_SUITS = 16; //number of suit combinations for two different ranks, including suited

    //encoding: suit(c1) * 4 + suit(c2) MAKE SURE C1 > C2, if C1 = C2 then sort by suit first
    //suited: 0, 5, 10, 15 (mod 5!! beautiful)
    //pocket pairs: 1, 2, 3, 6, 7, 11
    /*
    enum Suit {
        SPADES    = 0,
        HEARTS    = 1,
        CLUBS     = 2,
        DIAMONDS  = 3,
    };
    */

    Range();

    ~Range();

    // Get probability for a hand (two cards, order doesn't matter)
    double get_prob(const array<Card, HAND_SIZE> hand){
        
    }

    void set_prob(array<Card, HAND_SIZE> hand, double prob){
        
    }


    double get_suited_prob(const array<Card, HAND_SIZE> hand){

    }


    void set_suited_prob(array<Card, HAND_SIZE> hand, double prob){

    }



    double get_offsuit_prob(const array<Card, HAND_SIZE> hand){
        
    }


    void set_offsuit_prob(array<Card, HAND_SIZE> hand, double prob){

    }

    double get_specific_prob(const array<Card, HAND_SIZE> hand){
    }


    void set_specific_prob(array<Card, HAND_SIZE> hand, double prob){

    }

    void update_probs(){
        
    }

private:

    HandPair range [NUM_RANKS][NUM_RANKS];
};




/*
inline Range::Range() {
    probs.fill(0.0);
}

inline Range::~Range() {}


inline int Range::hand_index(const Card& c1, const Card& c2) {
    // Map two cards to a unique index (order doesn't matter)
    // Card index: 0..51 (suit*13 + rank-1)
    int i = static_cast<int>(c1.get_suit()) * 13 + static_cast<int>(c1.get_rank()) - 1;
    int j = static_cast<int>(c2.get_suit()) * 13 + static_cast<int>(c2.get_rank()) - 1;
    if (i > j) std::swap(i, j);
    // index in upper triangle (excluding diagonal)
    return i * (NUM_CARDS - 1) - (i * (i + 1)) / 2 + (j - i - 1);
}

inline double Range::get_prob(const Card& c1, const Card& c2) const {
    return probs[hand_index(c1, c2)];
}

inline void Range::set_prob(const Card& c1, const Card& c2, double prob) {
    probs[hand_index(c1, c2)] = prob;
}
*/






#endif
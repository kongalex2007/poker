#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"
#include "Range.hpp"

using namespace std;
    static const int NUM_CARDS = 52;
    static const int NUM_HANDS = 1326;
    static const int NUM_RANKS = 13;
    static const int NUM_SUITS = 4;
    static const int NUM_COMBO_SUITS = 16;
    static const int HAND_SIZE = 2;

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



Range::Range(){
    for(int i = 0; i < NUM_RANKS; i++){
        for(int j = 0; j < NUM_RANKS; j++){
            if(i == j){
                for(int s = 0; s < NUM_SUITS; s ++){
                    for(int t = s + 1; t < NUM_SUITS; t ++){
                        range[i][j].suit_combo_probs[s * 4 + t] = 1.0 / NUM_HANDS;
                    }
                }
            } 
            else {
                for(int s = 0; s < NUM_SUITS; s++){
                    for(int t = 0; t < NUM_SUITS; t++){
                        if(s == t){
                            range[i][j].suit_combo_probs[s * 4 + t] = 1.0 / NUM_HANDS;
                        } 
                        else {
                            range[i][j].suit_combo_probs[s * 4 + t] = 1.0 / NUM_HANDS;
                        }
                    }
                }
            }
        }

    }

    //what in the fuck????
}


    double Range::get_prob(const array<Card, HAND_SIZE> hand){
        return (range[hand[0].get_rank()][hand[1].get_rank()].prob);
    }

    void Range::set_prob(array<Card, HAND_SIZE> hand, double prob){
        
    }


    double Range::get_suited_prob(const array<Card, HAND_SIZE> hand){
        return (range[hand[0].get_rank()][hand[1].get_rank()].suitedprob);
    }


    void Range::set_suited_prob(array<Card, HAND_SIZE> hand, double prob){

    }


    double Range::get_offsuit_prob(const array<Card, HAND_SIZE> hand){
        return (range[hand[0].get_rank()][hand[1].get_rank()].offsuitprob);
    }


    void Range::set_offsuit_prob(array<Card, HAND_SIZE> hand, double prob){

    }

    double Range::get_specific_prob(const array<Card, HAND_SIZE> hand){
        return (range[hand[0].get_rank()][hand[1].get_rank()].suit_combo_probs[hand[0].get_suit() * 4 + hand[1].get_rank()]);
    }


    void Range::set_specific_prob(array<Card, HAND_SIZE> hand, double prob){
        double temp = get_specific_prob(hand);
        range[hand[0].get_rank()][hand[1].get_rank()].suit_combo_probs[hand[0].get_suit() * 4 + hand[1].get_rank()] = prob;

    }

    void Range::update_probs(){
        for(int i = 0; i < NUM_RANKS; i++){
            for(int j = 0; j < NUM_RANKS; j++){
                if(i == j){
                    range[i][j].prob = 0.0;
                    range[i][j].suitedprob = 0.0;
                    range[i][j].offsuitprob = 0.0;
                    for(int s = 0; s < NUM_SUITS; s++){
                        for(int t = s + 1; t < NUM_SUITS; t++){
                            range[i][j].prob += range[i][j].suit_combo_probs[s * 4 + t];
                            range[i][j].offsuitprob += range[i][j].suit_combo_probs[s * 4 + t];
                        }
                    }
                } 
                else {
                    range[i][j].prob = 0.0;
                    range[i][j].suitedprob = 0.0;
                    range[i][j].offsuitprob = 0.0;
                    for(int s = 0; s < NUM_SUITS; s++){
                        for(int t = 0; t < NUM_SUITS; t++){
                            if(s == t){
                                range[i][j].prob += range[i][j].suit_combo_probs[s * 4 + t];
                                range[i][j].suitedprob += range[i][j].suit_combo_probs[s * 4 + t];
                            } 
                            else {
                                range[i][j].prob += range[i][j].suit_combo_probs[s * 4 + t];
                                range[i][j].offsuitprob += range[i][j].suit_combo_probs[s * 4 + t];
                            }
                        }
                    }
                }
            }

        }
    }


Range::~Range() {}



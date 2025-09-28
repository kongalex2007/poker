#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP
#include <array>
#include <vector>
#include "Card.hpp"
#include <string>



struct GameState {

    int pot;                //size of pot

    int player_chips[2];

    std::vector<Card> board;

    std::vector<Card> player_hands[2];

    int betting_round;

    bool is_terminal() const;
    

};


#endif  
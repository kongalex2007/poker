#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <array>
#include "Card.hpp"
#include <string>
#include "Range.hpp"

using namespace std;

class Player {
    public:
        Player(string name_in, int chips_in, int position_in);

        array<Card, 2> get_hand() const;

        void deal_card(const Card& card, int index);

        int get_chips() const;

        void adjust_chips(int amount);

        int get_position() const;

        int get_current_bet() const;

        void set_current_bet(int amount);

        bool has_folded() const;

        void fold();

        bool is_all_in() const;

        void set_all_in(bool all_in_status);

        bool has_acted_this_round() const;

        void set_acted_this_round(bool acted);

        bool is_dealer_button() const;

        void set_dealer_button(bool is_dealer_status);

        Range get_range();

        string get_name() const;






    private:
        static const int HAND_SIZE = 2;
        static const int CARD_SIZE = 13;
        static const int MAX_COMBO_SUITS_SIZE = 12;
        array<Card, HAND_SIZE> hand;
        Range range;
    

        int chips;
        int position; //0 = SB, 1 = BB, 2 = UTG, etc
        int current_bet;
        bool folded;
        bool all_in;
        bool acted_this_round;
        bool is_dealer;
        string name;
};




#endif
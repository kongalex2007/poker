#include <array>
#include "Card.hpp"
#include <string>
#include "Player.hpp"
#include "Range.hpp"
using namespace std;


Player::Player(std::string name_in, int chips_in, int position_in)
    : name(name_in), chips(chips_in), position(position_in), current_bet(0),
      folded(false), all_in(false), acted_this_round(false), is_dealer(false), range(Range()) {
    hand.fill(Card()); // Initialize hand with default cards
}

array<Card, 2> Player::get_hand() const {
    return hand;
}

void Player::deal_card(const Card& card, int index) {
    if (index >= 0 && index < hand.size()) {
        hand[index] = card;
    }
}

int Player::get_chips() const {
    return chips;
}

void Player::adjust_chips(int amount) {
    chips += amount;
}

int Player::get_position() const {
    return position;
}

int Player::get_current_bet() const {
    return current_bet;
}
void Player::set_current_bet(int amount) {
    current_bet = amount;
}

bool Player::has_folded() const {
    return folded;
}

void Player::fold() {
    folded = true;
}

bool Player::is_all_in() const {
    return all_in;
}

void Player::set_all_in(bool all_in_status) {
    all_in = all_in_status;
}

bool Player::has_acted_this_round() const {
    return acted_this_round;
}

void Player::set_acted_this_round(bool acted) {
    acted_this_round = acted;
}

bool Player::is_dealer_button() const {
    return is_dealer;
}

void Player::set_dealer_button(bool is_dealer_status) {
    is_dealer = is_dealer_status;
}

string Player::get_name() const {
    return name;
}

Range Player::get_range() {
    return range;
}
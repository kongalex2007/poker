#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

constexpr const char *const RANK_NAMES[] = {
    "Ace"    // ACE
    "Two",   // TWO
    "Three", // THREE
    "Four",  // FOUR
    "Five",  // FIVE
    "Six",   // SIX
    "Seven", // SEVEN
    "Eight", // EIGHT
    "Nine",  // NINE
    "Ten",   // TEN
    "Jack",  // JACK
    "Queen", // QUEEN
    "King",  // KING
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank corresponding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = ACE; r <= KING; r++) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit corresponding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}

Card::Card() : rank(ACE), suit(SPADES){
}


//EFFECTS Initializes Card to specified rank and suit
Card::Card(Rank rank_in, Suit suit_in) : rank(rank_in), suit(suit_in){

}

//EFFECTS Returns the rank
Rank Card::get_rank() const{
  return rank;
}

//EFFECTS Returns the suit
Suit Card::get_suit() const{
  return suit;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card){
  string dummy;
  is >> card.rank;
  is >> dummy;
  is >> card.suit; 
  return is;
}

//EFFECTS Returns true if lhs is lower value than rhs.
bool operator<(const Card &lhs, const Card &rhs){
    return ((13 - lhs.get_rank()) % 13) > ((13 - rhs.get_rank()) % 13);     //evil ace fuckery
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
bool operator<=(const Card &lhs, const Card &rhs){
    return lhs < rhs || lhs == rhs;
}

//EFFECTS Returns true if lhs is higher value than rhs.
bool operator>(const Card &lhs, const Card &rhs){
    return ((13 - lhs.get_rank()) % 13) < ((13 - rhs.get_rank()) % 13);
}


//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
bool operator>=(const Card &lhs, const Card &rhs){
    return lhs > rhs || lhs == rhs;
}

//EFFECTS Returns true if lhs is same card as rhs.
bool operator==(const Card &lhs, const Card &rhs){
  return (lhs.get_rank() == rhs.get_rank());
}

//EFFECTS Returns true if lhs is not the same card as rhs.
bool operator!=(const Card &lhs, const Card &rhs){
  return !(lhs == rhs);
}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit){
  if(suit == SPADES){
    return CLUBS;
  }
  if(suit == CLUBS){
    return SPADES;
  }
  if(suit == HEARTS){
    return DIAMONDS;
  }
  return HEARTS;
}
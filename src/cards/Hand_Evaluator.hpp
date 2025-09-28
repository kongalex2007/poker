#ifndef HAND_EVALUATOR_HPP
#define HAND_EVALUATOR_HPP
#include "Card.hpp"
#include <vector>

// Returns an integer representing the strength of the hand (higher is stronger)
int evaluate_hand(const std::vector<Card>& cards);

#endif

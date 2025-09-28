#include "Hand_Evaluator.hpp"
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

// Helper functions for hand evaluation
namespace {
    // Returns true if at least 5 cards are the same suit (flush)
    bool is_flush(const vector<Card>& cards) {
        if (cards.size() < 5) return false;
        map<Suit, int> suit_counts;
        for (const auto& c : cards) {
            suit_counts[c.get_suit()]++;
        }
        for (const auto& kv : suit_counts) {
            if (kv.second >= 5) return true;
        }
        return false;
    }

    // Returns true if any 5-card subset forms a straight
    bool is_straight(const vector<Card>& cards) {
        if (cards.size() < 5) return false;
        vector<int> ranks;
        for (const auto& c : cards) ranks.push_back(static_cast<int>(c.get_rank()));
        sort(ranks.begin(), ranks.end());
        // Remove duplicates
        ranks.erase(unique(ranks.begin(), ranks.end()), ranks.end());
        // Check all 5-card windows
        
        // Handle Ace-low straight
        if (ranks.back() == 13 && ranks[0] == 1) {
            ranks.insert(ranks.begin(), 0);
        }        
        for (int i = 0; i + 4 < ranks.size(); i++) {
            vector<int> window(ranks.begin() + i, ranks.begin() + i + 5);
            bool straight = true;
            for (int j = 1; j < 5; ++j) {
                if (window[j] != window[j-1] + 1) {
                    straight = false;
                    break;
                }
            }
            if (straight) return true;
        }
        return false;
    }


    //returns is straight flush
    bool is_straight_flush(const vector<Card>& cards) {
        if (cards.size() < 5) return false;
        map<Suit, int> suit_counts;
        for (const auto& c : cards) {
            suit_counts[c.get_suit()]++;
        }
        for (const auto& kv : suit_counts) {
            if (kv.second >= 5){
                vector<Card> suited_cards;
                for(const auto& card : cards){
                    if(card.get_suit() == kv.first){
                        suited_cards.push_back(card);
                        return is_straight(suited_cards);
                    }
                }
            }
        }
        return false;
    }

    

    // Returns a map of rank counts
    map<int, int> get_rank_counts(const vector<Card>& cards) {
        map<int, int> counts;
        for (const auto& c : cards) {
            counts[static_cast<int>(c.get_rank())]++;
        }
        return counts;
    }
}

// Returns an integer representing the strength of the hand (higher is stronger)
int evaluate_hand(const vector<Card>& cards) {
    if (cards.size() < 2 || cards.size() > 7) return 0;
    // Poker hand strength encoding
    // 9: Straight Flush
    // 8: Four of a Kind
    // 7: Full House
    // 6: Flush
    // 5: Straight
    // 4: Three of a Kind
    // 3: Two Pair
    // 2: One Pair
    // 1: High Card


    bool flush = is_flush(cards);
    bool straight = is_straight(cards);
    bool straight_flush = false;
    if(straight && flush){
        straight_flush = is_straight_flush(cards);
    }
    
    auto rank_counts = get_rank_counts(cards);
    int max_count = 0, pairs = 0, trips = 0;

    for (const auto& kv : rank_counts) {
        if (kv.second > max_count) max_count = kv.second;
        if (kv.second == 2) pairs++;
        if (kv.second == 3) trips++;
    }

    // Sub Hand strengh encoding:
    // SF : 9000000 + highest card in SF
    // Quads : 8000000 + rank of quads * 14 + highest other card (MAKE SURE TO DEAL WITH HIGHER PAIRS PROPERLY)
    // Full House : 7000000 + rank of trips * 14 + rank of highest other pair (DEAL WITH 2 TRIPS PROPERLY)
    // Flush : 6000000 + 14 encoding of top 5 cards in flush
    // Straight : 5000000 + highest card in straight
    // Trips : 4000000 + rank of trips * 14^2 + sum of next 2 highest cards (14 encoding)
    // Two Pair : 3000000 + 14 encoding (higher pair, lower pair, highest kicker)
    // One Pair : 2000000 + 14 encoding (pair, top 3 kickers)
    // High Card : 1000000 + 14 encoding (top 5 cards)

    // there HAS to be a more efficient way to do ts :wilted_rose:
        //use 14 encoding? 6000000 + top card*14^4 + next*14^3 + next*14^2 + next*14^1 + next*14^0
        //yeah that works ok sick

    // Sort cards by rank descending
    vector<int> ranks;
    for (const auto& c : cards) ranks.push_back(static_cast<int>(c.get_rank()));
    sort(ranks.rbegin(), ranks.rend());

    // Straight Flush
    if (straight && flush) {
        int high_card = ranks[0];
        return 9000000 + high_card;
    }

    // Four of a Kind
    if (max_count == 4) {
        int quad_rank = 0, kicker = 0;
        for (const auto& kv : rank_counts) {
            if (kv.second == 4) quad_rank = kv.first;
            else if (kv.second == 1) kicker = kv.first;
        }
        return 8000000 + quad_rank * 14 + kicker;
    }

    // Full House
    if (trips == 1 && pairs >= 1) {
        int trip_rank = 0, pair_rank = 0;
        for (const auto& kv : rank_counts) {
            if (kv.second == 3 && kv.first > trip_rank) trip_rank = kv.first;
        }
        for (const auto& kv : rank_counts) {
            if (kv.second >= 2 && kv.first != trip_rank && kv.first > pair_rank) pair_rank = kv.first;
        }
        return 7000000 + trip_rank * 14 + pair_rank;
    }

    // Flush
    if (flush) {
        int val = 6000000;
        for (int i = 0; i < min(5, (int)ranks.size()); ++i) {
            val += ranks[i] * pow(14, 4-i);
        }
        return val;
    }

    // Straight
    if (straight) {
        int high_card = ranks[0];
        return 5000000 + high_card;
    }

    // Three of a Kind
    if (max_count == 3) {
        int trip_rank = 0;
        vector<int> kickers;
        for (const auto& kv : rank_counts) {
            if (kv.second == 3) trip_rank = kv.first;
            else kickers.push_back(kv.first);
        }
        sort(kickers.rbegin(), kickers.rend());
        int val = 4000000 + trip_rank * pow(14,2);
        for (int i = 0; i < min(2, (int)kickers.size()); ++i) {
            val += kickers[i] * pow(14,1-i);
        }
        return val;
    }

    // Two Pair
    if (pairs == 2) {
        vector<int> pair_ranks, kickers;
        for (const auto& kv : rank_counts) {
            if (kv.second == 2) pair_ranks.push_back(kv.first);
            else kickers.push_back(kv.first);
        }
        sort(pair_ranks.rbegin(), pair_ranks.rend());
        int val = 3000000 + pair_ranks[0] * pow(14,2) + pair_ranks[1] * 14;
        if (!kickers.empty()) val += kickers[0];
        return val;
    }

    // One Pair
    if (pairs == 1) {
        int pair_rank = 0;
        vector<int> kickers;
        for (const auto& kv : rank_counts) {
            if (kv.second == 2) pair_rank = kv.first;
            else kickers.push_back(kv.first);
        }
        sort(kickers.rbegin(), kickers.rend());
        int val = 2000000 + pair_rank * pow(14,3);
        for (int i = 0; i < min(3, (int)kickers.size()); ++i) {
            val += kickers[i] * pow(14,2-i);
        }
        return val;
    }

    // High Card
    int val = 1000000;
    for (int i = 0; i < min(5, (int)ranks.size()); ++i) {
        val += ranks[i] * pow(14,4-i);
    }
    return val;
}

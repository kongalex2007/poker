#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "Player.hpp"

using namespace std;

enum class ActionType {
    FOLD,
    CALL,
    RAISE,
    CHECK,
    BET,
    DEAL,
};

struct Action {
    ActionType type;
    double amount;  // relevant for bet/raise, 0 otherwise

    Action(ActionType t, double amt = 0.0) : type(t), amount(amt) {}
};


class Node {
    public:

    Player currentPlayer;
    double potSize;
    vector<Action> history;
    vector<shared_ptr<Node>> children;
    bool isTerminal;
    double terminalUtility; // e.g., from showdown or fo  ld

    Node(Player p, double pot = 0.0)
        : currentPlayer(p), potSize(pot), isTerminal(false), terminalUtility(0.0) {}

    void addChild(shared_ptr<Node> child) {
        children.push_back(child);
    }




    

    string historyString() const {
        ostringstream oss;
        for (const auto &a : history) {
            switch (a.type) {
                case ActionType::FOLD:  oss << "F "; break;
                case ActionType::CALL:  oss << "C "; break;
                case ActionType::RAISE: oss << "R(" << a.amount << ") "; break;
                case ActionType::CHECK: oss << "X "; break;
                case ActionType::BET:   oss << "B(" << a.amount << ") "; break;
                case ActionType::DEAL:  oss << "D "; break;
            }
        }
        return oss.str();
    }
};




#endif
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
#include "Node.hpp"

//Tree construction for a simple heads-up poker game
/*
shared_ptr<Node> buildSimpleTree() {
    // Example: Heads-up preflop simplified tree
    auto root = make_shared<Node>(Player::PLAYER1, 1.5);

    // Player 1 options: fold, call, raise
    auto foldNode = make_shared<Node>(Player::TERMINAL);
    foldNode->isTerminal = true;
    foldNode->terminalUtility = -0.5; // Player 1 loses blind
    foldNode->history = { Action(ActionType::FOLD) };
    root->addChild(foldNode);

    auto callNode = make_shared<Node>(Player::PLAYER2);
    callNode->history = { Action(ActionType::CALL) };
    root->addChild(callNode);

    auto raiseNode = make_shared<Node>(Player::PLAYER2, 3.5);
    raiseNode->history = { Action(ActionType::RAISE, 2.0) };
    root->addChild(raiseNode);

    // Expand Player 2 responses here (fold/call/reraise)...

    return root;
}
//Tree traversal and printing
*/

void printTree(const shared_ptr<Node>& node, int depth = 0) {
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "[Player: " << static_cast<int>('a') //node->currentPlayer)
              << " | Pot: " << node->potSize
              << " | History: " << node->historyString() << "]\n";

    for (auto &child : node->children) {
        printTree(child, depth + 1);
    }
}

int main() {
    //auto root = buildSimpleTree();
    //printTree(root);
    return 0;
}

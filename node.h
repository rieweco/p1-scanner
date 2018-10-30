#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include "token.h"

using namespace std;

static int ROOT_LEVEL = 0;

class Node {
private:
    string value;
    bool nonTerminal;
    int level;
    vector<Node *> children;
public:
    Node(string value, bool nonTerminal, int level);
    ~Node();
    string &getValue();
    bool isNonTerminal();
    int getLevel();
    vector<Node *> &getChildren();
    void setChildren(vector<Node *> &children);
    string toString();
    string toStringMe();
    string toStringChildren();
};

#endif

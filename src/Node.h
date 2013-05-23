#include <iostream>

class Node
{
private:
    int count;
    char letter;
    Node *left, *right;
public:
    Node(Node *_left, Node *_right);
    
    Node(int _count, char _letter);
    
    static bool compare(const Node* l, const Node* r);
    
    bool hasChild();
    
    int getCount();
    
    char getLetter();
    
    Node *getChild(bool isLeft);
};
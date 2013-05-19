#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Node
{
    Node *_left, *_right;
    int _count;
    char _letter;
public:
    Node(int count, char letter);
    Node(Node *left, Node *right);
    static bool compare(Node *left, Node *right);
    void out(ostream &stream, int k);
    void buildTable(map< char, vector<bool> > &table, vector<bool> code);
};
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

typedef vector<bool> code;

class Node
{
    Node *_left, *_right;
    int _count;
    char _letter;
public:
    Node(int count, char letter);
    Node(Node *left, Node *right);
    static bool compare(Node *left, Node *right);
    void out(ostream &stream, int k = 50)
    void buildTable(map<char, code> &table, code _code);
};
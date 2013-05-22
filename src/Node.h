#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

typedef vector<bool> code;
typedef map<char, code> codeMap;

class Node
{
protected:
    Node *_left, *_right;
    int _count;
    char _letter;
private:
    void buildTable(codeMap &table, code _code);
public:
    Node(int count, char letter);
    Node(Node *left, Node *right);
    static bool compare(Node *left, Node *right);
    void out(ostream &stream, int k);
    codeMap getTable();
    bool isLast();
    char getLetter();
    Node *getChild(bool isRight);
};
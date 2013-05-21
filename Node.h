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
    char getLetter()
    {
        return _letter;
    }

    Node *getLeft()
    {
        return _left;
    }

    Node *getRight()
    {
        return _right;
    }

    bool isLast()
    {
        return (_right == NULL && _left == NULL);
    }
};
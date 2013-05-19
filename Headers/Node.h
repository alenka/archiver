class Node
{
    Node *_left, *_right;
    int _count;
    char _letter;
public:
    Node::Node(int count, char letter);
    Node::Node(Node *left, Node *right);
    static bool Node::compare(Node *left, Node *right);
    void Node::out(ostream &stream, int k = 5);
    void Node::buildTable(map< char, vector<bool> > &table, vector<bool> code = vector<bool>());
};
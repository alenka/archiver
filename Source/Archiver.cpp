class Archiver
{
private:
    list<Node*> _list;
    char *_source;
    unsigned long _sourceSize;
public:
    Archiver(char *source)
    {
        _source = source;
        _sourceSize = strlen(source);
        parseData();
    }
    void encode()
    {
        Node *tree = buildTree();
        tree->out(cout);
        map< char, vector<bool> > table;
        tree->buildTable(*&table);
        for(int i=0; i<_sourceSize; i++){
            char letter = _source[i];
            vector<bool> code = table[letter];
            for(int j = 0; j<code.size(); j++){
                cout<<code[j];
            }
        }
    }
    void parseData()
    {
        map<char, int> lettersCount;
        for(int i = 0; i < _sourceSize; i++){
            lettersCount[_source[i]]++;
        }

        map<char, int>::iterator i;
        for (i = lettersCount.begin(); i != lettersCount.end(); i++) {
            _list.push_back( new Node(i->second, i->first) );
        }
    }

    Node *buildTree()
    {
        while(_list.size() != 1){
            _list.sort(Node::compare);
            Node *left = _list.front();
            _list.pop_front();
            Node *right = _list.front();
            _list.pop_front();
            _list.push_back(new Node(left, right));
        }
        return _list.front();
    }
};
class Archiver
{
protected:
    char *_source;
public:
    Archiver();
    ~Archiver();
    decode();
    encode();
    out(ostream &out);
};
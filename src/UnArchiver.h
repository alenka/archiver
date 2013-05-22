#include "Compressor.cpp"

class UnArchiver : Compressor
{
protected:
    void loadLetters();
public:
    UnArchiver(const char *filename);
    bool run(const char *filename);
};
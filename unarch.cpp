#include "src/UnArchiver.cpp"

int main()
{
    UnArchiver unarch("resources/out.bin");
    unarch.run("resources/test.unarch.txt");
}
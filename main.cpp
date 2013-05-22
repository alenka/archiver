#include <iostream>
#include "src/Archiver.cpp"

using namespace std;

void printBool(const bool a)
{
    cout << endl << (a ? "true" : "false") << endl;
}

int main()
{
    Archiver arch("resources/test.txt");
    arch.run("resources/out.bin");
}
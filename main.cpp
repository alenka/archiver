#include <iostream>
#include "Archiver.cpp"

using namespace std;

void printBool(const bool a)
{
    cout << endl << (a ? "true" : "false") << endl;
}

int main()
{
    Archiver arch("test.txt");
    // printBool(arch.do("out.bin"));
}
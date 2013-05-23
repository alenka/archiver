#include "src/Archiver.cpp"

int main()
{
    Archiver arch("resources/test.txt");
    arch.run("out.bin");
}
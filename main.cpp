#include <iostream>
#include "Compressor.cpp"

int main()
{
    Compressor *c = new Compressor("Alena super star!!!");
    c->compress("out.bin");
    return 0;
}
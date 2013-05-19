#include <iostream>
#include "Compressor.cpp"

int main()
{
    Compressor *c = new Compressor("boooobooooo");
    c->compress("out.bin");
    return 0;
}
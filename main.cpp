#include <iostream>
#include "Compressor.cpp"

int main()
{
    Compressor *c = new Compressor("boogieman boooo");
    c->encode();
    return 0;
}
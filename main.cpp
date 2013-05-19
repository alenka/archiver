#include <iostream>
#include "Compressor.cpp"

int main()
{
    Compressor *c = new Compressor("wooowwwoo");
    c->encode();
    return 0;
}
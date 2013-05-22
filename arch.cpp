#include "src/Archiver.cpp"

int main(int argc, const char **argv)
{
    if(argc < 3)
    {
        cerr<<"Expected 2 args: input and output filenames\n";
        return -1;
    }
    Archiver arch(argv[1]);
    arch.run(argv[2]);
}
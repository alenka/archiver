#include "src/Compressor.cpp"

void help()
{
    cout<<"\
Example usage:\n\
    huffman [compress | -c] <source_file> <output_file>\n\
    huffman [decompress | -d] <compressed_file> <output_file>\n\
";
}

int main(int argc, char **argv)
{
    if(argc < 4) {
        cout<<"Not enought args!\n";
        help();
        return -1;
    }
    Compressor *c = new Compressor(argv[2]);

    char *act = argv[1];
    if(strstr(act, "-c") || strstr(act, "compress")) {
        c->compress(argv[3]);
    }else if(strstr(act, "-d") || strstr(act, "decompress")) {
        c->decompress(argv[3]);
    }else{
        help();
        return -1;
    }
    delete c;
}
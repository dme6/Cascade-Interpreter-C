#include <stdlib.h>
#include <cascade.h>

int main(int argc, char** argv) {

    if(argc < 2) return EXIT_FAILURE;

    interpret_file(argv[1]);
}
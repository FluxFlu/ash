#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

#include "./input/handle_input_filename.c"
#include "./input/getinput.c"

#include "./parse/token.c"
#include "./parse/tokenize.c"

int main(int argc, char** argv) {
    FILE* fptr = handleInputFilename(argc, argv);
    if (fptr == (FILE*) 1) {
        return 1;
    }
    char* input = getInput(fptr);
    puts(input);
    return 0;
}
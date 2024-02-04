
#define VERSION "1.0.0"



#include "./util/def.c"
#include "./util/string.c"

#include "./repl/shell_state.c"
#include "./repl/raw_mode.c"
#include "./repl/write.c"

#include "./parse/token.c"
#include "./parse/tokenize.c"

#include "./exec/exec.c"

#include "./input/input.h"

// #TODO: Make errors good

int main(int argc, char** argv) {
    FILE* fptr = handleInputFilename(argc, argv);
    if (fptr == (FILE*) 1) {
        return 1;
    }

    if (fptr == (FILE*) 2) {
        print = printInteractive;
        handleInteractive();
    } else {
        print = printNonInteractive;
        handleFile(fptr);
    }

    return 0;
}
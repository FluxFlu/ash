
#define VERSION "0.0.0"



#include "./util/def.c"
#include "./util/string.c"

#include "./parse/token.c"

#include "./repl/shell_state.c"
#include "./repl/raw_mode.c"
#include "./repl/write.c"

#include "./parse/tokenize.c"

#include "./exec/exec.c"

#include "./input/input.h"

 /**
   *  TODO:
   *  Interpret ".ash" files as specifically ash scripts
   *  Make errors good
   *  Make history not suck
   *  Add tab & right suggestion
   *  Add operators (&, &&, |, >, etc)
   *  Add more builtins (eg. disown)
   */

int main(int argc, char** argv) {
    if (argc > 1 && strcmp(argv[1], "--version") == 0) {
        printf("ash, version %s\n", VERSION);
        return 0;
    }
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

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
  * TODO:
  * Interpret ".ash" files as specifically ash scripts
  * Make errors good
  * Add tab & right suggestion
  * Add operators (&, &&, |, >, etc)
  * Add more builtins (eg. disown)
  */

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
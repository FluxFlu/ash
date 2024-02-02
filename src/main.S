    // .rodata
cliError:
    .ascii "Command-line arguments not yet implemented..."
    .byte 0

    .text
    .globl main

#include "./getInput.S"

main:
    cmpl    $1, %edi // Check if there are any command line arguments passed
    jle     .real    // If not, we execute the rest of the program

                     // Otherwise, throw an error:

    leaq    cliError(%rip), %rdi
    call    puts
    movl    $1, %eax
    ret

.real:
    movl    $128, %edi  // Malloc 128
    call    malloc

    movq    %rax, %rbp  // Store the result in %rbp
    
    call    getInput

    // movb    $0, %al
    ret
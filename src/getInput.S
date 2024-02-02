

// TODO: Realloc the memory to be double the length if we ever go above the memory limit
getInput:
    movq %rbp, %rbx
    nextChar:
        movq    $0, %rax        // Read syscall
        movq    $0, %rdi        // Read from stdin
        leaq    -8(%rsp), %rsi  // Read into %rsp (onto the stack)
        movq    $1, %rdx        // Read one character
        syscall

        movq    -8(%rsp), %rax  // Load from the stack into %rax
        movq    %rax, (%rbx)    // Load %rax into the heap memory

        incq    %rbx            // Increment %rbx

        cmpq    $10, %rax       // If %rax isn't 10 (if the input wasn't a newline)
        jne     nextChar        // Then we get another character

    // movq    $1, %rax
    // movq    $1, %rdi
    // movq    %rbp, %rsi
    // subq    %rbp, %rbx
    // movq    %rbx, %rdx
    // syscall
    
    ret

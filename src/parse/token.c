
typedef enum type {
    NULLTYPE,
    
    SEPARATOR,
    IDENTIFIER,
    OPERATOR,
    STRING,
    NUMBER,
} Type;

typedef struct token {
    Type type;
    char* value;
} Token;

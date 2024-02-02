
typedef enum type {
    IDENTIFIER,
    OPERATOR,
    STRING,
    NUMBER,
} Type;

typedef struct token {
    Type type;
    char* value;
} Token;

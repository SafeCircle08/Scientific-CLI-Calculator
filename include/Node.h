#ifndef AST_H
#define AST_H

typedef enum {
    NODE_NUMBER,
    NODE_VARIABLE,

    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_POW,

    NODE_NEG,

    NODE_SIN,
    NODE_COS,
    NODE_TAN,
    NODE_ASIN,
    NODE_ACOS,
    NODE_ATAN,

    NODE_LOG,
    NODE_LOG_BASE,
    NODE_LN,
    NODE_SQRT,
    NODE_ABS,

    NODE_FACTORIAL
} NodeType;


typedef struct Node {
    NodeType type;

    double value;
    char variable;

    struct Node* left;
    struct Node* right;
} Node;

Node* new_node_number(double value);
Node* new_variable(char variable);

Node* new_node_unary(NodeType type, Node* child);
Node* new_node_binary(NodeType type, Node* left, Node* right);

void show_AST(Node* root, int depth);

void free_Node(Node* node);

#endif //AST_H

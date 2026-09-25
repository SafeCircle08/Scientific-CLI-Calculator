#include "Node.h"
#include <stdlib.h>
#include <stdio.h>

Node* new_node_number(double value) {
    Node* ast = malloc(sizeof(Node));
    if (ast != NULL) {
        ast->type = NODE_NUMBER;
        ast->value = value;
        ast->variable = '\0';

        ast->left = NULL;
        ast->right = NULL;
    }
    return ast;
}

Node* new_variable(char variable) {
    Node* ast = malloc(sizeof(Node));
    if (ast != NULL) {
        ast->type = NODE_VARIABLE;
        ast->value = 0;
        ast->variable = variable;

        ast->left = NULL;
        ast->right = NULL;
    }
    return ast;
}

Node* new_node_unary(NodeType type, Node* child) {
    Node *ast = malloc(sizeof(Node));
    if (ast != NULL) {
        ast->type = type;
        ast->value = 0;
        ast->variable = '\0';

        ast->left = child;
        ast->right = NULL;
    }
    return ast;
}

Node* new_node_binary(NodeType type, Node* left, Node* right) {
    Node *ast = malloc(sizeof(Node));
    if (ast != NULL) {
        ast->type = type;
        ast->value = 0;
        ast->variable = '\0';

        ast->left = left;
        ast->right = right;
    }
    return ast;
}

void free_Node(Node* node) {
    if (node == NULL) return;

    free_Node(node->left);
    free_Node(node->right);

    free(node);
}

void show_AST(Node *node, int depth) {
    if (node == NULL) return;

    for (int i = 0; i < depth; i++) printf(" ");

    switch (node->type) {
        case NODE_NUMBER: printf("NUMBER: %g\n", node->value); break;
        case NODE_ADD: printf("ADD\n"); break;
        case NODE_SUB: printf("SUB\n"); break;
        case NODE_MUL: printf("MUL\n"); break;
        case NODE_DIV: printf("DIV\n"); break;
        case NODE_POW: printf("POW\n"); break;
        case NODE_FACTORIAL: printf("FACT\n"); break;
        case NODE_SIN: printf("SIN\n"); break;

        default: printf("ERROR\n"); break;
    }
    show_AST(node->left, depth + 1);
    show_AST(node->right, depth + 1);
}
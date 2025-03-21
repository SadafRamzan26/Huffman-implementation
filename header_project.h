#ifndef HEADER_H
#define HEADER_H

struct node {
    int Roll_Number;
    char name[50]; // Use a char array for name
    double GPA;

    node* lchild;
    node* rchild;
};


void inorder(node* root);
void preorder(node* root);
void postorder(node* root);
void insert(node** root, int size);
void find(int item, node** loc, node** par, node** root);
void Delete(node** root, int data);
void case_a(node* par, node* loc, node** root);
void case_b(node* par, node* loc, node** root);
void case_c(node* par, node* loc, node** root);
void drawTree(node* root, int x, int y, int xOffset, int level);

#endif


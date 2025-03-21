#include <iostream>
#include <cstdio>
#include <graphics.h>
#include "header_project.h"
using namespace std;

void find(int item, node** loc, node** par, node** root) {
    node* ptr, * ptrsave;
    if (*root == NULL) {
        *loc = NULL;
        *par = NULL;
        return;
    }
    if (item == (*root)->Roll_Number) {
        *loc = *root;
        *par = NULL;
        return;
    }
    if (item < (*root)->Roll_Number) {
        ptr = (*root)->lchild;
    } else {
        ptr = (*root)->rchild;
    }
    ptrsave = *root;
    while (ptr != NULL) {
        if (item == ptr->Roll_Number) {
            *loc = ptr;
            *par = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (item < ptr->Roll_Number) {
            ptr = ptr->lchild;
        } else {
            ptr = ptr->rchild;
        }
    }
    *loc = NULL;
    *par = ptrsave;
}

void insert(node** root, int roll) {
    node* par, * loc, * tmp;
    find(roll, &loc, &par, root);
    if (loc != NULL) {
        cout << "Student with this Roll Number Already Exists" << endl;
        return;
    }
    tmp = new node();
    tmp->Roll_Number = roll;

    cout << "Enter Student Name: ";
    cin.ignore(); // Clear input buffer
    cin.getline(tmp->name, 50);

    cout << "Enter GPA: ";
    cin >> tmp->GPA;

    tmp->lchild = NULL;
    tmp->rchild = NULL;

    if (par == NULL) {
        *root = tmp;
    } else {
        if (roll < par->Roll_Number) {
            par->lchild = tmp;
        } else {
            par->rchild = tmp;
        }
    }
}

void inorder(node* root) {
    if (root != NULL) {
        inorder(root->lchild);
        cout << root->Roll_Number << " ";
        inorder(root->rchild);
    }
}

void drawTree(node* root, int x, int y, int xOffset, int level) {
    if (root == NULL) return;

    // Set the circle radius
    int radius = 40;

    // Draw the circle for the current node
    circle(x, y, radius);

    // Prepare the text to be displayed inside the circle
    char rollText[50], nameText[50], gpaText[50];
    sprintf(rollText, "Roll: %d", root->Roll_Number);
    sprintf(nameText, "Name: %s", root->name);
    sprintf(gpaText, "GPA: %.2f", root->GPA);

    // Display the text inside the circle on separate lines
    outtextxy(x - radius + 10, y - radius + 10, rollText);  // Roll number
    outtextxy(x - radius + 10, y - radius + 25, nameText);  // Name
    outtextxy(x - radius + 10, y - radius + 40, gpaText);   // GPA

    // Draw lines and recursively draw left and right children
    if (root->lchild) {
        // Draw line from parent to left child
        line(x, y + radius, x - xOffset, y + 100 - radius);
        drawTree(root->lchild, x - xOffset, y + 100, xOffset / 2, level + 1);
    }

    if (root->rchild) {
        // Draw line from parent to right child
        line(x, y + radius, x + xOffset, y + 100 - radius);
        drawTree(root->rchild, x + xOffset, y + 100, xOffset / 2, level + 1);
    }
}


void Delete(node** root, int num) {
    node* par, * loc;
    if (*root == NULL) {
        cout << "Empty Tree" << endl;
        return;
    }
    find(num, &loc, &par, root);

    if (loc == NULL) {
        cout << "Number not present" << endl;
        return;
    }
    if (loc->lchild == NULL && loc->rchild == NULL) {
        case_a(par, loc, root);
    } else if (loc->lchild != NULL && loc->rchild == NULL) {
        case_b(par, loc, root);
    } else if (loc->lchild == NULL && loc->rchild != NULL) {
        case_b(par, loc, root);
    } else {
        case_c(par, loc, root);
    }
    delete loc;
}

void case_a(node* par, node* loc, node** root) {
    if (par == NULL) {
        *root = NULL;
    } else {
        if (loc == par->lchild) {
            par->lchild = NULL;
        } else {
            par->rchild = NULL;
        }
    }
}

void case_b(node* par, node* loc, node** root) {
    node* child;
    if (loc->lchild != NULL) {
        child = loc->lchild;
    } else {
        child = loc->rchild;
    }
    if (par == NULL) {
        *root = child;
    } else {
        if (loc == par->lchild) {
            par->lchild = child;
        } else {
            par->rchild = child;
        }
    }
}

void case_c(node* par, node* loc, node** root) {
    node* ptr, * ptrsave, * succ, * parsucc;
    ptrsave = loc;
    ptr = loc->rchild;

    while (ptr->lchild != NULL) {
        ptrsave = ptr;
        ptr = ptr->lchild;
    }
    succ = ptr;
    parsucc = ptrsave;

    if (succ->rchild == NULL) {
        case_a(parsucc, succ, root);
    } else {
        case_b(parsucc, succ, root);
    }

    if (par == NULL) {
        *root = succ;
    } else {
        if (loc == par->lchild) {
            par->lchild = succ;
        } else {
            par->rchild = succ;
        }
    }
    succ->lchild = loc->lchild;
    succ->rchild = loc->rchild;
}


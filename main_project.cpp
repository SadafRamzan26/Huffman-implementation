#include <iostream>
#include <graphics.h>
#include "header_project.h"
using namespace std;

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    int choice, num;
    node* root = NULL;

    while (true) {
        cleardevice();
        drawTree(root, getmaxx() / 2, 50, 100, 0);

        cout << "---------------------------------------" << endl;
        cout << "1- Insert" << endl;
        cout << "2- Delete" << endl;
        cout << "3- Inorder Traversal" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
           case 1:
    cout << "Enter Roll Number: ";
    cin >> num; // num represents the Roll Number here
    insert(&root, num);
    break;

            case 2:
                cout << "Enter the number to be deleted: ";
                cin >> num;
                Delete(&root, num);
                break;
            case 3:
                inorder(root);
                break;
        }
    }

    closegraph();
    return 0;
}


#include <stdio.h> 
#include <stdlib.h> 
typedef enum { RED, BLACK } Color; 
typedef struct Node { 
    int data; 
    Color color; 
    struct Node *left, *right, *parent; 
} Node; 
Node *root = NULL; 
Node* createNode(int data) { 
    Node* node = (Node*)malloc(sizeof(Node)); 
    node->data = data; 
    node->color = RED; 
    node->left = node->right = node->parent = NULL; 
    return node; 
} 
void leftRotate(Node **root, Node *x) { 
    Node *y = x->right; 
    x->right = y->left; 
    if (y->left) y->left->parent = x; 
    y->parent = x->parent; 
    if (!x->parent) 
        *root = y; 
    else if (x == x->parent->left) 
        x->parent->left = y; 
    else 
        x->parent->right = y; 
    y->left = x; 
    x->parent = y; 
} 
void rightRotate(Node **root, Node *y) { 
    Node *x = y->left; 
    y->left = x->right; 
    if (x->right) x->right->parent = y; 
    x->parent = y->parent; 
    if (!y->parent) 
        *root = x; 
    else if (y == y->parent->left) 
        y->parent->left = x; 
    else 
        y->parent->right = x; 
    x->right = y; 
    y->parent = x; 
} 
void fixInsertion(Node **root, Node *z) { 
    while (z->parent && z->parent->color == RED) { 
        Node *gp = z->parent->parent; 
        if (z->parent == gp->left) { 
            Node *uncle = gp->right; 
            if (uncle && uncle->color == RED) { 
                z->parent->color = BLACK; 
                uncle->color = BLACK; 
                gp->color = RED; 
                z = gp; 
            } else { 
                if (z == z->parent->right) { 
                    z = z->parent; 
                    leftRotate(root, z); 
                } 
                z->parent->color = BLACK; 
                gp->color = RED; 
                rightRotate(root, gp); 
            } 
        } else { 
            Node *uncle = gp->left; 
            if (uncle && uncle->color == RED) { 
                z->parent->color = BLACK; 
                uncle->color = BLACK; 
                gp->color = RED; 
                z = gp; 
            } else { 
                if (z == z->parent->left) { 
                    z = z->parent; 
                    rightRotate(root, z); 
                } 
                z->parent->color = BLACK; 
                gp->color = RED; 
                leftRotate(root, gp); 
            } 
        } 
    } 
    (*root)->color = BLACK; 
} 
Node* bstInsert(Node* root, Node* node) 
{ 
    if (!root) return node; 
    if (node->data < root->data) { 
        root->left = bstInsert(root->left, node); 
        root->left->parent = root; 
    } else if (node->data > root->data) { 
        root->right = bstInsert(root->right, node); 
        root->right->parent = root; 
    } 
    return root; 
} 
void insert(int data) { 
    Node* node = createNode(data); 
    root = bstInsert(root, node); 
    fixInsertion(&root, node); 
} 
Node* minimum(Node* node) { 
    while (node->left) node = node->left; 
    return node; 
} 
void transplant(Node **root, Node *u, Node *v) { 
    if (!u->parent) 
        *root = v; 
    else if (u == u->parent->left) 
        u->parent->left = v; 
    else 
        u->parent->right = v; 
    if (v) 
        v->parent = u->parent; 
} 
void fixDeletion(Node **root, Node *x) { 
     
                 
while (x != *root && (!x || x->color == BLACK)) { 
        if (x == x->parent->left) { 
            Node *w = x->parent->right; 
            if (w && w->color == RED) { 
                w->color = BLACK; 
                x->parent->color = RED; 
                leftRotate(root, x->parent); 
                w = x->parent->right; 
            } 
            if ((!w->left || w->left->color == BLACK) && 
                (!w->right || w->right->color == BLACK)) { 
                if (w) w->color = RED; 
                x = x->parent; 
            } else { 
                if (!w->right || w->right->color == BLACK) { 
                    if (w->left) w->left->color = BLACK; 
                    if (w) w->color = RED; 
                    rightRotate(root, w); 
                    w = x->parent->right; 
                } 
                if (w) w->color = x->parent->color; 
                x->parent->color = BLACK; 
                if (w->right) w->right->color = BLACK; 
                leftRotate(root, x->parent); 
                x = *root; 
            } 
        } else { 
            Node *w = x->parent->left; 
            if (w && w->color == RED) { 
                w->color = BLACK; 
                x->parent->color = RED; 
                rightRotate(root, x->parent); 
                w = x->parent->left; 
            } 
            if ((!w->right || w->right->color == BLACK) && 
                (!w->left || w->left->color == BLACK)) { 
                if (w) w->color = RED; 
                x = x->parent; 
            } else { 
                if (!w->left || w->left->color == BLACK) { 
                    if (w->right) w->right->color = BLACK; 
                    if (w) w->color = RED; 
                    leftRotate(root, w); 
                    w = x->parent->left; 
                } 
                if (w) w->color = x->parent->color; 
                x->parent->color = BLACK; 
                if (w->left) w->left->color = BLACK; 
                rightRotate(root, x->parent); 
                x = *root; 
 
            } 
        } 
    } 
    if (x) x->color = BLACK;} 
void deleteNode(int data) { 
    Node *z = root, *x, *y; 
    while (z && z->data != data) { 
        if (data < z->data) 
            z = z->left; 
        else 
            z = z->right; 
    } 
    if (!z) { 
        printf("Node not found!\n"); 
        return; 
    } 
    y = z; 
    Color yOriginalColor = y->color; 
    if (!z->left) { 
        x = z->right; 
        transplant(&root, z, z->right); 
    } else if (!z->right) { 
        x = z->left; 
        transplant(&root, z, z->left); 
    } else { 
        y = minimum(z->right); 
        yOriginalColor = y->color; 
        x = y->right; 
        if (y->parent == z) { 
            if (x) x->parent = y; 
        } else { 
            transplant(&root, y, y->right); 
            y->right = z->right; 
            if (y->right) y->right->parent = y; 
        } 
        transplant(&root, z, y); 
        y->left = z->left; 
        if (y->left) y->left->parent = y; 
        y->color = z->color; 
    } 
    free(z); 
    if (yOriginalColor == BLACK) 
        fixDeletion(&root, x); 
} 
void inorder(Node* node) { 
    if (!node) return; 
    inorder(node->left); 
    printf("%d(%s) ", node->data, node->color == RED ? "R" : "B"); 
    inorder(node->right); 
} 
int main() { 
    int choice, value; 
    while (1) { 
        printf("\n--- Red-Black Tree Menu ---\n"); 
        printf("1. Insert\n"); 
        printf("2. Delete\n"); 
        printf("3. Display (Inorder)\n"); 
        printf("4. Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
        switch (choice) { 
            } 
        } 
    } 
    if (x) x->color = BLACK;{
void deleteNode(int data) { 
    Node *z = root, *x, *y; 
    while (z && z->data != data) { 
        if (data < z->data) 
            z = z->left; 
        else 
            z = z->right; 
    } 
    if (!z) { 
        printf("Node not found!\n"); 
        return; 
    } 
    y = z; 
    Color yOriginalColor = y->color; 
    if (!z->left) { 
        x = z->right; 
        transplant(&root, z, z->right); 
    } else if (!z->right) { 
        x = z->left; 
        transplant(&root, z, z->left); 
    } else { 
        y = minimum(z->right); 
        yOriginalColor = y->color; 
        x = y->right; 
        if (y->parent == z) { 
            if (x) x->parent = y; 
        } else { 
            transplant(&root, y, y->right); 
            y->right = z->right; 
            if (y->right) y->right->parent = y; 
        } 
        transplant(&root, z, y); 
        y->left = z->left; 
        if (y->left) y->left->parent = y; 
        y->color = z->color; 
    } 
    free(z); 
    if (yOriginalColor == BLACK) 
        fixDeletion(&root, x); 
} 
void inorder(Node* node) { 
    if (!node) return; 
    inorder(node->left); 
    printf("%d(%s) ", node->data, node->color == RED ? "R" : "B"); 
    inorder(node->right); 
} 
int main() { 
    int choice, value; 
    while (1) { 
        printf("\n--- Red-Black Tree Menu ---\n"); 
        printf("1. Insert\n"); 
        printf("2. Delete\n"); 
        printf("3. Display (Inorder)\n"); 
        printf("4. Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
        switch (choice) { 
            case 1: 
                printf("Enter value to insert: "); 
                scanf("%d", &value); 
                insert(value); 
                break; 
            case 2: 
                printf("Enter value to delete: "); 
                scanf("%d", &value); 
                deleteNode(value); 
                break; 
            case 3: 
                printf("Inorder traversal: "); 
                inorder(root); 
                printf("\n"); 
                break; 
            case 4: 
                exit(0); 
            default: 
                printf("Invalid choice!\n"); 
                 } 
            } 
       return 0;
        }
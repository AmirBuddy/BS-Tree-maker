#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

// Binary search tree structure
struct BSTree {
    string data;
    BSTree *left, *right;
    BSTree(string number) {
        this->data = number;
        this->left = NULL;
        this->right = NULL;
    }
};

struct Trunk {
    Trunk *prev;
    string str;
    Trunk(Trunk *prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

void showTrunks(Trunk *p) {
    if (p == NULL) 
        return;
    showTrunks(p->prev);
    cout << p->str;
}
 
/**
 * The function takes a pointer to a tree node, a pointer to a Trunk object, and a boolean value. It
 * prints the tree in a horizontal fashion
 * 
 * @param root The root of the tree
 * @param prev the previous trunk
 * @param isLeft true if the node is a left child of its parent
 */
void horizontal_printer(BSTree *root, Trunk *prev = NULL, bool isLeft = false) {
    if (root == NULL) 
        return;
    string prev_str = "     ";
    Trunk *trunk = new Trunk(prev, prev_str);
    horizontal_printer(root->right, trunk, true);
    if (!prev) 
        trunk->str = "----";
    else if (isLeft) {
        trunk->str = ".----";
        prev_str = "    |";
    }
    else {
        trunk->str = "\'----";
        prev->str = prev_str;
    }
    showTrunks(trunk);
    cout << " " << root->data << endl;
    if (prev) 
        prev->str = prev_str;
    trunk->str = "    |";
    horizontal_printer(root->left, trunk, false);
}

/**
 * It reads in a line of input, and returns a queue of BSTree nodes
 * 
 * @return A queue of BSTree pointers.
 */
queue<BSTree*> getNodes() {
    queue<BSTree*> res;
    string node;
    while (cin >> node) {
        BSTree *root = new BSTree(node);
        res.push(root);
        if (cin.peek() == '\n') break;
    }
    cin.ignore(1);
    return res;
}

/**
 * The function takes in the inorder and postorder/preorder traversals of a binary tree, and returns the root of
 * the constructed tree 
 * This is the core part and the main algorithm used to construct the tree
 * by giving it the inorder traversal and either postorder or preorder traversal of the tree 
 * 
 * @param in_order the in-order traversal of the tree
 * @param post_pre the post-order/pre-order traversal of the tree
 * @param root the root of the tree
 * 
 * @return The root of the constructed tree.
 */
BSTree* build(queue<BSTree*> &in_order, queue<BSTree*> &post_pre, BSTree *&root) {
    if (in_order.size() == 0)
        return NULL;
    if (in_order.size() == 1) 
        return root;
    if (in_order.size() == 2) {
        if (in_order.back()->data == root->data)
            root->left = in_order.front();
        else
            root->right = in_order.back();
        return root;
    } 
    if (in_order.size() == 3) {
        root->left = in_order.front();
        root->right = in_order.back();
        return root;
    }
    int sign;
    if (post_pre.front()->data == root->data) {
        post_pre.pop();
        sign = 2;
    }
    else sign = 1;

    queue<BSTree*> left_in;
    while (in_order.front()->data != root->data) {
        left_in.push(in_order.front());
        in_order.pop();
    }
    in_order.pop();

    queue<BSTree*> right_in;
    while (!in_order.empty()) {
        right_in.push(in_order.front());
        in_order.pop();
    }

    queue<BSTree*> left_p;
    for (int i = 0; i < left_in.size(); i++) {
        left_p.push(post_pre.front());
        post_pre.pop();
    }
    
    queue<BSTree*> right_p;
    for (int i = 0; i < right_in.size(); i++) {
        right_p.push(post_pre.front());
        post_pre.pop();
    }

    if (sign == 1) {
        root->left = build(left_in, left_p, left_p.back());
        root->right = build(right_in, right_p, right_p.back());
    }
    else {
        root->left = build(left_in, left_p, left_p.front());
        root->right = build(right_in, right_p, right_p.front());
    }
    return root;
}

BSTree* buildTree(queue<BSTree*> &in, queue<BSTree*> &post_pre, int num) {
    if (num == 1)
        return build(in, post_pre, post_pre.back());
    else if (num == 2)
        return build(in, post_pre, post_pre.front());
    else cout << "something went wrong!" << endl;
    return NULL;
}

int height(BSTree *root) {
    if (root == NULL)
        return 0;
    else {
        int left_height = height(root->left);
        int right_height = height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

/**
 * It takes a tree, a level, and a queue, then adds the data of the nodes at that level to the queue
 * 
 * @param root the root of the tree
 * @param level the level of the tree you're currently on
 * @param q queue of strings
 * 
 * @return the width of the tree.
 */
void width(BSTree *root, int level, queue<string> &q){
    if (root == NULL) {
        if (level>1){
            width(NULL, level - 1, q);
            width(NULL, level - 1, q);
        }
        else q.push("null");
        return;
    }
    if (level == 1)
       q.push(root->data);
    else if (level > 1) {
        width(root->left, level - 1, q);
        width(root->right, level - 1, q);
    }
}

/**
 * The function takes a binary search tree and prints it out in a vertical fashion
 * 
 * @param root the root of the tree
 * @param parse the string that is printed between each node
 */
void vertical_printer(BSTree *root, string parse = "  ") {
    int nodes = pow(2, height(root)) - 1;
    string *space = new string[nodes];
    for (int i = 0; i < nodes; i++) 
        space[i] = "#";
    for (int l = 1; l <= height(root); l++) {
        queue<string> q;
        width(root, l, q);
        int jumps = pow(2, height(root) - l);
        int helper = jumps;
        for (int i = 1; helper <= nodes; i++) {
            if (i != helper) 
                cout << parse;
            else if (i == helper && space[i-1] != "#") {
                cout << parse;
                helper += jumps;
            }
            else if (i == helper && space[i-1] == "#" && q.front() == "null") {
                space[i-1] = q.front();
                q.pop();
                helper += jumps;
                cout << parse;
            }
            else {
                space[i-1] = q.front();
                q.pop();
                helper += jumps;
                cout << space[i-1];
            }
        }
        for (int i = 1; i <= jumps/2; i++)
            cout << endl;
    }
    delete[] space;
}

int main() {
    cout << "Enter in-order traversal of the tree with space in between(x x x ...)" << endl;
    queue<BSTree*> in = getNodes();
    cout << "Which one do you want to enter now: (1 or 2)" << endl 
         << "1. post" << endl 
         << "2. pre" << endl
         << "Your choice: ";
    int num;
    cin >> num; cin.ignore(1);
    cout << "Enter the traversal" << endl;
    queue<BSTree*> post_pre = getNodes();
    BSTree *root = buildTree(in, post_pre, num);
    cout << endl;

    horizontal_printer(root);
    cout << endl;
    for (int i = 0; i < 50; i++) cout << "-"; 
    cout << endl; 

    vertical_printer(root);

    cout << "\n\nPress enter to exit..."; 
    cin.get();
    return 0;
}

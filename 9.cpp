#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    string keyword, meaning;
    Node* left;
    Node* right;
    int height;

    Node(string k, string m) : keyword(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* root, string key, string meaning) {
    if (!root) return new Node(key, meaning);

    if (key < root->keyword)
        root->left = insert(root->left, key, meaning);
    else if (key > root->keyword)
        root->right = insert(root->right, key, meaning);
    else {
        cout << "Keyword already exists.\n";
        return root;
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalance(root);

    // Balance the tree
    if (balance > 1 && key < root->left->keyword) return rightRotate(root);
    if (balance < -1 && key > root->right->keyword) return leftRotate(root);
    if (balance > 1 && key > root->left->keyword) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->keyword) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* minValueNode(Node* node) {
    while (node->left) node = node->left;
    return node;
}

Node* deleteNode(Node* root, string key) {
    if (!root) return root;

    if (key < root->keyword)
        root->left = deleteNode(root->left, key);
    else if (key > root->keyword)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void updateMeaning(Node* root, string key) {
    while (root) {
        if (key < root->keyword)
            root = root->left;
        else if (key > root->keyword)
            root = root->right;
        else {
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, root->meaning);
            cout << "Meaning updated.\n";
            return;
        }
    }
    cout << "Keyword not found.\n";
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        inOrder(root->right);
    }
}

void reverseInOrder(Node* root) {
    if (root) {
        reverseInOrder(root->right);
        cout << root->keyword << " : " << root->meaning << endl;
        reverseInOrder(root->left);
    }
}

int maxComparisons(Node* root) {
    return getHeight(root);
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    do {
        cout << "\n1. Add keyword\n2. Delete keyword\n3. Update meaning\n4. Display Ascending\n";
        cout << "5. Display Descending\n6. Max Comparisons (Tree Height)\n7. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                root = insert(root, key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                updateMeaning(root, key);
                break;
            case 4:
                cout << "\nDictionary in Ascending Order:\n";
                inOrder(root);
                break;
            case 5:
                cout << "\nDictionary in Descending Order:\n";
                reverseInOrder(root);
                break;
            case 6:
                cout << "Maximum comparisons to find a keyword: " << maxComparisons(root) << endl;
                break;
            case 7:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
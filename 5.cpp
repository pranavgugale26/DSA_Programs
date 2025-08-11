#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

Node* constructTree(const string& prefix) {
    stack<Node*> st;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];
        Node* node = new Node(ch);

        if (isOperator(ch)) {
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
        }
        st.push(node);
    }
    return st.top();
}

void postOrderNonRecursive(Node* root) {
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);

        if (curr->left)
            s1.push(curr->left);
        if (curr->right)
            s1.push(curr->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data;
        s2.pop();
    }
    cout << endl;
}

void deleteTree(Node* root) {
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);

        if (curr->left)
            s1.push(curr->left);
        if (curr->right)
            s1.push(curr->right);
    }

    while (!s2.empty()) {
        delete s2.top();
        s2.pop();
    }
}

int main() {
    string prefix;
    cout << "Enter a prefix expression: ";
    cin >> prefix;

    Node* root = constructTree(prefix);

    cout << "Post-order traversal (non-recursive): ";
    postOrderNonRecursive(root);

    deleteTree(root);
    cout << "Tree deleted successfully." << endl;

    return 0;
}
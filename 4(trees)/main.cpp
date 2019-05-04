#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//3, 12, 15, 18, 21, 24

struct Tree_node {
    int data;
    vector<Tree_node*> child;
    Tree_node* parent;
};

struct BTree_node {
    int data;
    BTree_node* left;
    BTree_node* right;
    BTree_node* parent;
};

Tree_node* new_node (int new_data) {
    Tree_node* curr = new Tree_node;
    curr->data = new_data;
    curr->parent = nullptr;
    return curr;
}

BTree_node* new_bin_node (int new_data) {
    BTree_node* curr = new BTree_node;
    curr->data = new_data;
    curr->parent = nullptr;
    curr->left = nullptr;
    curr->right = nullptr;
    return curr;
}

void insert (int insert_value, int input_index, Tree_node* root) {      //task 3
    Tree_node* input_node = new_node(insert_value);
    queue<pair<Tree_node*, int>> q;
    int curr_index = 0;
    q.push(make_pair(root, curr_index));
    curr_index++;
    while (!q.empty()) {
        pair<Tree_node*,int> curr_node = q.front();
        q.pop();
        if (curr_node.second == input_index) {
            input_node->parent = curr_node.first;
            curr_node.first->child.push_back(input_node);
        }
        for (int i = 0; i < ((curr_node.first)->child).size(); i++) {
            q.push(make_pair(curr_node.first->child[i], curr_index));
            curr_index++;
        }
    }
}

void binary_insert (int insert_value, BTree_node* root) {       //task 18
    BTree_node* input_node = new_bin_node(insert_value);
    if (insert_value < root->data) {
        if (root->left == nullptr) {
            root->left = input_node;
            input_node->parent = root;
        }
        binary_insert(insert_value, root->left);
    }
    if (insert_value > root->data) {
        if (root->right == nullptr) {
            root->right = input_node;
            input_node->parent = root;
        }
        binary_insert(insert_value, root->right);
    }
}

void interactive_output (Tree_node* root) {     //task 12
    Tree_node* curr_node = root;
    int next;
    if (curr_node->parent != nullptr) {
        cout<<"Parent: "<<(curr_node->parent)->data<<"[0]"<<endl;
    }
    cout<<"Current node: "<<curr_node->data<<endl;
    if (!curr_node->child.empty()) {
        cout<<"Childs: ";
        for (int i = 0; i < curr_node->child.size(); i++) {cout<<curr_node->child[i]->data<<'['<<i+1<<"] ";}
        cout<<endl;
    }
    cout<<"Enter index of node to show"<<endl;
    cout<<"(for exit enter -1)"<<endl;
    cin>>next;
    if (next == -1) {return;}
    if (next == 0) {interactive_output(curr_node->parent);}
    else {interactive_output(curr_node->child[next-1]);}
}

void binary_interactive_output (BTree_node* root) {
    BTree_node* curr_node = root;
    int next;
    if (curr_node->parent != nullptr) {
        cout<<"Parent: "<<(curr_node->parent)->data<<"[0]"<<endl;
    }
    cout<<"Current node: "<<curr_node->data<<endl;
    if (curr_node->left != nullptr) {
        cout<<"Left: "<<curr_node->left->data<<"[1]"<<endl;
    }
    if (curr_node->right != nullptr) {
        cout<<"Right: "<<curr_node->right->data<<"[2]"<<endl;
    }
    cout<<"Enter index of node to show"<<endl;
    cout<<"(for exit enter -1)"<<endl;
    cin>>next;
    if (next == -1) {return;}
    if (next == 0) {binary_interactive_output(curr_node->parent);}
    if (next == 1) {binary_interactive_output(curr_node->left);}
    if (next == 2) {binary_interactive_output(curr_node->right);}

}

void delete_by_value (int deleting_value, Tree_node* root) {        //task 15
    for (int i = 0; i < root->child.size(); i++) {
        delete_by_value(deleting_value, root->child[i]);
    }
    if (root->data == deleting_value) {
        for (int i = 0; i < root->child.size(); i++) {
            (root->parent)->child.push_back(root->child[i]);
        }
        for (int i = 0; i < (root->parent)->child.size(); i++) {
            if ((root->parent)->child[i] == root) {(root->parent)->child.erase((root->parent)->child.begin()+i);}
        }
        delete root;
    }
}

void pre_binary_output (BTree_node* root, int level) {      //task 21
    if (root != nullptr) {
        cout << '|';
        for (int i = 0; i < level; i++) {cout << "     " << '|';}
        cout << root->data << endl;
        if (root->left != nullptr) { pre_binary_output(root->left, level++); }
        if (root->right != nullptr) { pre_binary_output(root->right, level++); }
    }
}

void boolean_expressions (){

}

int main() {
    return 0;
}
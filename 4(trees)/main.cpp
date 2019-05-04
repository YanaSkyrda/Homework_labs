#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "tm_functions.h"

using namespace std;

//3, 12, 15, 18, 21, 26

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

struct Catalog_node {
    string name;
    float size;
    tm last_update;
    Catalog_node* parent;
    vector<Catalog_node*> child;
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

Catalog_node* new_catalog_node (string name_data, float size_data, tm upd_data) {
    Catalog_node* curr = new Catalog_node;
    curr->name = name_data;
    curr->size = size_data;
    curr->last_update = upd_data;
    curr->parent = nullptr;
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

float catalog_size (Catalog_node* root, float size){        //task 26
    if (root->child.empty()) {size += root->size;}
    for (int i = 0; i < root->child.size(); i++) {
        catalog_size(root->child[i], size);
    }
    return size;
}

int files_amount (Catalog_node* root, int curr_amount) {
    if (root->child.empty()) {curr_amount++;}
    for (int i = 0; i < root->child.size(); i++) {
        files_amount(root->child[i], curr_amount);
    }
    return curr_amount;
}

int subdirect_amount (Catalog_node* root, int curr_amount) {
    if (!root->child.empty()) {curr_amount++;}
    for (int i = 0; i < root->child.size(); i++) {
        subdirect_amount(root->child[i], curr_amount);
    }
    return curr_amount;
}

void all_updates (Catalog_node* root, vector<tm>& vec_upd) {
    vec_upd.push_back(root->last_update);
    for (int i = 0; i < root->child.size(); i++) {
        all_updates(root->child[i], vec_upd);
    }
}

tm min_last_upd (Catalog_node* root) {
    vector<tm> updates;
    tm min_date;
    all_updates(root, updates);
    min_date = updates[0];
    for (auto item : updates) {
        if (item < min_date) {
            min_date = item;
        }
    }
    return min_date;
}

tm max_last_upd (Catalog_node* root) {
    vector<tm> updates;
    tm max_date;
    all_updates(root, updates);
    max_date = updates[0];
    for (auto item : updates) {
        if (item > max_date) {
            max_date = item;
        }
    }
    return max_date;
}

void copy_catalog (Catalog_node* root, Catalog_node* new_root) {
    Catalog_node* curr_new;
    curr_new = new_catalog_node(root->name, root->size, root->last_update);
    curr_new->parent = new_root;
    new_root->child.push_back(curr_new);
    for (int i = 0; i < root->child.size(); i++) {
        copy_catalog(root->child[i], curr_new);
    }
}

void leave_by_name (string leave_name, Catalog_node* root) {
    for (int i = 0; i < root->child.size(); i++) {
        leave_by_name(leave_name, root->child[i]);
    }
    if (root->name != leave_name) {
        for (int i = 0; i < root->child.size(); i++) {
            (root->parent)->child.push_back(root->child[i]);
        }
        for (int i = 0; i < (root->parent)->child.size(); i++) {
            if ((root->parent)->child[i] == root) {(root->parent)->child.erase((root->parent)->child.begin()+i);}
        }
        delete root;
    }
}

void leave_by_size (float min_size, float max_size, Catalog_node* root) {
    for (int i = 0; i < root->child.size(); i++) {
        leave_by_size(min_size, max_size, root->child[i]);
    }
    if ((min_size!= -1&&root->size<min_size)||(max_size!= -1&&root->size>max_size)) {
        for (int i = 0; i < root->child.size(); i++) {
            (root->parent)->child.push_back(root->child[i]);
        }
        for (int i = 0; i < (root->parent)->child.size(); i++) {
            if ((root->parent)->child[i] == root) {(root->parent)->child.erase((root->parent)->child.begin()+i);}
        }
        delete root;
    }
}

void leave_by_update (tm min_date, tm max_date, Catalog_node* root) {
    for (int i = 0; i < root->child.size(); i++) {
        leave_by_update(min_date, max_date, root->child[i]);
    }
    if (root->last_update<min_date||root->last_update>max_date) {
        for (int i = 0; i < root->child.size(); i++) {
            (root->parent)->child.push_back(root->child[i]);
        }
        for (int i = 0; i < (root->parent)->child.size(); i++) {
            if ((root->parent)->child[i] == root) {(root->parent)->child.erase((root->parent)->child.begin()+i);}
        }
        delete root;
    }
}

void name_filter (Catalog_node* root, string name_filter, Catalog_node* new_catalog) {
    copy_catalog(root, new_catalog);
    leave_by_name(name_filter, new_catalog);
}

void size_filter (Catalog_node* root, float min_size, float max_size, Catalog_node* new_catalog) {
    copy_catalog(root, new_catalog);
    leave_by_size(min_size,max_size, new_catalog);
}

void update_filter (Catalog_node* root, tm min_date, tm max_date, Catalog_node* new_catalog) {
    copy_catalog(root, new_catalog);
    leave_by_update(min_date, max_date, new_catalog);
}

Catalog_node* filter_catalog (Catalog_node* root, string rule) {
    Catalog_node* new_catalog = nullptr;
    if (rule[0] == 'n') {
        string name_filter;
        for (int i = 5; i < rule.size(); i++) { name_filter += rule[i]; }

    }
    if (rule[0] == 's') {

    }
    if (rule[0] == 'u') {

    }
}

int main() {
    return 0;
}
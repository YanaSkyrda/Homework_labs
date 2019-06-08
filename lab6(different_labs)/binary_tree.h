#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include"tm_functions.h"

using namespace std;

struct btree_node {
    tm data;
    btree_node* left;
    btree_node* right;
};

btree_node* create_empty_btree() {
    btree_node* new_tree;
    new_tree = new btree_node;
    new_tree->left = nullptr;
    new_tree->right = nullptr;
    new_tree->data.tm_year = -1;
    return new_tree;
}

void insert (btree_node** root, tm insert_data) {
    btree_node* input_node = new btree_node;
    input_node->data = insert_data;
    input_node->left = nullptr;
    input_node->right = nullptr;

    if (*root == nullptr) {
        *root = input_node;
        return;
    }

    if (input_node->data < (*root)->data) {
        if ((*root)->left == nullptr) {
            (*root)->left = input_node;
            return;
        }
        insert(&(*root)->left, insert_data);
    } else if (input_node->data > (*root)->data)   {
        if ((*root)->right == nullptr) {
            (*root)->right = input_node;
            return;
        }
        insert(&(*root)->right, insert_data);
    }
}

void delete_by_value (tm deleting_value, btree_node** root, btree_node* rec_root = nullptr) {
    if (!rec_root) {rec_root = *root;}
    if (rec_root->left) { delete_by_value(deleting_value, root, rec_root->left); }
    if (rec_root->right) { delete_by_value(deleting_value, root, rec_root->right); }

    if (rec_root->left || rec_root->right || (rec_root == *root && (*root)->data == deleting_value)) {
        queue<btree_node*> q;

        if (rec_root->left && rec_root->left->data == deleting_value) {
            q.push(rec_root->left);
            rec_root->left = nullptr;
        }
        else if (rec_root->right && rec_root->right->data == deleting_value) {
            q.push(rec_root->right);
            rec_root->right = nullptr;
        } else if (rec_root == *root && (*root)->data == deleting_value) {
            q.push(rec_root);
            (*root) = nullptr;
        } else {return;}

        vector<tm> childs_data;
        while (!q.empty()) {
            btree_node* curr_node = q.front();
            q.pop();
            if(!(curr_node->data == deleting_value)) {childs_data.push_back(curr_node->data);}
            if (curr_node->left) { q.push(curr_node->left); }
            if (curr_node->right) { q.push(curr_node->right); }
            delete curr_node;
        }


        for (int i = 0; i < childs_data.size(); i++) {
            insert(root,childs_data[i]);
        }
    }
}

void binary_tree_output(btree_node *root, bool is_top = true) {
    if (!root) {
        if (is_top) {cout<<"Empty tree"<<endl;}
        return;
    }
    cout<<root->data;
    if (root->left || root->right) { cout<<"("; }
    binary_tree_output(root->left, false);
    if (root->left && root->right) { cout<<","; }
    binary_tree_output(root->right, false);
    if (root->left || root->right) { cout << ")"; }
    if (is_top) {cout<<endl;}
}

btree_node* find_by_date_btree(btree_node* root, tm key) {
    bool found = false;
    while (root && !found) {
        if (key > root->data) {
            root = root->right;
        } else if (key < root->data) {
            root = root->left;
        } else if (root->data == key) {
            found = true;
        }
    }
    if (found) {return root;}
    else {return nullptr;}
}

void find_by_interval_btree(btree_node* root, tm left, tm right, vector<btree_node*>* result) {
    btree_node* curr = root;
    while (curr) {
        if (curr->data > left && curr->data < right) {
            (*result).push_back(root);
            if (curr->left) {find_by_interval_btree(curr->left, left, right, result);}
            if (curr->right) {find_by_interval_btree(curr->right, left, right, result);}
            break;
        } else if (left > curr->data) {
            curr = curr->right;
        } else if (right < curr->data) {
            curr = curr->left;
        }
    }
}

btree_node* create_random_btree (int element_amount) {
    btree_node *first;
    if (element_amount<1) {return nullptr;}
    first = create_empty_btree();
    first->data = random_time();

    for (int i = 1; i < element_amount; i++) {
        insert(&first, random_time());
    }
    return first;
}

void output_sorted_btree(btree_node* root, bool print = true) {
    vector<tm> all_dates;

    queue<btree_node*> q;
    q.push(root);
    while (!q.empty()) {
        btree_node* curr_node = q.front();
        q.pop();
        all_dates.push_back(curr_node->data);
        if (curr_node->left) { q.push(curr_node->left); }
        if (curr_node->right) { q.push(curr_node->right); }
    }

    sort (all_dates.begin(), all_dates.end(), [](tm left, tm right){return left < right;});

    if (print) {
        for (int i = 0; i < all_dates.size(); i++) {
            cout<<all_dates[i]<<"      ";
        }
        cout<<endl;
    }
}

void do_some_function_btree(btree_node* first, tm (*f)(tm)) {
    if(!first) {return;}

    queue<btree_node*> q;
    q.push(first);
    while (!q.empty()) {
        btree_node* curr_node = q.front();
        q.pop();
        curr_node->data = f(curr_node->data);
        if (curr_node->left) { q.push(curr_node->left); }
        if (curr_node->right) { q.push(curr_node->right); }
    }
}


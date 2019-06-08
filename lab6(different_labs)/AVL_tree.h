#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "tm_functions.h"

using namespace std;

struct avl_node {
    tm data;
    avl_node* left;
    avl_node* right;
};

int find_height (avl_node* root) {
    int high = 1;

    if (!root) {return 0;}
    if (!root->left&&!root->right) { return 1; }

    int max = find_height(root->left);
    if (find_height(root->right) > max) { max = find_height(root->right); }

    high += max;
    return high;
}

avl_node* create_empty_avl() {
    avl_node* new_tree;
    new_tree = new avl_node;
    new_tree->left = nullptr;
    new_tree->right = nullptr;
    new_tree->data.tm_year = -1;
    return new_tree;
}

avl_node* right_rotate(avl_node* right) {
    avl_node* left = right->left;
    avl_node* subtree = left->right;

    left->right = right;
    right->left = subtree;

    return left;
}

avl_node* left_rotate(avl_node* left) {
    avl_node* right = left->right;
    avl_node* subtree = right->left;

    right->left = left;
    left->right = subtree;

    return right;
}

int balance_difference (avl_node* curr_node) {
    if (curr_node == nullptr) { return 0; }
    return (find_height(curr_node->left) - find_height(curr_node->right));
}

avl_node* insert_avl(avl_node* root, tm insert_data, bool need_balance = true) {
    avl_node* input_node = new avl_node;
    input_node->data = insert_data;
    input_node->left = nullptr;
    input_node->right = nullptr;

    if (root == nullptr) {
        root = input_node;
        return root;
    }

    if (input_node->data < (root)->data) {
        if ((root)->left == nullptr) {
            (root)->left = input_node;
        } else { insert_avl((root)->left, insert_data, false);}
    } else if (input_node->data > (root)->data)   {
        if ((root)->right == nullptr) {
            (root)->right = input_node;
        } else { insert_avl((root)->right, insert_data, false);}
    } else {return root;}

    if (need_balance) {
        int balance = balance_difference(root);

        // Left Left Case
        if (balance > 1 && insert_data < root->left->data) { return right_rotate(root); }
        // Right Right Case
        if (balance < -1 && insert_data > root->right->data) { return left_rotate(root); }
        // Left Right Case
        if (balance > 1 && insert_data > root->left->data) {
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }
        // Right Left Case
        if (balance < -1 && insert_data < root->right->data) {
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }

        return root;
    }
}

void delete_by_value_avl (tm deleting_value, avl_node** root, avl_node* rec_root = nullptr) {
    if (!rec_root) {rec_root = *root;}
    if (rec_root->left) { delete_by_value_avl(deleting_value, root, rec_root->left); }
    if (rec_root->right) { delete_by_value_avl(deleting_value, root, rec_root->right); }

    if (rec_root->left || rec_root->right || (rec_root == *root && (*root)->data == deleting_value)) {
        queue<avl_node*> q;

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
            avl_node* curr_node = q.front();
            q.pop();
            if(!(curr_node->data == deleting_value)) {childs_data.push_back(curr_node->data);}
            if (curr_node->left) { q.push(curr_node->left); }
            if (curr_node->right) { q.push(curr_node->right); }
            delete curr_node;
        }


        for (int i = 0; i < childs_data.size(); i++) {
            (*root) = insert_avl(*root,childs_data[i]);
        }
    }
}

void avl_tree_output(avl_node *root, bool is_top = true) {
    if (!root) {
        if (is_top) {cout<<"Empty tree"<<endl;}
        return;
    }
    cout<<root->data;
    if (root->left || root->right) { cout<<"("; }
    avl_tree_output(root->left, false);
    if (root->left && root->right) { cout<<","; }
    avl_tree_output(root->right, false);
    if (root->left || root->right) { cout << ")"; }
    if (is_top) {cout<<endl;}
}

avl_node* find_by_date_avl(avl_node* root, tm key) {
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

void find_by_interval_avl(avl_node* root, tm left, tm right, vector<avl_node*>* result) {
    avl_node* curr = root;
    while (curr) {
        if (curr->data > left && curr->data < right) {
            (*result).push_back(curr);
            if (curr->left) {find_by_interval_avl(curr->left, left, right, result);}
            if (curr->right) {find_by_interval_avl(curr->right, left, right, result);}
            break;
        } else if (left > curr->data) {
            curr = curr->right;
        } else if (right < curr->data) {
            curr = curr->left;
        }
    }
}

avl_node* create_random_avl_tree (int element_amount) {
    avl_node *first;
    if (element_amount<1) {return nullptr;}
    first = create_empty_avl();
    first->data = random_time();

    for (int i = 1; i < element_amount; i++) {
        first = insert_avl(first, random_time());
    }
    return first;
}

void output_sorted_avl(avl_node* root, bool print = true) {
    vector<tm> all_dates;

    queue<avl_node*> q;
    q.push(root);
    while (!q.empty()) {
        avl_node* curr_node = q.front();
        q.pop();
        all_dates.push_back(curr_node->data);
        if (curr_node->left) { q.push(curr_node->left); }
        if (curr_node->right) { q.push(curr_node->right); }
    }

    sort (all_dates.begin(), all_dates.end(), [](tm left, tm right){return left < right;});
    if (print) {
        for (int i = 0; i < all_dates.size(); i++) {
            cout << all_dates[i] << "      ";
        }
        cout << endl;
    }
}

void do_some_function_avl(avl_node* first, tm (*f)(tm)) {
    if(!first) {return;}

    queue<avl_node*> q;
    q.push(first);
    while (!q.empty()) {
        avl_node* curr_node = q.front();
        q.pop();
        curr_node->data = f(curr_node->data);
        if (curr_node->left) { q.push(curr_node->left); }
        if (curr_node->right) { q.push(curr_node->right); }
    }
}


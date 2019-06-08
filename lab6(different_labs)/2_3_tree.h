#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include"tm_functions.h"

struct tt_tree {
    vector<tm> options;
    tt_tree* left;
    tt_tree* middle;
    tt_tree* right;
    tt_tree* parent;
};

tt_tree* create_empty_tt() {
    tt_tree* new_tree = new tt_tree;
    new_tree->left = nullptr;
    new_tree->middle = nullptr;
    new_tree->right = nullptr;
    new_tree->parent = nullptr;
    return new_tree;
}

void insert_tt (tt_tree** root, tm insert_data, tt_tree* main_root = nullptr) {

    if (!main_root) { main_root = *root;}
    if (*root == nullptr) {
        *root = create_empty_tt();
        (*root)->options.push_back(insert_data);
        return;
    }

    if ((*root)->options.empty()) {
        (*root)->options.push_back(insert_data);
        return;
    }

    if ((*root)->left == nullptr && (*root)->middle == nullptr && (*root)->right == nullptr && *root == main_root){
            if ((*root)->options.size() == 1) {
                (*root)->options.push_back(insert_data);
                sort( (*root)->options.begin(),  (*root)->options.end(),[](tm left, tm right){return left < right;});
                return;
            } else {
                if (insert_data < (*root)->options[0]) {
                    (*root)->left = create_empty_tt();
                    (*root)->left->options.push_back(insert_data);
                    (*root)->left->parent = (*root);
                    (*root)->middle = create_empty_tt();
                    (*root)->middle->options.push_back((*root)->options[1]);
                    (*root)->middle->parent = (*root);
                    (*root)->options.erase((*root)->options.begin()+1);
                    return;
                } else if (insert_data > (*root)->options[0] && insert_data < (*root)->options[1]) {
                    (*root)->left = create_empty_tt();
                    (*root)->left->options.push_back((*root)->options[0]);
                    (*root)->left->parent = (*root);
                    (*root)->middle = create_empty_tt();
                    (*root)->middle->options.push_back((*root)->options[1]);
                    (*root)->middle->parent = (*root);
                    (*root)->options.clear();
                    (*root)->options.push_back(insert_data);
                    return;
                } else {
                    (*root)->middle = create_empty_tt();
                    (*root)->middle->options.push_back(insert_data);
                    (*root)->middle->parent = (*root);
                    (*root)->left = create_empty_tt();
                    (*root)->left->options.push_back((*root)->options[0]);
                    (*root)->left->parent = (*root);
                    (*root)->options.erase((*root)->options.begin());
                    return;
                }
            }
    }

    if (insert_data < (*root)->options[0]) {
        if ((*root)->left) {
            insert_tt(&(*root)->left, insert_data, main_root);
            return;
        }
    } else if ((*root)->options.size() == 2) {
        if (insert_data > (*root)->options[0] && insert_data < (*root)->options[1]) {
            if ((*root)->middle) {
                insert_tt(&(*root)->middle, insert_data, main_root);
                return;
            }
        } else if (insert_data > (*root)->options[1]) {
            if ((*root)->right) {
                insert_tt(&(*root)->right, insert_data, main_root);
                return;
            }
        }
    } else if (insert_data > (*root)->options[0]) {
        if ((*root)->middle) {
            insert_tt(&(*root)->middle, insert_data, main_root);
            return;
        }
    }
    if ((*root)->options[0] == insert_data || (*root)->options[1] == insert_data) { return; }

    if ((*root)->left == nullptr && (*root)->middle == nullptr && (*root)->right == nullptr) {

        if ((*root)->options.size() == 1) {
            (*root)->options.push_back(insert_data);
            sort( (*root)->options.begin(),  (*root)->options.end(),[](tm left, tm right){return left < right;});
            return;
        } else if ((*root)->parent->options.size() == 1) {
            vector<tm> temp_node =  (*root)->options;
            temp_node.push_back(insert_data);
            sort(temp_node.begin(), temp_node.end(),[](tm left, tm right){return left < right;});
            (*root)->parent->options.push_back(temp_node[1]);
            sort( (*root)->options.begin(),  (*root)->options.end(),[](tm left, tm right){return left < right;});

            if (*root == (*root)->parent->left) {
                (*root)->parent->left->options.clear();
                (*root)->parent->left->options.push_back(temp_node[0]);

                (*root)->parent->right = create_empty_tt();
                ((*root)->parent->right)->parent = (*root)->parent;
                (*root)->parent->right->options = (*root)->parent->middle->options;

                (*root)->parent->middle->options.clear();
                (*root)->parent->middle->options.push_back(temp_node[2]);
            } else if (*root == (*root)->parent->middle) {
                (*root)->parent->right = create_empty_tt();
                ((*root)->parent->right)->parent = (*root)->parent;
                (*root)->parent->right->options.push_back(temp_node[2]);

                (*root)->parent->middle->options.clear();
                (*root)->parent->middle->options.push_back(temp_node[0]);
            }
            return;
        } else {
            pair<vector<tm>,vector<tm>> for_input;
            int side = 0;
            if (*root == (*root)->parent->left) {
                for_input = make_pair((*root)->parent->middle->options,(*root)->parent->right->options);
                side = 0;
            } else if (*root == (*root)->parent->middle) {
                for_input = make_pair((*root)->parent->left->options,(*root)->parent->right->options);
                side = 1;
            } else if (*root == (*root)->parent->right) {
                for_input = make_pair((*root)->parent->left->options,(*root)->parent->middle->options);
                side = 2;
            }


                vector<tm> temp_node = (*root)->options;
                temp_node.push_back(insert_data);
                sort(temp_node.begin(), temp_node.end(),[](tm left, tm right){return left < right;});

                vector<tm> temp_node_parent = (*root)->parent->options;
                temp_node_parent.push_back(temp_node[1]);
                sort(temp_node_parent.begin(), temp_node_parent.end(),[](tm left, tm right){return left < right;});
                tt_tree* parent_node = (*root)->parent;

                parent_node->options.clear();
                parent_node->options.push_back(temp_node_parent[1]);

                parent_node->left->options.clear();
                parent_node->left->options.push_back(temp_node_parent[0]);

                parent_node->middle->options.clear();
                parent_node->middle->options.push_back(temp_node_parent[2]);

            parent_node->right = nullptr;

            parent_node->left->left = create_empty_tt();
            ((parent_node->left)->left)->parent = parent_node->left;

            parent_node->left->middle = create_empty_tt();
            ((parent_node->left)->middle)->parent = parent_node->left;

            parent_node->middle->left = create_empty_tt();
            ((parent_node->middle)->left)->parent = parent_node->middle;

            parent_node->middle->middle = create_empty_tt();
            ((parent_node->middle)->middle)->parent = parent_node->middle;
            if (side == 0) {
                (parent_node->left)->left->options.push_back(temp_node[0]);
                (parent_node->left)->middle->options.push_back(temp_node[2]);

                parent_node->middle->left->options = for_input.first;
                parent_node->middle->middle->options = for_input.second;
            } else if (side == 1) {
                (parent_node->left)->left->options = for_input.first;
                (parent_node->left)->middle->options.push_back(temp_node[0]);

                parent_node->middle->left->options.push_back(temp_node[2]);
                parent_node->middle->middle->options = for_input.second;
            }
            else if (side == 2) {
                (parent_node->left)->left->options = for_input.first;
                (parent_node->left)->middle->options = for_input.second;

                parent_node->middle->left->options.push_back(temp_node[0]);
                parent_node->middle->middle->options.push_back(temp_node[2]);
            }
            return;
        }
    }

}

void delete_by_value_tt (tm deleting_value, tt_tree** root, tt_tree* rec_root = nullptr) {
    if (!rec_root) {rec_root = *root;}
    if (rec_root->left) { delete_by_value_tt(deleting_value, root, rec_root->left); }
    if (rec_root->middle) { delete_by_value_tt(deleting_value, root, rec_root->middle); }
    if (rec_root->right) { delete_by_value_tt(deleting_value, root, rec_root->right); }

    if (rec_root->left || rec_root->middle || rec_root->right || (rec_root == *root && (((*root)->options[0] == deleting_value)||(*root)->options[1] == deleting_value))) {
        queue<tt_tree*> q;

        if (rec_root->left && (rec_root->left->options[0] == deleting_value||rec_root->left->options[1] == deleting_value)) {
            q.push(rec_root->left);
            rec_root->left = nullptr;
        } else if (rec_root->middle && (rec_root->middle->options[0] == deleting_value||rec_root->middle->options[1] == deleting_value)) {
            q.push(rec_root->middle);
            rec_root->middle = nullptr;
        } else if (rec_root->right && (rec_root->right->options[0] == deleting_value||rec_root->right->options[1] == deleting_value)) {
            q.push(rec_root->right);
            rec_root->right = nullptr;
        } else if (rec_root == *root && ((*root)->options[0] == deleting_value||(*root)->options[1] == deleting_value)) {
            q.push(rec_root);
            (*root) = nullptr;
        } else {return;}

        vector<tm> childs_data;
        while (!q.empty()) {
            tt_tree* curr_node = q.front();
            q.pop();
            for (int i = 0; i < curr_node->options.size(); i++) {
                if (!(curr_node->options[i] == deleting_value)) {childs_data.push_back(curr_node->options[i]);}
            }
            if (curr_node->left) { q.push(curr_node->left); }
            if (curr_node->middle) { q.push(curr_node->middle); }
            if (curr_node->right) { q.push(curr_node->right); }
            delete curr_node;
        }


        for (int i = 0; i < childs_data.size(); i++) {
            insert_tt(root,childs_data[i]);
        }
    }
}

tt_tree* create_random_tt(int element_amount) {
    tt_tree* first;
    if (element_amount<1) {return nullptr;}
    first = create_empty_tt();
    first->options.push_back(random_time());

    for (int i = 1; i < element_amount; i++) {
        insert_tt(&first, random_time());
    }
    return first;
}

tt_tree* find_by_date_tt(tt_tree* root, tm key) {
    bool found = false;
    while (root && !found) {
        if (root->options[0] == key || root->options[1] == key) {
            found = true;
            break;
        } else if (key < root->options[0]) {
            root = root->left;
        } else if (root->options.size() == 2) {
            if (key > root->options[0] && key < root->options[1]) {
                root = root->middle;
            } else if (key > root->options[1]) {
                root = root->right;
            }
        } else if (key > root->options[0]) {
            root = root->middle;
        }
    }
    if (found) {return root;}
    else {return nullptr;}
}

void find_by_interval_tt(tt_tree* root, tm left, tm right, vector<tt_tree*>* result) {
  tt_tree* curr = root;
    while (curr) {
        if ((curr->options[0] >= left && curr->options[0] <= right) || (curr->options[1] >= left && curr->options[1] <= right)) {
            (*result).push_back(curr);
            if (curr->left) {find_by_interval_tt(curr->left, left, right, result);}
            if (curr->middle) {find_by_interval_tt(curr->middle, left, right, result);}
            if (curr->right) {find_by_interval_tt(curr->right, left, right, result);}
            break;
        } else if (right < curr->options[0]) {
            curr = curr->left;
        } else if (curr->options.size() == 2) {
            if (left > curr->options[0] && right < curr->options[1]) {
                curr = curr->middle;
            } else if (left > curr->options[1]) {
                curr = curr->right;
            }
        } else if (left > curr->options[0]) {
            curr = curr->middle;
        }
    }
}

void output_sorted_tt(tt_tree* root, bool print = true) {
    vector<tm> all_dates;

    queue<tt_tree*> q;
    q.push(root);
    while (!q.empty()) {
        tt_tree* curr_node = q.front();
        q.pop();

        all_dates.push_back(curr_node->options[0]);
        if (curr_node->options.size() == 2) {all_dates.push_back(curr_node->options[1]);}
        if (curr_node->left) { q.push(curr_node->left); }
        if (curr_node->middle) { q.push(curr_node->middle); }
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

void do_some_function_tt(tt_tree* root, tm (*f)(tm)) {
    queue<tt_tree*> q;
    q.push(root);
    while (!q.empty()) {
        tt_tree* curr_node = q.front();
        q.pop();
        for (int i = 0; i < root->options.size(); i++) {
            curr_node->options[i] = f(curr_node->options[i]);
        }
        if (curr_node->left) { q.push(curr_node->left); }
        if (curr_node->middle) { q.push(curr_node->middle); }
        if (curr_node->right) { q.push(curr_node->right); }
    }
}

void tt_tree_output(tt_tree* root, bool is_top = true) {
    if (!root) {
        if (is_top) {cout<<"Empty tree"<<endl;}
        return;
    }
    cout<<'[';
    for (int i = 0; i < root->options.size(); i++) {
        cout<<root->options[i];
        if (i+1 != root->options.size()) {cout<<" + ";}
    }
    cout<<']';

    if (root->left || root->right || root->middle) { cout<<"( "; }
    tt_tree_output(root->left, false);
    if (root->left && root->middle) { cout<<","; }
    tt_tree_output(root->middle, false);
    if (root->middle && root->right) { cout<<","; }
    tt_tree_output(root->right, false);
    if (root->left || root->right || root->middle) { cout << " )"; }
    if (is_top) {cout<<endl;}
}


#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "tm_functions.h"
#include <ctime>

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

void interactive();

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

Tree_node* insert (int insert_value, int input_index, Tree_node* root) {      //task 3
    Tree_node* input_node = new_node(insert_value);
    queue<pair<Tree_node*, int>> q;
    int curr_index = 0;

    if (root == nullptr) { return input_node;}

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
    return root;
}
Catalog_node* add_to_catalog (string name_data, float size_data, tm upd_data, int input_index, Catalog_node* root) {      //task 3
    Catalog_node* input_node = new_catalog_node(name_data, size_data, upd_data);
    queue<pair<Catalog_node*, int>> q;
    int curr_index = 0;

    if (root == nullptr) { return input_node;}

    q.push(make_pair(root, curr_index));
    curr_index++;
    while (!q.empty()) {
        pair<Catalog_node*,int> curr_node = q.front();
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
    return root;
}
void binary_insert (int insert_value, BTree_node** root) {       //task 18
    BTree_node* input_node = new_bin_node(insert_value);

    if (*root == nullptr) {
        *root = input_node;
        return;
    }

    if (insert_value <= (*root)->data) {
        if ((*root)->left == nullptr) {
            (*root)->left = input_node;
            input_node->parent = *root;
            return;
        }
        binary_insert(insert_value, &(*root)->left);
    }
    if (insert_value > (*root)->data) {
        if ((*root)->right == nullptr) {
            (*root)->right = input_node;
            input_node->parent = *root;
            return;
        }
        binary_insert(insert_value, &(*root)->right);
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
void pre_output (Tree_node* root) {
    if (root != nullptr) {
        cout << root->data << ' ';
        for (int i = 0; i < root->child.size(); i++) { pre_output(root->child[i]); }
    }
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
void pre_binary_output (BTree_node* root) {      //task 21
    if (root != nullptr) {
        cout << root->data << ' ';
        if (root->left != nullptr) { pre_binary_output(root->left); }
        if (root->right != nullptr) { pre_binary_output(root->right); }
    }
}

void pre_catalog_output (Catalog_node* root) {
    if (root != nullptr) {
        cout <<'('<< root->name <<", "<<root->size<<", "<<root->last_update<<") ";
        for (int i = 0; i < root->child.size(); i++) { pre_catalog_output(root->child[i]); }
    }
}

void delete_by_value (int deleting_value, Tree_node* root) {        //task 15
    for (int i = 0; i < root->child.size(); i++) {
        delete_by_value(deleting_value, root->child[i]);
    }
    if (root->data == deleting_value && root->parent != nullptr) {
        for (int i = 0; i < root->child.size(); i++) {
            (root->parent)->child.push_back(root->child[i]);
        }
        for (int i = 0; i < (root->parent)->child.size(); i++) {
            if ((root->parent)->child[i] == root) {(root->parent)->child.erase((root->parent)->child.begin()+i);}
        }
        delete root;
    }
}

void catalog_size (Catalog_node* root, float* size){        //task 26
    if (root->child.empty()) {*size += root->size;}
    for (int i = 0; i < root->child.size(); i++) {
        catalog_size(root->child[i], size);
    }
}
void files_amount (Catalog_node* root, int* curr_amount) {
    if (root->child.empty()) {(*curr_amount)++;}
    for (int i = 0; i < root->child.size(); i++) {
        files_amount(root->child[i], curr_amount);
    }
}
void subdirect_amount (Catalog_node* root, int* curr_amount) {
    if (!root->child.empty()) {(*curr_amount)++;}
    for (int i = 0; i < root->child.size(); i++) {
        subdirect_amount(root->child[i], curr_amount);
    }
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

Catalog_node* copy_catalog (Catalog_node* root) {
    if (root == nullptr) {
        return nullptr;
    }
    Catalog_node* new_catalog = new_catalog_node(root->name, root->size, root->last_update);
    new_catalog->parent = root->parent;
    for (int i = 0; i < root->child.size(); i++) {
        Catalog_node* new_catalog_node = copy_catalog(root->child[i]);
        new_catalog->child.push_back(new_catalog_node);
    }

    return new_catalog;
}

bool leave_by_name (string leave_name, Catalog_node* root, Catalog_node* prev = nullptr) {
    bool same_with_filtr = true;
    for (int i = 0; i < root->child.size(); i++) {
        if(leave_by_name(leave_name, root->child[i], root)) {i--;}
    }
    for (int i = 0; i < leave_name.size(); i++) {
        if (root->name[i] != leave_name[i]) {
            same_with_filtr = false;
            break;
        }
    }
    if (!(same_with_filtr) && prev != nullptr) {
        for (int i = 0; i < root->child.size(); i++) {
            (prev)->child.push_back(root->child[i]);
            (root->child[i])->parent = prev;
        }
        for (int i = 0; i < (prev)->child.size(); i++) {
            if ((prev)->child[i] == root) {
                (prev)->child.erase(prev->child.begin() + i);
                i--;
            }
        }
        delete root;
        return 1;
    }
    return 0;
}
bool leave_by_size (float min_size, float max_size, Catalog_node* root, Catalog_node* prev = nullptr) {
    for (int i = 0; i < root->child.size(); i++) {
        if(leave_by_size(min_size, max_size, root->child[i], root)) {i--;}
    }
    if (((min_size!= -1&&root->size<min_size)||(max_size!= -1&&root->size>max_size))&& prev != nullptr) {
        for (int i = 0; i < root->child.size(); i++) {
            (prev)->child.push_back(root->child[i]);
            (root->child[i])->parent = prev;
        }
        for (int i = 0; i < (prev)->child.size(); i++) {
            if (prev->child[i] == root) {prev->child.erase(prev->child.begin()+i);}
        }
        delete root;
        return 1;
    }
    return 0;
}
bool leave_by_update (tm min_date, tm max_date, Catalog_node* root, Catalog_node* prev = nullptr) {
    for (int i = 0; i < root->child.size(); i++) {
        if(leave_by_update(min_date, max_date, root->child[i], root)) {i--;}
    }
    if ((root->last_update<min_date||root->last_update>max_date)&& prev != nullptr) {
        for (int i = 0; i < root->child.size(); i++) {
            (prev)->child.push_back(root->child[i]);
            (root->child[i])->parent = prev;
        }
        for (int i = 0; i < prev->child.size(); i++) {
            if (prev->child[i] == root) {prev->child.erase(prev->child.begin()+i);}
        }
        delete root;
        return 1;
    }
    return 0;
}

void name_filter (Catalog_node* root, string name_filter, Catalog_node** new_catalog) {
    *new_catalog = new_catalog_node(root->name, root->size, root->last_update);
    (*new_catalog) = copy_catalog(root);
    leave_by_name(name_filter, *new_catalog);
}
void size_filter (Catalog_node* root, float min_size, float max_size, Catalog_node** new_catalog) {
    *new_catalog = new_catalog_node(root->name, root->size, root->last_update);
    *new_catalog = copy_catalog(root);
    leave_by_size(min_size,max_size, *new_catalog);
}
void update_filter (Catalog_node* root, tm min_date, tm max_date, Catalog_node** new_catalog) {
    *new_catalog = new_catalog_node(root->name, root->size, root->last_update);
    *new_catalog = copy_catalog(root);
    leave_by_update(min_date, max_date, *new_catalog);
}

void demonstration_insert(Tree_node* root, int index) {
    int new_value = rand()%10;
    cout<<"Insert new node with input index "<< index <<'('<<new_value<<"): ";
    insert(new_value, 0, root);
    pre_output(root);
    cout<<endl;
};
void demonstration_catalog_insert(Catalog_node** root, int index) {
    int size = rand()%101, name_size =rand()%5+1;
    tm date = random_time();
    string name = "";
    for (int i = 0; i < name_size; i++) {
        name += (char) (rand()%26 + 97);
    }
    cout<<"Insert new node with input index "<< index <<'('<<name<<", "<<size<<", "<<date<<"): ";
    *root = add_to_catalog(name,size,date,index,*root);
    pre_catalog_output(*root);
    cout<<endl;
};
void demonstration_bin_insert(BTree_node* root) {
    int new_value = rand()%10;
    cout<<"Insert new node"<<'('<<new_value<<"): ";
    binary_insert(new_value, &root);
    pre_binary_output(root);
    cout<<endl;
};
void demonstration_delete(Tree_node* root) {
    int new_value = rand()%10;
    cout<<"Delete nodes with value "<<new_value<<": ";
    delete_by_value(new_value, root);
    pre_output(root);
    cout<<endl;
};

void demonstration() {
    Tree_node* tree_root = new_node(rand()%10);
    BTree_node* bin_tree_root = new_bin_node(rand()%10);
    Catalog_node* catalog_root = nullptr;
    string letter = "";
    tm date;

    cout<<"\nGeneral tree: \n"<<endl;
    cout<<"Created tree only with root: ";
    pre_output(tree_root);
    cout<<endl;
    demonstration_insert(tree_root, 0);
    demonstration_insert(tree_root, 0);
    demonstration_insert(tree_root, 1);
    demonstration_insert(tree_root, 1);
    demonstration_insert(tree_root, 1);
    demonstration_insert(tree_root, 2);
    demonstration_insert(tree_root, 4);

    for (int i = 0; i < 3; i++) {
        demonstration_delete(tree_root);
    }

    cout<<"\nBinary tree: \n"<<endl;
    for (int i = 0; i < 7; i++) {
        demonstration_bin_insert(bin_tree_root);
    }

    cout<<"\nCatalog tree: \n"<<endl;
    for (int i = 0; i<4; i++) {
       demonstration_catalog_insert(&catalog_root, 0);
    }
    demonstration_catalog_insert(&catalog_root, 2);
    demonstration_catalog_insert(&catalog_root, 1);
    demonstration_catalog_insert(&catalog_root, 3);
    demonstration_catalog_insert(&catalog_root, 5);

    float size = 0;
    catalog_size(catalog_root, &size);
    cout<<"General size of catalog: " << size <<endl;

    int amount = 0;
    files_amount(catalog_root, &amount);
    cout<<"Amount of files in catalog: " << amount <<endl;

    amount = 0;
    subdirect_amount(catalog_root, &amount);
    cout<<"Amount of subdirectories: " << amount <<endl;

    date = min_last_upd(catalog_root);
    cout<<"Minimum last update time: " << date<<endl;

    date = max_last_upd(catalog_root);
    cout<<"Maximum last update time: " << date <<endl;

    Catalog_node* filtred_catalog = nullptr;
    letter += (char) (rand()%26 + 97);
    cout<<"Name filter (only nodes that begins on "<<letter<<" (plus root)): "<<endl;
    name_filter(catalog_root, letter, &filtred_catalog);
    pre_catalog_output(filtred_catalog);
    cout<<endl;

    filtred_catalog = nullptr;
    cout<<"Size filter (only nodes with size more than 30 (plus root)): "<<endl;
    size_filter(catalog_root, 30, -1, &filtred_catalog);
    pre_catalog_output(filtred_catalog);
    cout<<endl;

    filtred_catalog = nullptr;
    tm min_date = random_time();
    tm max_date = random_time();
    while (min_date > max_date) { max_date = random_time(); }
    cout<<"Update filter (only nodes with last update earlier than "<<max_date<<" and later than " << min_date<<" (plus root)): "<<endl;
    update_filter(catalog_root,min_date, max_date, &filtred_catalog);
    pre_catalog_output(filtred_catalog);
    cout<<endl;
}

void interactive_generic(Tree_node** root) {
    int mode = 0, value, index;
    cout<<"Create new tree - enter 1"<<endl;
    cout<<"Add node to tree - enter 2"<<endl;
    cout<<"Delete nodes by value - enter 3"<<endl;
    cout<<"Output tree - enter 4"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            if (*root != nullptr) {*root = nullptr;}
            break;
        }
        case 2: {
            cout<<"Enter new value and insert index"<<endl;
            cin>>value>>index;
            *root =insert(value,index,*root);
            break;
        }
        case 3: {
            cout<<"Enter value to delete"<<endl;
            cin>>value;
            delete_by_value(value, *root);
            break;
        }
        case 4: {
            interactive_output(*root);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_generic(root);
}
void interactive_binary(BTree_node** root) {
    int mode = 0, value;
    cout<<"Create new tree - enter 1"<<endl;
    cout<<"Add node to tree - enter 2"<<endl;
    cout<<"Interative output - enter 3"<<endl;
    cout<<"Pre-order output - enter 4"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            if (*root != nullptr) {*root = nullptr;}
            break;
        }
        case 2: {
            cout<<"Enter new value"<<endl;
            cin>>value;
            binary_insert(value, root);
            break;
        }
        case 3: {
            binary_interactive_output(*root);
            break;
        }
        case 4: {
            pre_binary_output(*root);
            cout<<endl;
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_binary(root);
}
void interactive_catalog (Catalog_node** root) {
    int mode = 0, index = 0;
    Catalog_node* filtred = nullptr;
    float size;
    tm date;
    string name;
    cout<<"Create new catalog - enter 1"<<endl;
    cout<<"Add node to catalog - enter 2"<<endl;
    cout<<"Output catalog - enter 3"<<endl;
    cout<<"Find general size of catalog - enter 4"<<endl;
    cout<<"Find amount of files in catalog - enter 5"<<endl;
    cout<<"Find amount of subdirectories in catalog - enter 6"<<endl;
    cout<<"Find minimum last update time - enter 7"<<endl;
    cout<<"Find maximum last update time - enter 8"<<endl;
    cout<<"Filter catalog by name - enter 9"<<endl;
    cout<<"Filter catalog by size - enter 10"<<endl;
    cout<<"Filter catalog by date - enter 11"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            if (*root != nullptr) {*root = nullptr;}
            break;
        }
        case 2: {
            cout<<"Enter name, size, date and index for insert"<<endl;
            cin>>name>>size>>date>>index;
            *root = add_to_catalog(name,size,date,index,*root);
            break;
        }
        case 3: {
            pre_catalog_output(*root);
            cout<<endl;
            break;
        }
        case 4: {
            float size = 0;
            catalog_size(*root, &size);
            cout<<"General size of catalog: " << size <<endl;
            break;
        }
        case 5: {
            int amount = 0;
            files_amount(*root, &amount);
            cout<<"Amount of files in catalog: " << amount <<endl;
            break;
        }
        case 6: {
            int amount = 0;
            subdirect_amount(*root, &amount);
            cout<<"Amount of subdirectories: " << amount <<endl;
            break;
        }
        case 7: {
            date = min_last_upd(*root);
            cout<<"Minimum last update time: " << date<<endl;
            break;
        }
        case 8: {
            date = max_last_upd(*root);
            cout<<"Maximum last update time: " << date <<endl;
            break;
        }
        case 9: {
            filtred = nullptr;
            cout<<"Enter name filter"<<endl;
            cin>>name;
            name_filter(*root,name,&filtred);
            cout<<"Filtred catalog: "<<endl;
            pre_catalog_output(filtred);
            cout<<endl;
            break;
        }
        case 10: {
            float min_size, max_size;
            filtred = nullptr;
            cout<<"Enter size filter(min and max size)"<<endl;
            cout<<"(enter -1 for one of the limit if you don't wont to have it)"<<endl;
            cin>>min_size>>max_size;
            size_filter(*root,min_size,max_size,&filtred);
            cout<<"Filtred catalog: "<<endl;
            pre_catalog_output(filtred);
            cout<<endl;
            break;
        }
        case 11: {
            tm min_date, max_date;
            filtred = nullptr;
            cout<<"Enter update filter(min and max last update time)"<<endl;
            cin>>min_date>>max_date;
            update_filter(*root, min_date, max_date, &filtred);
            cout<<"Filtred catalog: "<<endl;
            pre_catalog_output(filtred);
            cout<<endl;
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_catalog(root);
}

int interactive_options() {
    int mode = 0;
    cout<<"Work with generic tree - enter 1"<<endl;
    cout<<"Work with binary tree - enter 2"<<endl;
    cout<<"Work with catalog - enter 3"<<endl;
    cout<<"Exit - enter 0"<<endl;
    cin>>mode;
    return mode;
}
void interactive() {
    int mode = 0;
    mode = interactive_options();
    switch(mode) {
        case 0: {
          return;
        }
        case 1: {
            Tree_node* groot = nullptr;
            interactive_generic(&groot);
            break;
        }
        case 2: {
            BTree_node* broot = nullptr;
            interactive_binary(&broot);
            break;
        }
        case 3: {
            Catalog_node* croot = nullptr;
            interactive_catalog(&croot);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
        }
    }
}

int main() {
    int mode;
    srand(time(0));

    cout << "For interactive mode enter 1" << endl;
    cout << "For demonstration mode enter 2" << endl;
    cin>>mode;
    if (mode == 1) {interactive();}
    if (mode == 2) {demonstration();}

    return 0;
}
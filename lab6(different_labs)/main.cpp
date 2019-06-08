#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "tm_functions.h"
#include "linked_list.h"
#include "array_list.h"
#include "binary_tree.h"
#include "AVL_tree.h"
#include "2_3_tree.h"

using namespace std;

tm some_function (tm date) {
    date.tm_year++;
    return date;
}

void demonstration_linked() {
    cout<<"1. Linked list"<<endl;
    int amount = rand()%10+1;
    cout<<"Fill list with "<<amount<<" random elements: "<<endl;
    linked_list* linked_sample = create_empty();
    linked_sample = create_random_list(amount);
    cout<<"List now: "<<endl;
    output_list(linked_sample);
    tm first_date = random_time(), second_date = random_time();
    cout<<"Add element "<<first_date<<" and "<<second_date<<" to list:"<<endl;
    add_to_list(&linked_sample, first_date);
    add_to_list(&linked_sample, second_date);
    cout<<"List now: "<<endl;
    output_list(linked_sample);
    cout<<"Lets delete element "<<(linked_sample->next)->data<<": "<<endl;
    delete_element(&linked_sample,(linked_sample->next)->data);
    cout<<"List now: "<<endl;
    output_list(linked_sample);
    vector<linked_list*> search_linked;
    cout<<"Lets find element "<<(linked_sample->next)->data<<": "<<endl;
    search_linked = find_by_date(linked_sample, (linked_sample->next)->data);
    if (search_linked.empty()) {cout<<"there is no such date"<<endl;}
    else {
        for (int i = 0; i < search_linked.size(); i++) {
            cout<<search_linked[i]<<"("<<search_linked[i]->data<<")"<<"   ";
        }
        cout<<endl;
    }
    first_date = random_time();
    do {second_date = random_time();} while (first_date>second_date);
    cout<<"Lets find elements in interval "<<first_date<<"  -   "<<second_date<<": "<<endl;
    search_linked = find_by_interval(linked_sample, first_date, second_date);
    if (search_linked.empty()) {cout<<"there is no such date"<<endl;}
    else {
        for (int i = 0; i < search_linked.size(); i++) {
            cout<<search_linked[i]<<"("<<search_linked[i]->data<<")"<<"   ";
        }
        cout<<endl;
    }
    cout<<"Lets sort our list:"<<endl;
    sort_list(linked_sample);
    cout<<"Lets do some function - increment every year in the list:"<<endl;
    do_some_function(linked_sample, some_function);
    output_list(linked_sample);
}
void demonstration_array() {
    cout<<"2. Array list"<<endl;
    int amount = rand()%10+1;
    cout<<"Fill list with "<<amount<<" random elements: "<<endl;
    array_list* array_sample = create_arr_empty();
    array_sample = create_random_arr_list(amount);
    cout<<"List now: "<<endl;
    output_arr_list(array_sample);
    tm first_date = random_time(), second_date = random_time();
    cout<<"Add element "<<first_date<<" and "<<second_date<<" to list:"<<endl;
    add_to_arr_list(&array_sample, first_date);
    add_to_arr_list(&array_sample, second_date);
    cout<<"List now: "<<endl;
    output_arr_list(array_sample);
    cout<<"Lets delete element "<<(array_sample)->data[1]<<": "<<endl;
    delete_arr_element(array_sample,array_sample->data[1]);
    cout<<"List now: "<<endl;
    output_arr_list(array_sample);
    vector<tm*> search_array;
    cout<<"Lets find element "<<array_sample->data[1]<<": "<<endl;
    search_array = find_by_date_arr(array_sample, array_sample->data[1]);
    if (search_array.empty()) {cout<<"there is no such date"<<endl;}
    else {
        for (int i = 0; i < search_array.size(); i++) {
            cout<<search_array[i]<<"("<<*search_array[i]<<")"<<"   ";
        }
        cout<<endl;
    }
    first_date = random_time();
    do {second_date = random_time();} while (first_date>second_date);
    cout<<"Lets find elements in interval "<<first_date<<"  -   "<<second_date<<": "<<endl;
    search_array = find_by_interval_arr(array_sample, first_date, second_date);
    if (search_array.empty()) {cout<<"there is no such date"<<endl;}
    else {
        for (int i = 0; i < search_array.size(); i++) {
            cout<<search_array[i]<<"("<<*search_array[i]<<")"<<"   ";
        }
        cout<<endl;
    }
    cout<<"Lets sort our list:"<<endl;
    sort_arr_list(array_sample);
    cout<<"Lets do some function - increment every year in the list:"<<endl;
    do_some_function_arr(array_sample, some_function);
    output_arr_list(array_sample);
}
void demonstration_btree() {
    cout<<"3. Binary search tree"<<endl;
    int amount = rand()%10+1;
    cout<<"Fill tree with "<<amount<<" random elements: "<<endl;
    btree_node* sample = create_empty_btree();
    sample = create_random_btree(amount);
    cout<<"Tree now: "<<endl;
    binary_tree_output(sample);
    tm first_date = random_time(), second_date = random_time();
    cout<<"Add element "<<first_date<<" and "<<second_date<<" to tree:"<<endl;
    insert(&sample, first_date);
    insert(&sample, second_date);
    cout<<"Tree now: "<<endl;
    binary_tree_output(sample);
    cout<<"Lets delete element "<<(sample)->data<<": "<<endl;
    delete_by_value((sample)->data, &sample);
    cout<<"Tree now: "<<endl;
    binary_tree_output(sample);
    vector<btree_node*> search;
    search.resize(1);
    if ((sample)->right) {
        cout<<"Lets find element "<<(sample)->right->data<<": "<<endl;
        search[0] = find_by_date_btree(sample, (sample)->right->data);
    }
    else {
        cout<<"Lets find element "<<(sample)->left->data<<": "<<endl;
        search[0] = find_by_date_btree(sample, (sample)->left->data);
    }
    if (!search[0]) {cout<<"there is no such date"<<endl;}
    else {
        cout<<search[0]<<"("<<search[0]->data<<")"<<"   "<<endl;
    }
    first_date = random_time();
    do {second_date = random_time();} while (first_date>second_date);
    cout<<"Lets find elements in interval "<<first_date<<"  -   "<<second_date<<": "<<endl;
    search.clear();
    find_by_interval_btree(sample, first_date, second_date, &search);
    if (search.empty()) {cout<<"there is no such date"<<endl;}
    else {
        for (int i = 0; i < search.size(); i++) {
            cout<<search[i]<<"("<<search[i]->data<<")"<<"   ";
        }
        cout<<endl;
    }
    cout<<"Output sorted tree:"<<endl;
    output_sorted_btree(sample);
    cout<<"Lets do some function - increment every year in the tree:"<<endl;
    do_some_function_btree(sample, some_function);
    binary_tree_output(sample);
    output_sorted_btree(sample);
}
void demonstration_avltree() {
    cout<<"3. AVL tree"<<endl;
    int amount = rand()%10+1;
    cout<<"Fill tree with "<<amount<<" random elements: "<<endl;
    avl_node* sample = create_empty_avl();
    sample = create_random_avl_tree(amount);
    cout<<"Tree now: "<<endl;
    avl_tree_output(sample);
    tm first_date = random_time(), second_date = random_time();
    cout<<"Add element "<<first_date<<" and "<<second_date<<" to tree:"<<endl;
    sample = insert_avl(sample, first_date);
    sample = insert_avl(sample, second_date);
    cout<<"Tree now: "<<endl;
    avl_tree_output(sample);
    cout<<"Lets delete element "<<(sample)->data<<": "<<endl;
    delete_by_value_avl((sample)->data, &sample);
    cout<<"Tree now: "<<endl;
    avl_tree_output(sample);
    vector<avl_node*> search;
    search.resize(1);
    if ((sample)->right) {
        cout<<"Lets find element "<<(sample)->right->data<<": "<<endl;
        search[0] = find_by_date_avl(sample, (sample)->right->data);
    }
    else {
        cout<<"Lets find element "<<(sample)->left->data<<": "<<endl;
        search[0] = find_by_date_avl(sample, (sample)->left->data);
    }
    if (!search[0]) {cout<<"there is no such date"<<endl;}
    else {
        cout<<search[0]<<"("<<search[0]->data<<")"<<"   "<<endl;
    }
    first_date = random_time();
    do {second_date = random_time();} while (first_date>second_date);
    cout<<"Lets find elements in interval "<<first_date<<"  -   "<<second_date<<": "<<endl;
    search.clear();
    find_by_interval_avl(sample, first_date, second_date, &search);
    if (search.empty()) {cout<<"there is no such date"<<endl;}
    else {
        for (int i = 0; i < search.size(); i++) {
            cout<<search[i]<<"("<<search[i]->data<<")"<<"   ";
        }
        cout<<endl;
    }
    cout<<"Output sorted tree:"<<endl;
    output_sorted_avl(sample);
    cout<<"Lets do some function - increment every year in the tree:"<<endl;
    do_some_function_avl(sample, some_function);
    avl_tree_output(sample);
    output_sorted_avl(sample);
}
void demonstration_23_tree() {
    cout<<"5. 2-3 tree"<<endl;
    int amount = rand()%10+1;
    cout<<"Fill tree with "<<amount<<" random elements: "<<endl;
    tt_tree* sample = create_empty_tt();
    sample = create_random_tt(amount);
    cout<<"Tree now: "<<endl;
    tt_tree_output(sample);
    tm first_date = random_time(), second_date = random_time();
    cout<<"Add element "<<first_date<<" and "<<second_date<<" to tree:"<<endl;
    insert_tt(&sample, first_date);
    insert_tt(&sample, second_date);
    cout<<"Tree now: "<<endl;
    tt_tree_output(sample);
    cout<<"Lets delete element "<<(sample)->options[0]<<": "<<endl;
    delete_by_value_tt((sample)->options[0], &sample);
    cout<<"Tree now: "<<endl;
    tt_tree_output(sample);
    vector<tt_tree*> search;
    search.resize(1);
    if ((sample)->right) {
        cout<<"Lets find element "<<(sample)->right->options[0]<<": "<<endl;
        search[0] = find_by_date_tt(sample, (sample)->right->options[0]);
    }
    else {
        cout<<"Lets find element "<<(sample)->left->options[0]<<": "<<endl;
        search[0] = find_by_date_tt(sample, (sample)->left->options[0]);
    }
    if (!search[0]) {cout<<"there is no such date"<<endl;}
    else {
        cout<<search[0]<<"("<<search[0]->options[0];
        if (search[0]->options.size() == 2) {cout<<", "<< search[0]->options[1]<<")"<<"   "<<endl;}
        else {cout<<")"<<"   "<<endl;}
    }
    first_date = random_time();
    do {second_date = random_time();} while (first_date>second_date);
    cout<<"Lets find elements in interval "<<first_date<<"  -   "<<second_date<<": "<<endl;
    search.clear();
    find_by_interval_tt(sample, first_date, second_date, &search);
    if (search.empty()) {cout<<"there is no such date"<<endl;}
    else {
        for (int i = 0; i < search.size(); i++) {
            cout<<search[i]<<"("<<search[i]->options[0];
            if (search[i]->options.size() == 2) {cout<<", "<< search[i]->options[1]<<")"<<"   "<<endl;}
            else {cout<<")"<<"   "<<endl;}
        }
        cout<<endl;
    }
    cout<<"Output sorted tree:"<<endl;
    output_sorted_tt(sample);
    cout<<"Lets do some function - increment every year in the tree:"<<endl;
    do_some_function_tt(sample, some_function);
    tt_tree_output(sample);
    output_sorted_tt(sample);
}
void demonstration() {
    demonstration_linked();
    demonstration_array();
    demonstration_btree();
    demonstration_avltree();
    demonstration_23_tree();
}

void interactive();
void interactive_linked (linked_list** sample) {
    int mode = 0;
    tm date;

    cout<<"Create empty list - enter 1"<<endl;
    cout<<"Add date to list - enter 2"<<endl;
    cout<<"Output list - enter 3"<<endl;
    cout<<"Create random list - enter 4"<<endl;
    cout<<"Delete date from list - enter 5"<<endl;
    cout<<"Find by date - enter 6"<<endl;
    cout<<"Find by interval - enter 7"<<endl;
    cout<<"Sort list by ascending order - enter 8"<<endl;
    cout<<"Do some function (increment every date year) - enter 9"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            *sample = create_empty();
            break;
        }
        case 2: {
            cout<<"Enter date (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            add_to_list(sample, date);
            break;
        }
        case 3: {
            output_list(*sample);
            break;
        }
        case 4: {
            cout<<"Enter amount of elements"<<endl;
            int amount;
            cin>>amount;
            *sample = create_random_list(amount);
            break;
        }
        case 5: {
            cout<<"Enter date to delete from list (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            delete_element(sample,date);
            break;
        }
        case 6: {
            cout<<"Enter date to find (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            vector<linked_list*>search_linked = find_by_date(*sample, date);
            if (search_linked.empty()) {cout<<"there is no such date"<<endl;}
            else {
                for (int i = 0; i < search_linked.size(); i++) {
                    cout<<search_linked[i]<<"("<<search_linked[i]->data<<")"<<"   ";
                }
                cout<<endl;
            }
            break;
        }
        case 7: {
            cout<<"Enter start date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            tm end_date;
            cout<<"Enter end date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>end_date;
            vector<linked_list*>search_linked = find_by_interval(*sample, date, end_date);
            if (search_linked.empty()) {cout<<"there is no such dates"<<endl;}
            else {
                for (int i = 0; i < search_linked.size(); i++) {
                    cout<<search_linked[i]<<"("<<search_linked[i]->data<<")"<<"   ";
                }
                cout<<endl;
            }
            break;
        }
        case 8: {
            sort_list(*sample);
            break;
        }
        case 9: {
            do_some_function(*sample, some_function);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_linked(sample);
}
void interactive_array (array_list** sample) {
    int mode = 0;
    tm date;

    cout<<"Create empty list - enter 1"<<endl;
    cout<<"Add date to list - enter 2"<<endl;
    cout<<"Output list - enter 3"<<endl;
    cout<<"Create random list - enter 4"<<endl;
    cout<<"Delete date from list - enter 5"<<endl;
    cout<<"Find by date - enter 6"<<endl;
    cout<<"Find by interval - enter 7"<<endl;
    cout<<"Sort list by ascending order - enter 8"<<endl;
    cout<<"Do some function (increment every date year) - enter 9"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            *sample = create_arr_empty();
            break;
        }
        case 2: {
            cout<<"Enter date (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            add_to_arr_list(sample, date);
            break;
        }
        case 3: {
            output_arr_list(*sample);
            break;
        }
        case 4: {
            cout<<"Enter amount of elements"<<endl;
            int amount;
            cin>>amount;
            *sample = create_random_arr_list(amount);
            break;
        }
        case 5: {
            cout<<"Enter date to delete from list (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            delete_arr_element(*sample,date);
            break;
        }
        case 6: {
            cout<<"Enter date to find (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            vector<tm*> search_array;
            search_array = find_by_date_arr(*sample, date);
            if (search_array.empty()) {cout<<"there is no such date"<<endl;}
            else {
                for (int i = 0; i < search_array.size(); i++) {
                    cout<<search_array[i]<<"("<<*search_array[i]<<")"<<"   ";
                }
                cout<<endl;
            }
            break;
        }
        case 7: {
            cout<<"Enter start date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            tm end_date;
            cout<<"Enter end date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>end_date;
            vector<tm*> search_array;
            search_array = find_by_interval_arr(*sample, date, end_date);
            if (search_array.empty()) {cout<<"there is no such date"<<endl;}
            else {
                for (int i = 0; i < search_array.size(); i++) {
                    cout<<search_array[i]<<"("<<*search_array[i]<<")"<<"   ";
                }
                cout<<endl;
            }
            break;
        }
        case 8: {
            sort_arr_list(*sample);
            break;
        }
        case 9: {
            do_some_function_arr(*sample, some_function);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_array(sample);
}
void interactive_btree (btree_node** sample) {
    int mode = 0;
    tm date;

    cout<<"Create empty tree - enter 1"<<endl;
    cout<<"Add date to tree - enter 2"<<endl;
    cout<<"Output tree - enter 3"<<endl;
    cout<<"Create random tree - enter 4"<<endl;
    cout<<"Delete date from tree - enter 5"<<endl;
    cout<<"Find by date - enter 6"<<endl;
    cout<<"Find by interval - enter 7"<<endl;
    cout<<"Output tree by ascending order - enter 8"<<endl;
    cout<<"Do some function (increment every date year) - enter 9"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            *sample = create_empty_btree();
            break;
        }
        case 2: {
            cout<<"Enter date (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            insert(sample, date);
            break;
        }
        case 3: {
            binary_tree_output(*sample);
            break;
        }
        case 4: {
            cout<<"Enter amount of elements"<<endl;
            int amount;
            cin>>amount;
            *sample = create_random_btree(amount);
            break;
        }
        case 5: {
            cout<<"Enter date to delete from list (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            delete_by_value(date, sample);
            break;
        }
        case 6: {
            cout<<"Enter date to find (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            btree_node* search;

            search = find_by_date_btree(*sample, date);
            if (!search) {cout<<"there is no such date"<<endl;}
            else { cout<<search<<"("<<search->data<<")"<<"   "<<endl; }
            break;
        }
        case 7: {
            cout<<"Enter start date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            tm end_date;
            cout<<"Enter end date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>end_date;
            vector<btree_node*> search;
            find_by_interval_btree(*sample, date, end_date, &search);
            if (search.empty()) {cout<<"there is no such date"<<endl;}
            else {
                for (int i = 0; i < search.size(); i++) {
                    cout<<search[i]<<"("<<search[i]->data<<")"<<"   ";
                }
                cout<<endl;
            }
            break;
        }
        case 8: {
            output_sorted_btree(*sample);
            break;
        }
        case 9: {
            do_some_function_btree(*sample, some_function);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_btree(sample);
}
void interactive_avltree (avl_node** sample) {
    int mode = 0;
    tm date;

    cout<<"Create empty tree - enter 1"<<endl;
    cout<<"Add date to tree - enter 2"<<endl;
    cout<<"Output tree - enter 3"<<endl;
    cout<<"Create random tree - enter 4"<<endl;
    cout<<"Delete date from tree - enter 5"<<endl;
    cout<<"Find by date - enter 6"<<endl;
    cout<<"Find by interval - enter 7"<<endl;
    cout<<"Output tree by ascending order - enter 8"<<endl;
    cout<<"Do some function (increment every date year) - enter 9"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            *sample = create_empty_avl();
            break;
        }
        case 2: {
            cout<<"Enter date (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            *sample = insert_avl(*sample, date);
            break;
        }
        case 3: {
            avl_tree_output(*sample);
            break;
        }
        case 4: {
            cout<<"Enter amount of elements"<<endl;
            int amount;
            cin>>amount;
            *sample = create_random_avl_tree(amount);
            break;
        }
        case 5: {
            cout<<"Enter date to delete from list (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            delete_by_value_avl(date, sample);
            break;
        }
        case 6: {
            cout<<"Enter date to find (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            avl_node* search;

            search = find_by_date_avl(*sample, date);
            if (!search) {cout<<"there is no such date"<<endl;}
            else { cout<<search<<"("<<search->data<<")"<<"   "<<endl; }
            break;
        }
        case 7: {
            cout<<"Enter start date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            tm end_date;
            cout<<"Enter end date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>end_date;
            vector<avl_node*> search;
            find_by_interval_avl(*sample, date, end_date, &search);
            if (search.empty()) {cout<<"there is no such date"<<endl;}
            else {
                for (int i = 0; i < search.size(); i++) {
                    cout<<search[i]<<"("<<search[i]->data<<")"<<"   ";
                }
                cout<<endl;
            }
            break;
        }
        case 8: {
            output_sorted_avl(*sample);
            break;
        }
        case 9: {
            do_some_function_avl(*sample, some_function);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_avltree(sample);
}
void interactive_23tree (tt_tree** sample) {
    int mode = 0;
    tm date;

    cout<<"Create empty tree - enter 1"<<endl;
    cout<<"Add date to tree - enter 2"<<endl;
    cout<<"Output tree - enter 3"<<endl;
    cout<<"Create random tree - enter 4"<<endl;
    cout<<"Delete date from tree - enter 5"<<endl;
    cout<<"Find by date - enter 6"<<endl;
    cout<<"Find by interval - enter 7"<<endl;
    cout<<"Output tree by ascending order - enter 8"<<endl;
    cout<<"Do some function (increment every date year) - enter 9"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            *sample = create_empty_tt();
            break;
        }
        case 2: {
            cout<<"Enter date (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            insert_tt(sample, date);
            break;
        }
        case 3: {
            tt_tree_output(*sample);
            break;
        }
        case 4: {
            cout<<"Enter amount of elements"<<endl;
            int amount;
            cin>>amount;
            *sample = create_random_tt(amount);
            break;
        }
        case 5: {
            cout<<"Enter date to delete from list (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            delete_by_value_tt(date, sample);
            break;
        }
        case 6: {
            cout<<"Enter date to find (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            tt_tree* search;

            search = find_by_date_tt(*sample, date);
            if (!search) {cout<<"there is no such date"<<endl;}
            else {
                cout<<search<<"("<<search->options[0];
                if (search->options.size() == 2) {cout<<", "<< search->options[1]<<")"<<"   "<<endl;}
                else {cout<<")"<<"   "<<endl;}
            }
            break;
        }
        case 7: {
            cout<<"Enter start date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>date;
            tm end_date;
            cout<<"Enter end date to find by interval (day, month, year, hour, minute, second)"<<endl;
            cin>>end_date;
            vector<tt_tree*> search;
            find_by_interval_tt(*sample, date, end_date, &search);
            if (search.empty()) {cout<<"there is no such date"<<endl;}
            else {
                for (int i = 0; i < search.size(); i++) {
                    cout<<search[i]<<"("<<search[i]->options[0];
                    if (search[i]->options.size() == 2) {cout<<", "<< search[i]->options[1]<<")"<<"   "<<endl;}
                    else {cout<<")"<<"   "<<endl;}
                }
                cout<<endl;
            }
            break;
        }
        case 8: {
            output_sorted_tt(*sample);
            break;
        }
        case 9: {
            do_some_function_tt(*sample, some_function);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_23tree(sample);
}
int interactive_options() {
    int mode = 0;
    cout<<"Work with linked list - enter 1"<<endl;
    cout<<"Work with array list - enter 2"<<endl;
    cout<<"Work with binary search tree - enter 3"<<endl;
    cout<<"Work with AVL tree - enter 4"<<endl;
    cout<<"Work with 2-3 tree - enter 5"<<endl;
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
            linked_list* sample = nullptr;
            interactive_linked(&sample);
            break;
        }
        case 2: {
            array_list* sample = nullptr;
            interactive_array(&sample);
            break;
        }
        case 3: {
            btree_node* sample = nullptr;
            interactive_btree(&sample);
            break;
        }
        case 4: {
            avl_node* sample = nullptr;
            interactive_avltree(&sample);
            break;
        }
        case 5: {
            tt_tree* sample = nullptr;
            interactive_23tree(&sample);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
        }
    }
}

void benchmark() {
    int count, count_sec;
    clock_t benchmark_clock;
    ofstream benchmark_linked_file;
    benchmark_linked_file.open("benchmark_linked.txt");

    tm first_date = random_time(), second_date;
    do { second_date = random_time();} while (first_date>second_date);
    benchmark_linked_file << "Results with linked list:" << "\r\n";
    count = 10;
    while (count) {
        benchmark_clock = clock();

        linked_list* linked_sample = create_empty();
        linked_sample = create_random_list(count);
        vector<linked_list*> search_linked;
        search_linked = find_by_date(linked_sample, first_date);
        search_linked = find_by_interval(linked_sample, first_date, second_date);
        sort_list(linked_sample, false);
        do_some_function(linked_sample, some_function);

        benchmark_linked_file << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << "\r\n";
        cout << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << endl;

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) { break; }
        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec/4 + count; }

    }
    ofstream benchmark_array_file;
    benchmark_array_file.open("benchmark_array.txt");
    benchmark_array_file << "Results with array list:" << "\r\n";
    count = 10;
    while (count) {
        benchmark_clock = clock();

        array_list* arr_sample = create_arr_empty();
        arr_sample = create_random_arr_list(count);
        vector<tm*> search;
        search = find_by_date_arr(arr_sample, first_date);
        search = find_by_interval_arr(arr_sample, first_date, second_date);
        sort_arr_list(arr_sample, false);
        do_some_function_arr(arr_sample, some_function);

        benchmark_array_file << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << "\r\n";
        cout << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << endl;

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) { break; }
        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec + count; }

    }
    ofstream benchmark_btree_file;
    benchmark_btree_file.open("benchmark_btree.txt");
    benchmark_btree_file << "Results with binary search tree:" << "\r\n";
    count = 10;
    while (count) {
        benchmark_clock = clock();

        btree_node* btree_sample = create_empty_btree();
        btree_sample = create_random_btree(count);
        vector<btree_node*> search;
        find_by_date_btree(btree_sample, first_date);
        find_by_interval_btree(btree_sample, first_date, second_date, &search);
        search.clear();
        output_sorted_btree(btree_sample, false);
        do_some_function_btree(btree_sample, some_function);

        benchmark_btree_file << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << "\r\n";
        cout << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << endl;

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) { break; }
        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec + count; }
    }
    ofstream benchmark_avltree_file;
    benchmark_avltree_file.open("benchmark_avltree.txt");
    benchmark_avltree_file << "Results with AVL tree:" << "\r\n";
    count = 10;
    while (count) {
        benchmark_clock = clock();

        avl_node* avl_sample = create_empty_avl();
        avl_sample = create_random_avl_tree(count);
        vector<avl_node*> search;
        find_by_date_avl(avl_sample, first_date);
        find_by_interval_avl(avl_sample, first_date, second_date, &search);
        search.clear();
        output_sorted_avl(avl_sample, false);
        do_some_function_avl(avl_sample, some_function);

        benchmark_avltree_file << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << "\r\n";
        cout << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << endl;

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) { break; }
        count += 100;
    }
    ofstream benchmark_23tree_file;
    benchmark_23tree_file.open("benchmark_23tree.txt");
    benchmark_23tree_file << "Results with 23 tree:" << "\r\n";
    count = 10;
    while (count) {
        benchmark_clock = clock();

        tt_tree* tt_sample = create_empty_tt();
        tt_sample = create_random_tt(count);
        vector<tt_tree*> search;
        find_by_date_tt(tt_sample, first_date);
        find_by_interval_tt(tt_sample, first_date, second_date, &search);
        search.clear();
        output_sorted_tt(tt_sample, false);
        do_some_function_tt(tt_sample, some_function);

        benchmark_23tree_file << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << "\r\n";
        cout << count << ' ' << ((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) << endl;

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) { break; }
        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec + count; }
    }
}
int main() {
    srand(time(0));

    int mode;
    cout << "For interactive mode enter 1" << endl;
    cout << "For demonstration mode enter 2" << endl;
    cout << "For benchmark mode enter 3" << endl;
    cin>>mode;

    if (mode == 1) {interactive();}
    if (mode == 2) {demonstration();}
    if (mode == 3) {benchmark();}

    return 0;
}
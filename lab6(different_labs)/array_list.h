#include <iostream>
#include <vector>
#include <algorithm>
#include "tm_functions.h"

using namespace std;

struct array_list {
    vector<tm> data;
};

array_list* create_arr_empty() {
    array_list* new_list;
    new_list = new array_list;
    return new_list;
}

void add_to_arr_list (array_list** list, tm insert_value) {
    if (*list == nullptr) {*list = create_arr_empty();}
    (*list)->data.push_back(insert_value);
}

void delete_arr_element (array_list* list, tm value_to_delete) {
    for (int i = 0; i < list->data.size(); i++) {
        if (list->data[i] == value_to_delete) {
            list->data.erase(list->data.begin()+i);
            i--;
        }
    }
}

vector<tm*> find_by_date_arr (array_list* list, tm date) {
    vector<tm*> result;
    for (int i = 0; i < list->data.size(); i++) {
        if (list->data[i] == date) {
            result.push_back(&list->data[i]);
        }
    }
    return result;
}

vector<tm*> find_by_interval_arr(array_list* list, tm start_time, tm end_time) {
    vector<tm*> result;
    for (int i = 0; i < list->data.size(); i++) {
        if (list->data[i] > start_time && list->data[i] < end_time) {
            result.push_back(&list->data[i]);
        }
    }
    return result;
}

array_list* create_random_arr_list (int element_amount) {
    array_list* list;
    if (element_amount<1) {return nullptr;}
    list = create_arr_empty();

    for (int i = 0; i < element_amount; i++) {
        add_to_arr_list(&list, random_time());
    }
    return list;
}

void sort_arr_list (array_list* list, bool print = true) {
    sort (list->data.begin(), list->data.end(), [](tm left, tm right){return left < right;});
    if (print) {
        for (int i = 0; i < list->data.size(); i++) {
            cout << list->data[i] << "     ";
        }
        cout << endl;
    }
}

void output_arr_list (array_list* list) {
    for (int i = 0; i < list->data.size(); i++) {
        cout<<list->data[i]<<"     ";
    }
    cout<<endl;
}

void do_some_function_arr(array_list* list, tm (*f)(tm)) {
    if(!list) {return;}
    sort_arr_list(list, false);
    for(int i = 0; i < list->data.size(); i++) {
        list->data[i] = f(list->data[i]);
    }
}


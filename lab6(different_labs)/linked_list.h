#include<iostream>
#include<vector>
#include<algorithm>
#include "tm_functions.h"

using namespace std;

struct linked_list {
    tm data;

    linked_list* next;
};

linked_list* create_empty() {
    linked_list* new_list;
    new_list = new linked_list;
    new_list->next = nullptr;
    new_list->data.tm_year = -1;
    return new_list;
}

void add_to_list (linked_list** first, tm add_data) {
    linked_list *new_element, *curr;

    if (*first == nullptr) {*first = create_empty();}
    new_element = new linked_list;
    new_element->data = add_data;
    new_element->next = nullptr;

    if ((*first)->data.tm_year == -1) {
        (*first)->data = add_data;
        return;
    }
    (curr) = *first;
    while ((curr) != nullptr) {
        if ((curr)->next == nullptr) {
            (curr)->next = new_element;
            return;
        }
        (curr) = (curr)->next;
    }
}

void delete_element (linked_list** first, tm value_to_delete) {
    linked_list *curr;
    linked_list* to_delete;
    while ((*first)->data == value_to_delete) {
        to_delete = (*first);
        *first = (*first)->next;
        delete to_delete;
    }
    curr = *first;
    while (curr) {
        if (!curr->next) {break;}
        if ((curr->next)->data == value_to_delete) {
            to_delete = (curr)->next;
            (curr)->next = (curr)->next->next;
            delete to_delete;
        } else { (curr) = (curr)->next;}
    }
}

vector<linked_list*> find_by_date (linked_list* first, tm date) {
    linked_list* curr = first;
    vector<linked_list*> result;
    while (curr) {
        if (curr->data == date) {
            result.push_back(curr);
        }
        curr = curr->next;
    }
    return result;
}

vector<linked_list*> find_by_interval(linked_list* first, tm start_time, tm end_time) {
    linked_list* curr = first;
    vector<linked_list*> matching;

    while (curr) {
        if ((curr->data >= start_time)&&(curr->data <= end_time)) matching.push_back(curr);
        curr = curr->next;
    }

    return matching;
}

linked_list* create_random_list (int element_amount) {
    linked_list *first;
    if (element_amount<1) {return nullptr;}
    first = create_empty();
    first->data = random_time();

    for (int i = 1; i < element_amount; i++) {
        add_to_list(&first, random_time());
    }
    return first;
}

void sort_list (linked_list* first, bool print = true) {
    vector<tm> all_dates;
    linked_list* curr = first;
    while (curr) {
        all_dates.push_back(curr->data);
        curr = curr->next;
    }
    sort (all_dates.begin(), all_dates.end(), [](tm left, tm right){return left < right;});
    curr = first;
    int index = 0;
    while (curr) {
        curr->data = all_dates[index];
     if (print) {
         cout<<curr->data<<"     ";
     }
        index++;
        curr = curr->next;
    }
    if (print) {cout<<endl;}
}

void output_list (linked_list* first) {
    linked_list* curr = first;
    while (curr) {
        cout<<curr->data<<"     ";
        curr = curr->next;
    }
    cout<<endl;
}

void do_some_function(linked_list* first, tm (*f)(tm)) {
    if(!first) {return;}
    sort_list(first, false);
    linked_list* curr = first;
    while (curr) {
        curr->data = f(curr->data);
        curr = curr->next;
    }
}


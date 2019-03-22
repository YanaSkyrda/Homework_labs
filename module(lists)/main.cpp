#include <iostream>
#include <vector>
#include<ctime>

using namespace std;

struct coefficients {
    int a,b,c;
    int s,n;

};

struct Set_of_values {
    vector<int> data;
    Set_of_values* next;
};

struct Cyclical {
    vector<int> data;
    int key;
    Cyclical* next;
    Cyclical* prev;
};

struct List_of_lists {
    Set_of_values* sublist;
    int value_mod_101;
    List_of_lists* next;
};

typedef Set_of_values* listp;
typedef Cyclical* clistp;
typedef List_of_lists* listlistp;

int value (vector<int>);
coefficients random_coefficients();
vector<int> fill_vector_data(coefficients);

listp add_element(listp, coefficients);
listp enqueue(listp, vector<int>);
pair<listp, vector<int>> dequeue(listp);
clistp add_element_to_cyclical (clistp, coefficients);

listlistp add_element_in_list_of_lists (listlistp, vector<int>);
listp find_by_value (listlistp, int);

void output_element(vector<int>);
void output_list (listp, bool);
void output_cyclical_list (clistp, bool) ;

clistp transformation (clistp);

void task_1();
void task_2();
void task_3();
void task_4();

int value (vector<int> data) {
    int value_result = 0;
    for (auto item : data) { value_result += item; }
    return value_result;
}

coefficients random_coefficients () {
    coefficients data;
    data.a = rand()%201-100;
    data.b = rand()%201-100;
    data.c = rand()%201-100;
    data.s = rand()%169+5;
    data.n = rand()%64+7;
    return data;
}

vector<int> fill_vector_data (coefficients coeffs) {
    vector<int> result;
    for (int x = 0; x <= coeffs.n; x++) { result.push_back((abs(coeffs.a*x*x*x - coeffs.b*x + coeffs.c))%coeffs.s); }
    return result;
};

listp add_element (listp first, coefficients coeffs) {
    listp curr_ptr = first, new_element;

    new_element = new Set_of_values;
    new_element->data = fill_vector_data(coeffs);
    new_element->next = nullptr;

    if (first == nullptr) {
        first = new_element;
        return first;
    }

    while (curr_ptr!= nullptr) {
        if (curr_ptr->next == nullptr) {
            curr_ptr->next = new_element;
            return first;
        }
        curr_ptr = curr_ptr->next;
    }
}

listp enqueue (listp first, vector<int> new_data) {
    listp curr_ptr = first, new_element;

    new_element = new Set_of_values;
    new_element->data = new_data;
    new_element->next = nullptr;

    if (first == nullptr) {
        first = new_element;
        return first;
    }

    while (curr_ptr!= nullptr) {
        if (curr_ptr->next == nullptr) {
            curr_ptr->next = new_element;
            return first;
        }
        curr_ptr = curr_ptr->next;
    }
}

pair <listp, vector<int>> dequeue (listp first) {
    pair <listp, vector<int>> return_ptr_vector;

    if (first->next == nullptr) {
        return_ptr_vector.first = nullptr;
        return_ptr_vector.second = first->data;
        delete first;
    } else {
        return_ptr_vector.first = first->next;
        return_ptr_vector.second = first->data;
        delete first;
    }
    return return_ptr_vector;
}

clistp add_element_to_cyclical (clistp start, coefficients coeffs) {
    clistp curr_ptr = start, new_element;

    new_element = new Cyclical;
    new_element->data = fill_vector_data(coeffs);
    new_element->key = value(new_element->data)%11;
    new_element->next = new_element;
    new_element->prev = new_element;

    if (start == nullptr) {
        start = new_element;
        return start;
    }

    do {
        if (curr_ptr->next == start) {
            curr_ptr->next = new_element;
            new_element->prev = curr_ptr;
            new_element->next = start;
            start->prev = new_element;
            return start;
        }
        curr_ptr = curr_ptr->next;
    } while (curr_ptr!= start);
}

listlistp add_element_in_list_of_lists (listlistp first, vector<int> new_data) {
    listlistp curr_ptr, new_list;
    listp new_element;
    bool exist = false;

    new_element = new Set_of_values;
    new_element->data = new_data;
    new_element->next = nullptr;

    if (first == nullptr) {
        new_list = new List_of_lists;
        new_list->next = nullptr;
        new_list->sublist = new_element;
        new_list->value_mod_101 = value(new_element->data)%101;
        first = new_list;
        return first;
    }

    curr_ptr = first;
    while (curr_ptr != nullptr) {
        if (curr_ptr->value_mod_101 == value(new_data)%101) {
            curr_ptr->sublist = enqueue(curr_ptr->sublist,new_data);
            exist = true;
        }
        if (curr_ptr->next == nullptr && !exist) {
            new_list = new List_of_lists;
            new_list->next = nullptr;
            new_list->sublist = new_element;
            new_list->value_mod_101 = value(new_element->data)%101;
            curr_ptr->next = new_list;
            break;
        }
        curr_ptr = curr_ptr->next;
    }
    return first;
}

listp find_by_value (listlistp first, int value) {
    listlistp curr_ptr = first;

    while (curr_ptr != nullptr) {
            if (curr_ptr->value_mod_101 == value) {
                return curr_ptr->sublist;
            }
        curr_ptr = curr_ptr->next;
    }
    cout<<"Can't find any of these value"<<endl;
    return nullptr;
}

void output_element (vector<int> element) {
    for (auto item : element) {
        cout<<item<<' ';
    }
    cout<<"value of data: "<<value(element);
}

void output_list (listp first, bool show_ptr) {
    listp curr_ptr = first;

    while (curr_ptr!= nullptr) {
        cout<<"element: ";
        for (auto item : curr_ptr->data) {
            cout<<item<<' ';
        }
        if (show_ptr) {cout<<curr_ptr;}
        cout<<endl;
        curr_ptr = curr_ptr->next;
    }
    cout<<endl;
}

void output_cyclical_list (clistp start, bool show_ptr) {
    clistp curr_ptr = start;

    if (start == nullptr) {return;}
    do {
        cout<<"element: ";
        for (auto item : curr_ptr->data) {
            cout<<item<<' ';
        }
        if (show_ptr) {cout<<curr_ptr;}
        cout<<endl;
        curr_ptr = curr_ptr->next;
    } while (curr_ptr!=start);
    cout<<endl;
}

clistp transformation (clistp start) {
    clistp curr_ptr = start->next, deleting, new_ptr, ptr_for_adding;
    int deleted_amount = 0, sequence_amount = 1, amount_of_elements = 1, passages = 0;

    while (curr_ptr != start) {
        amount_of_elements++;
        curr_ptr = curr_ptr->next;
    }

    while (deleted_amount <= 1327) {
        passages++;
        if ((abs(curr_ptr->key - (curr_ptr->next)->key) <= 1) || abs(curr_ptr->key - (curr_ptr->prev)->key) <= 1) {
            passages = 0;
            if ((abs(curr_ptr->key - (curr_ptr->next)->key) <= 1) && abs(curr_ptr->key - (curr_ptr->prev)->key) <= 1) {
                while ((abs(curr_ptr->key - (curr_ptr->next)->key) <= 1) && (abs(curr_ptr->key - (curr_ptr->prev)->key) <= 1)
                || (abs(curr_ptr->key - (curr_ptr->prev)->key) <= 1)) {
                    curr_ptr = curr_ptr->prev;
                }
            }
            while (abs(curr_ptr->key - (curr_ptr->next)->key) <= 1) {
                sequence_amount++;
                curr_ptr = curr_ptr->next;
            }
            curr_ptr = curr_ptr->next;
            for (int i = sequence_amount; i > 0; i--) {
                deleting = curr_ptr->prev;
                (curr_ptr->prev) = deleting->prev;
                (deleting->prev)->next = curr_ptr;
                delete deleting;
            }

            ptr_for_adding = curr_ptr;
            for (int i = 0; i < (sequence_amount - sequence_amount % 3) / 3; i++) {
                new_ptr = new Cyclical;
                new_ptr->data = fill_vector_data(random_coefficients());
                new_ptr->key = value((new_ptr->data)) % 11;
                new_ptr->next = ptr_for_adding;
                new_ptr->prev = ptr_for_adding->prev;
                ptr_for_adding->prev = new_ptr;

                ptr_for_adding = ptr_for_adding->prev;
            }
            deleted_amount += sequence_amount;
            amount_of_elements = amount_of_elements - sequence_amount + (sequence_amount - sequence_amount % 3) / 3;
            sequence_amount = 1;
            cout<<"changed:"<<endl;
            output_cyclical_list(curr_ptr, false);
        }
        if (passages > amount_of_elements) {break;}
        curr_ptr = curr_ptr->next;
    }
    return curr_ptr;
}

void task_1() {
    listp list = nullptr;
    int amount;

    amount = rand()%5+2;

    for (int i =0; i<amount; i++) {
        list = add_element(list, random_coefficients());
    }

    output_list(list, true);
    output_element(list->data);
    cout<<endl<<endl;

}

void task_2() {
    listp list = nullptr;
    clistp cyclical_list = nullptr;
    int amount;

    amount = rand()%30+1;
    for (int i =0; i<amount; i++) {
        cyclical_list = add_element_to_cyclical(cyclical_list, random_coefficients());
    }
    output_cyclical_list(cyclical_list, false);
    cyclical_list = transformation(cyclical_list);
    cout<<"result:"<<endl;
    output_cyclical_list(cyclical_list, false);
}

void task_3 () {
    listp list = nullptr, queue = nullptr, deleting;
    pair <listp, vector<int>> dequeue_result;
    vector<int> random_data, added_data;

    for (int i = 0 ; i< 100; i++) { list = add_element(list, random_coefficients()); }

    for (int i = 0; i<25; i++) {
        deleting = list;
        list = deleting->next;
        queue = enqueue(queue, deleting->data);
        delete deleting;
    }
    cout<<"current list:"<<endl;
    output_list(list, false);
    cout<<"current queue:"<<endl;
    output_list(queue, false);

    for (int i = 25; i<100; i++) {
        dequeue_result = dequeue(queue);
        queue = dequeue_result.first;
        random_data = fill_vector_data(random_coefficients());
        if ((value(list->data)%4 == value(dequeue_result.second)%4) && (value(list->data)%4!=value(random_data)%4)) {
            added_data = random_data;
        } else if ((value(list->data)%4 == value(random_data)%4) && (value(list->data)%4!=value(dequeue_result.second)%4)) {
            added_data = dequeue_result.second;
        } else if ((value(random_data)%4 == value(dequeue_result.second)%4) && (value(list->data)%4!=value(random_data)%4)) {
            added_data = list->data;
        } else {added_data = fill_vector_data(random_coefficients());}
        queue = enqueue(queue, added_data);
        cout<<"Using values (list, queue, random): "<<endl;
        output_element(list->data);
        cout<<endl;
        output_element(dequeue_result.second);
        cout<<endl;
        output_element(random_data);
        cout<<endl;
        cout<<"Added to queue: ";
        output_element(added_data);
        cout<<endl;

        if (i%10 == 4) {
            cout<<"current list: "<<endl;
            output_list(list, false);
            cout<<"current queue: "<<endl;
            output_list(queue, false);
        }
        deleting = list;
        list = deleting->next;
        delete deleting;
    }

    cout<<"current list: "<<endl;
    output_list(list, false);
    cout<<"current queue: "<<endl;
    output_list(queue, false);
}

void task_4 () {
    int amount, val;
    listlistp list_of_lists = nullptr;

    amount = rand()%50+1000;
    val = rand()%101;
    for(int i=0; i<amount; i++) {
        list_of_lists = add_element_in_list_of_lists(list_of_lists, fill_vector_data(random_coefficients()));
    }
    cout<<"Elements with value mod 101 = "<<val<<": "<<endl;
    output_list(find_by_value(list_of_lists, val), false);
}

int main() {
    srand(time(0));
    cout<<"task 1:"<<endl;
    task_1();
    cout<<"task 2:"<<endl;
    task_2();
    cout<<"task 3:"<<endl;
    task_3();
    cout<<"task 4:"<<endl;
    task_4();

    return 0;
}
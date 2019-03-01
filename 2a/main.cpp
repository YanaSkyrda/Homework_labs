#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Windows.h"
#include <fstream>
using namespace std;

struct date {
    int day, month, year;
};

struct Queue {
    date element;
    Queue* next;
};

typedef Queue* List_ptr;

ostream& operator<< (ostream& stream, date& dt) {
    string curr_day="",curr_month="";
    if (dt.day<10) curr_day='0';
    if (dt.month <10) curr_month='0';
    stream<<curr_day<<dt.day<<'.'<<curr_month<<dt.month<<'.'<<dt.year;
    return stream;
}

istream& operator>> (istream& stream, date& dt) {
    int curr_day,curr_month,curr_year;
    stream>>curr_day>>curr_month>>curr_year;
    dt.day = curr_day;
    dt.month = curr_month;
    dt.year = curr_year;
    return stream;
}

List_ptr create_empty_list();
bool list_is_empty(List_ptr);
void enqueue_list(List_ptr, date);
pair <List_ptr,date> dequeue_list(List_ptr);
void output_list(List_ptr);

void create_empty_array(date[], int);
bool array_is_empty(date[]);
void enqueue_array(date[],date, int);
date dequeue_array(date[], int);
void output_array(date[], int);

pair<vector<date>, date> dequeue_vector(vector<date>);
void output_vector(vector<date>);

date random_date();

void choose_menu_option();
void array_menu(date[]);
void vector_menu(vector<date>);
void list_menu(List_ptr);

bool Interactive_mode();
void Demonstration_mode();
void Benchmark_mode();

List_ptr create_empty_list() {
   Queue* first_date;
    first_date = new Queue;
    first_date->element.year = -1;
    first_date->next = nullptr;
    return first_date;
}

bool list_is_empty(List_ptr first_date) {
    if (first_date->element.year == -1) return true;
    return false;
}

void enqueue_list(List_ptr first_date, date new_date) {
    List_ptr curr_date, last_date = first_date;

    if (list_is_empty(first_date)) { first_date->element = new_date; }
    else {
        curr_date = new Queue;
        curr_date->element = new_date;
        curr_date->next = nullptr;

        while (last_date->next != nullptr) {last_date = last_date->next;}

        last_date->next = curr_date;
    }
}

pair <List_ptr, date> dequeue_list(List_ptr first_date) {
    pair <List_ptr, date> return_ptr_date;

    if (first_date->next == nullptr) {
        return_ptr_date.first = first_date;
        return_ptr_date.second = first_date->element;
        first_date->element.day = -1;
        first_date->element.month = -1;
        first_date->element.year = -1;
    } else {
        return_ptr_date.first = first_date->next;
        return_ptr_date.second = first_date->element;
        delete first_date;
    }

    return return_ptr_date;
}

void output_list(List_ptr first_date) {
    List_ptr curr_ptr = first_date;

    if (list_is_empty(first_date)) {
        cout<<"Queue is empty"<<endl;
        return;
    }

    do {
        cout<<curr_ptr->element<<' ';
        if (curr_ptr->next == nullptr) {break;}
        curr_ptr = curr_ptr->next;
    } while(true);
    cout<<endl;
}

void create_empty_array(date date_array[], int size) {
    for (int i=0; i<size; i++) {
        date_array[i].year = -1;
    }
}

bool array_is_empty (date date_array[]) {
    if (date_array[0].year == -1) return true;
    return false;
}

void enqueue_array (date date_array[], date new_date, int size) {

    if (date_array[size-1].year != -1) { cout<<"You went beyond the array, can not add new item"<<endl; }
    if (array_is_empty(date_array)) {
        date_array[0] = new_date;
        return;
    }

    for (int i=0; i<size; i++) {
        if (date_array[i].year == -1) {
            date_array[i] = new_date;
            return;
        }
    }
}

date dequeue_array(date date_array[], int size) {
    date return_date;

    return_date = date_array[0];
    for(int i=1; i<size; i++) {
        date_array[i-1] = date_array[i];
        if (date_array[i].year == -1) {
            return return_date;
        }
    }
    date_array[size-1].year = -1;
    date_array[size-1].month = -1;
    date_array[size-1].day = -1;
    return return_date;
}

void output_array (date date_array[], int size) {
    if (array_is_empty(date_array)) {
        cout<<"Queue is empty"<<endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        if (date_array[i].year == -1) break;
        cout<<date_array[i]<<' ';
    }
    cout<<endl;
}

pair<vector<date>, date> dequeue_vector(vector<date> curr_vector) {
    pair <vector<date>, date> return_vect_date;

    return_vect_date.second = curr_vector[0];
    curr_vector.erase(curr_vector.begin());
    return_vect_date.first = curr_vector;

    return return_vect_date;
}

void output_vector (vector<date> curr_vector) {
    if (curr_vector.empty()) {
        cout<<"Queue is empty"<<endl;
        return;
    }
    for (auto item : curr_vector) {cout<<item<<' ';}
    cout<<endl;
}

date random_date() {
    date dt;

    dt.year = rand()%400+1856;
    dt.month = 1+rand()%12;
    if (dt.month == 2) {dt.day = 1+rand()%29;}
    else if ((dt.month%2 == 1 && dt.month<8)||(dt.month%2 == 0 && dt.month>7)) {dt.day = 1+rand()%31;}
    else {dt.day = 1+rand()%30;}

    return dt;
};

void choose_menu_option() {
    cout << "Сreate new empty queue - enter 1" << endl;
    cout << "Enqueue - enter 2" << endl;
    cout << "Dequeue - enter 3" << endl;
    cout << "Output queue - enter 4" <<endl;
    cout << "Check if queue is empty - enter 5" << endl;
    cout << "Back in main menu - enter 0" << endl;
}

void array_menu (date array_of_dates[]) {
    int menu_option;
    date queue_date;

    choose_menu_option();
    cin>>menu_option;

    switch(menu_option) {
        case 1: {
            create_empty_array(array_of_dates, 20);
            array_menu(array_of_dates);
            break;
        }
        case 2: {
            cout<<"Enter date for enqueue"<<endl;
            cin>>queue_date;
            enqueue_array(array_of_dates, queue_date, 20);
            array_menu(array_of_dates);
            break;
        }
        case 3: {
            queue_date = dequeue_array(array_of_dates, 20);
            cout<<"Popped element: "<< queue_date<<endl;
            array_menu(array_of_dates);
            break;
        }
        case 4: {
            cout<<"Current queue: ";
            output_array(array_of_dates, 20);
            cout<<endl;
            array_menu(array_of_dates);
            break;
        }
        case 5: {
            cout<<"Queue is empty: ";
            if (array_is_empty(array_of_dates)) cout<<"yes"<<endl;
            else cout<<"no"<<endl;
            array_menu(array_of_dates);
            break;
        }
        case 0: {
            Interactive_mode();
            break;
        }
        default: {
            cout<<"You entered wrong number"<<endl;
            Sleep(3);
            array_menu(array_of_dates);
        }
    }
}

void vector_menu (vector<date> vector_of_dates) {
    int menu_option;
    pair<vector<date>, date> dequeue_result;
    date queue_date;

    choose_menu_option();
    cin>>menu_option;

    switch(menu_option) {
        case 1: {
            vector_menu(vector_of_dates);
            break;
        }
        case 2: {
            cout<<"Enter date for enqueue"<<endl;
            cin>>queue_date;
            vector_of_dates.push_back(queue_date);
            vector_menu(vector_of_dates);
            break;
        }
        case 3: {
            dequeue_result = dequeue_vector(vector_of_dates);
            vector_of_dates = dequeue_result.first;
            cout<<"Popped element: "<< dequeue_result.second <<endl;
            vector_menu(vector_of_dates);
            break;
        }
        case 4: {
            cout<<"Current queue: ";
            output_vector(vector_of_dates);
            vector_menu(vector_of_dates);
            break;
        }
        case 5: {
            cout<<"Queue is empty: ";
            if (vector_of_dates.empty()) {cout<<"yes"<<endl;}
            else {cout<<"no"<<endl;}
            vector_menu(vector_of_dates);
            break;
        }
        case 0: {
            Interactive_mode();
            break;
        }
        default: {
            cout<<"You entered wrong number"<<endl;
            Sleep(3);
            vector_menu(vector_of_dates);
        }
    }
}

void list_menu (List_ptr first_date) {
    int menu_option;
    pair<List_ptr, date> dequeue_result;
    date queue_date;

    choose_menu_option();
    cin>>menu_option;

    switch(menu_option) {
        case 1: {
            first_date = create_empty_list();
            list_menu(first_date);
            break;
        }
        case 2: {
            cout<<"Enter date for enqueue"<<endl;
            cin>>queue_date;
            enqueue_list(first_date, queue_date);
            list_menu(first_date);
            break;
        }
        case 3: {
            dequeue_result = dequeue_list(first_date);
            first_date = dequeue_result.first;
            cout<<"Popped element: "<< dequeue_result.second <<endl;
            list_menu(first_date);
            break;
        }
        case 4: {
            cout<<"Current queue: ";
            output_list(first_date);
            list_menu(first_date);
            break;
        }
        case 5: {
            cout<<"Queue is empty: ";
            if (list_is_empty(first_date)) cout<<"yes"<<endl;
            else cout<<"no"<<endl;
            list_menu(first_date);
            break;
        }
        case 0: {
            Interactive_mode();
            break;
        }
        default: {
            cout<<"You entered wrong number"<<endl;
            Sleep(3);
            list_menu(first_date);
        }
    }
}

bool Interactive_mode() {
    int interactive_menu_mode;
    date array_queue[20];
    vector<date> vector_queue;
    List_ptr first_date;

    cout << "Queue using array - enter 1 " << endl;
    cout << "Queue using vector - enter 2 " << endl;
    cout << "Queue using list - enter 3 "<< endl;
    cout << "Exit - enter 0" << endl;
    cin >> interactive_menu_mode;

    switch (interactive_menu_mode) {
        case 1:{
            create_empty_array(array_queue, 20);
            array_menu(array_queue);
            break;
        }
        case 2:{
            vector_menu(vector_queue);
            break;
        }
        case 3:{
            first_date = create_empty_list();
            list_menu(first_date);
            break;
        }
        case 0:{
            return true;
        }
        default: {
            cout<<"You entered wrong number"<<endl;
            Sleep(3);
            Interactive_mode();
        }
    }
}

void Demonstration_mode() {
    date array_of_dates [20], curr_date;
    vector<date> vector_of_dates;
    List_ptr list_of_dates;
    int amount_of_new = 0, curr_pos = 0;
    date array_dequeue_result;
    pair<vector<date>, date> vector_dequeue_result;
    pair<List_ptr, date> list_dequeue_result;

    cout<<"Working with array."<<endl;
    create_empty_array(array_of_dates, 20);
    amount_of_new = rand()%20+1;
    for (int i=0; i<amount_of_new; i++) { enqueue_array(array_of_dates,random_date(),20); }
    cout<<"Current queue:"<<endl;
    output_array(array_of_dates,20);

    curr_date = random_date();
    enqueue_array(array_of_dates,curr_date,20);
    cout<<"Adding "<<curr_date<<" in the queue:"<<endl;
    output_array(array_of_dates,20);

    cout<<"Deleting from queue:"<<endl;
    array_dequeue_result = dequeue_array(array_of_dates,20);
    cout<<"Current queue:"<<endl;
    output_array(array_of_dates,20);
    cout<<"Popped element: " <<array_dequeue_result<<endl;

    cout<<"Is array queue empty: ";
    if (array_is_empty(array_of_dates)) {cout<<"yes"<<endl;}
    else {cout<<"no"<<endl;}
    cout<<endl;

    cout<<"Working with vector."<<endl;

    amount_of_new = rand()%20+1;
    for (int i=0; i<amount_of_new; i++) {
       vector_of_dates.push_back(random_date());
    }
    cout<<"Current queue:"<<endl;
    output_vector(vector_of_dates);

    curr_date = random_date();
    vector_of_dates.push_back(curr_date);
    cout<<"Adding "<<curr_date<<" in the queue:"<<endl;
    output_vector(vector_of_dates);

    cout<<"Deleting from queue:"<<endl;
    vector_dequeue_result = dequeue_vector(vector_of_dates);
    vector_of_dates = vector_dequeue_result.first;
    cout<<"Current queue:"<<endl;
    output_vector(vector_of_dates);
    cout<<"Popped element: " << vector_dequeue_result.second<<endl;

    cout<<"Is vector queue empty: ";
    if (vector_of_dates.empty()) {cout<<"yes"<<endl;}
    else {cout<<"no"<<endl;}
    cout<<endl;

    cout<<"Working with lists."<<endl;
    list_of_dates = create_empty_list();
    amount_of_new = rand()%20+1;
    for (int i=0; i<amount_of_new; i++) { enqueue_list(list_of_dates, random_date()); }
    cout<<"Current queue:"<<endl;
    output_list(list_of_dates);

    curr_date = random_date();
    enqueue_list(list_of_dates,curr_date);
    cout<<"Adding "<<curr_date<<" in the queue:"<<endl;
    output_list(list_of_dates);

    cout<<"Deleting from queue:"<<endl;
    list_dequeue_result = dequeue_list(list_of_dates);
    list_of_dates = list_dequeue_result.first;
    cout<<"Current queue:"<<endl;
    output_list(list_of_dates);
    cout<<"Popped element: " << list_dequeue_result.second<<endl;

    cout<<"Is list queue empty: ";
    if (list_is_empty(list_of_dates)) {cout<<"yes"<<endl;}
    else {cout<<"no"<<endl;}

}

void Benchmark_mode() {
    date array_of_dates[100000];
    List_ptr list_of_dates;
    vector<date> vector_of_dates;
    int count_sec, count, option;
    clock_t benchmark_clock = clock();
    ofstream benchmark_results_file;

    cout<<"Do benchmark for enqueue - enter 1"<<endl;
    cout<<"Do benchmark for dequeue - enter 2"<<endl;
    cin>>option;

    switch (option) {
        case 1: {
            benchmark_results_file.open("benchmark_enqueue.txt");
            break;
        }
        case 2: {
            benchmark_results_file.open("benchmark_dequeue.txt");
            break;
        }
        default: {
            cout<<"You've entered wrong number"<<endl;
            return;
        }
    }
    benchmark_results_file<<"Results with array:"<<"\r\n";
    count = 100;
    while  (true) {
        switch (option) {
            case 1: {
                create_empty_array(array_of_dates, 100000);
                benchmark_clock = clock();
                for (int i = 0; i < count; i++) {
                    enqueue_array(array_of_dates, random_date(), 100000);
                    if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) {
                        count = i;
                        break;
                    }
                }
                break;
            }
            case 2: {
                create_empty_array(array_of_dates, 100000);
                for (int i = 0; i < count; i++) { enqueue_array(array_of_dates, random_date(), 100000); }
                benchmark_clock = clock();
                for (int i = 0; i < count; i++) {
                    dequeue_array(array_of_dates, 100000);
                    if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) { break; }
                }
                break;
            }
        }

        benchmark_results_file<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<"\r\n";
        cout<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<endl;

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) {break;}

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) < 1) {
            count = count*2;
            count_sec = count;
        }
        else {count = count_sec + count;}
    }

    benchmark_results_file<<"Results with list:"<<"\r\n";
    count = 100;
    while  (true) {
        switch (option) {
            case 1: {
                benchmark_clock = clock();
                list_of_dates = create_empty_list();
                for (int i = 0; i < count; i++) {
                    enqueue_list(list_of_dates, random_date());
                    if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) {
                        count = i;
                        break;
                    }
                }
                break;
            }
            case 2: {
                list_of_dates = create_empty_list();
                enqueue_list(list_of_dates, random_date());
                benchmark_clock = clock();
                for (int i = 0; i < count; i++) {
                    list_of_dates = dequeue_list(list_of_dates).first;
                    if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) { break; }
                    enqueue_list(list_of_dates, random_date());
                }
                break;
            }
        }

        benchmark_results_file<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<"\r\n";
        cout<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<endl;

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) >10) {break;}

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) < 1) {
            count = count*2;
            count_sec = count;
        }
        else {count = count_sec + count;}
    }

    benchmark_results_file<<"Results with vector:"<<"\r\n";
    count = 100;
    while  (true) {
        switch (option) {
            case 1: {
                benchmark_clock = clock();
                vector_of_dates.clear();
                for (int i = 0; i < count; i++) {
                    vector_of_dates.push_back(random_date());
                    if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) {
                        count = i;
                        break;
                    }
                }
                break;
            }
            case 2: {
                vector_of_dates.clear();
                for (int i = 0; i < count; i++) { vector_of_dates.push_back(random_date()); }
                benchmark_clock = clock();
                for (int i = 0; i < count; i++) {
                    vector_of_dates = dequeue_vector(vector_of_dates).first;
                    if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) { break; }
                }
                break;
            }
        }

        benchmark_results_file<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<"\r\n";
        cout<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<endl;

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) {break;}

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) < 1) {
            count = count*2;
            count_sec = count;
        }
        else {count = count_sec + count;}
    }
}

int main() {
    int mode;

    srand(time(0));
    cout << "For interactive mode enter 1" << endl;
    cout << "For demonstration mode enter 2" << endl;
    cout << "For benchmark mode enter 3" << endl;

    cin >> mode;
    switch (mode) {
       case 1: { if(Interactive_mode()) return 0; }
       case 2: {
           Demonstration_mode();
           break;
       }
       case 3: {
           Benchmark_mode();
           break;
       }
        default: cout<<"You've entered wrong number"<<endl;
    }
    return 0;
}
#include <iostream>
#include<iomanip>
#include <vector>
#include <string>
#include<algorithm>
#include <ctime>
#include<fstream>
using namespace std;

struct date_and_time {
    int date, month, hours, minutes;
};

struct popularity {
    float all_tick, tick_requests;
};

struct Train {
    int number;
    string name;
    string type;
    date_and_time arrival;
    date_and_time depature;
    popularity popular;
};

bool operator< (date_and_time left, date_and_time right) {
    if (left.month>right.month) return false;
    else if (left.month<right.month) return true;

    if (left.date>right.date) return false;
    else if (left.date<right.date) return true;

    if (left.hours>right.hours) return false;
    else if (left.hours<right.hours) return true;

    if (left.minutes>=right.minutes) return false;
    else return true;
}

bool operator != (date_and_time left, date_and_time right) {
    if (left.month != right.month) return true;
    if (left.date != right.date) return true;
    if (left.minutes != right.minutes) return true;
    if (left.hours != right.hours) return true;
    return false;
}

bool operator != (popularity left, popularity right) {
    if (left.all_tick != right.all_tick) return true;
    if (left.tick_requests != right.tick_requests) return true;
    return false;
}

bool operator != (Train left, Train right) {
    if (left.number != right.number) return true;
    if (left.name != right.name) return true;
    if (left.type != right.type) return true;
    if (left.arrival != right.arrival) return true;
    if (left.depature!= right.depature) return true;
    if (left.popular != right.popular) return true;
    return false;
}

int type_to_int (const string type){
    if (type == "international") {return 1;}
    if (type == "high-speed") {return 0;}
    if (type == "regular") {return 2;}
    if (type == "suburban") {return 3;}
}

date_and_time Random_dt () {
    date_and_time dt;

    dt.hours = rand()%24;
    dt.minutes = rand()%60;
    dt.month = 1+rand()%12;
    if (dt.month == 2) {dt.date = 1+rand()%29;}
    else if ((dt.month%2 == 1 && dt.month<8)||(dt.month%2 == 0 && dt.month>7)) {dt.date = 1+rand()%31;}
    else {dt.date = 1+rand()%30;}

    return dt;
}

popularity Random_tickets(){
    popularity tickets;

    tickets.tick_requests = 1+rand()%3000;
    tickets.all_tick = 1+rand()%1000;

    return tickets;
}

string Random_type() {
    int i = rand()%4;
    switch (i) {
        case 0: {return "international";}
        case 1: {return "high-speed";}
        case 2: {return "regular";}
        case 3: {return "suburban";}
    }
}

string Random_name(){
    int i = rand()%10;
    switch (i) {
        case 0: {return "Aberdonian";}
        case 1: {return "Armada";}
        case 2: {return "Brighton Belle";}
        case 3: {return "Cambrian Coast Express";}
        case 4: {return "Devon Express";}
        case 5: {return "Lakes Express";}
        case 6: {return "North Briton";}
        case 7: {return "North Yorkshireman";}
        case 8: {return "White Rose";}
        case 9: {return "Weymouth Wizard";}
    }
}

Train Generate_train (){
    Train new_train;
    new_train.number = 1000+rand()%9000;
    new_train.name = Random_name();
    new_train.type = Random_type();
    new_train.arrival = Random_dt();
    new_train.depature = Random_dt();
    new_train.popular = Random_tickets();
    return new_train;
}

int partition (vector<Train>& trains, int low, int high, const string sort_by) {
    int first_opened_index = low+1;

    if (sort_by == "number") {
        int pivot = trains[low].number;
        for (int i = low+1; i <= high; i++) {
            if (trains[i].number < pivot) {
                swap(trains[i], trains[first_opened_index]);
                first_opened_index++;
            }
        }
    }
    if (sort_by == "popularity") {
        float pivot = trains[low].popular.tick_requests/trains[low].popular.all_tick;
        for (int i = low+1; i <= high; i++) {
            if (trains[i].popular.tick_requests/trains[i].popular.all_tick < pivot) {
                swap(trains[i], trains[first_opened_index]);
                first_opened_index++;
            }
        }
    }
    if (sort_by == "type") {
        string pivot = trains[low].type;
        for (int i = low+1; i <= high; i++) {
            if (trains[i].type < pivot) {
                swap(trains[i], trains[first_opened_index]);
                first_opened_index++;
            }
        }
    }
    if (sort_by == "name") {
        string pivot = trains[low].name;
        for (int i = low+1; i <= high; i++) {
            if (trains[i].name < pivot) {
                swap(trains[i], trains[first_opened_index]);
                first_opened_index++;
            }
        }
    }
    if (sort_by == "arrival") {
        date_and_time pivot = trains[low].arrival;
        for (int i = low+1; i <= high; i++) {
            if (trains[i].arrival < pivot) {
                swap(trains[i], trains[first_opened_index]);
                first_opened_index++;
            }
        }
    }
    if (sort_by == "depature") {
        date_and_time pivot = trains[low].depature;
        for (int i = low+1; i <= high; i++) {
            if (trains[i].depature < pivot) {
                swap(trains[i], trains[first_opened_index]);
                first_opened_index++;
            }
        }
    }


    swap(trains[low], trains[first_opened_index-1]);
    return (first_opened_index-1);
}

void quick_sort(vector<Train>& trains, int low, int high, const string sort_by) {
    if (low < high) {
        int pivot_index = partition(trains, low, high, sort_by);

        quick_sort(trains, low, pivot_index - 1, sort_by);
        quick_sort(trains, pivot_index + 1, high, sort_by);
    }
}

void count_sort_type (vector<Train>& for_sort) {
    vector<int> count_vec;
    vector <Train> result;

    for (int i = 0; i < 4; i++) {
        count_vec.push_back(0);
    }

    for (int i = 0; i < for_sort.size(); i++) {result.push_back(Generate_train());}

    for (auto item : for_sort) { count_vec[type_to_int(item.type)]++;}

    for (int i = 1; i<4; i++) { count_vec[i] = count_vec[i]+count_vec[i-1]; }
    for (int i = 3; i>0; i--) {count_vec[i] = count_vec[i-1];}
    count_vec[0] = 0;

    for (auto item : for_sort) {
        result[count_vec[type_to_int(item.type)]] = item;
        count_vec[type_to_int(item.type)]++;
    }

    for (int i = 0; i < for_sort.size(); i++) {
        for_sort[i] = result[i];
    }
}

void count_sort_for_radix (vector<Train>& for_sort, int dig) {
    vector<int> count_vec;
    vector <Train> result;

    for (int i = 0; i < 10; i++) {
        count_vec.push_back(0);
    }

    for (int i = 0; i < for_sort.size(); i++) { result.push_back(Generate_train()); }

    for (auto item : for_sort) { count_vec[item.number % dig / (dig/10)]++; }

    for (int i = 1; i < 10; i++) { count_vec[i] = count_vec[i] + count_vec[i - 1]; }
    for (int i = 9; i > 0; i--) { count_vec[i] = count_vec[i - 1]; }
    count_vec[0] = 0;

    for (auto item : for_sort) {
        result[count_vec[item.number% dig/ (dig/10)]] = item;
        count_vec[item.number% dig/ (dig/10)]++;
    }
    for (int i = 0; i < for_sort.size(); i++) {
        for_sort[i] = result[i];
    }
}

void radix_sort_number (vector<Train>& for_sort) {
   for (int digit = 10; digit < 10001; digit = digit*10) {
       count_sort_for_radix(for_sort, digit);
   }
}

void sort_priority_quick (vector<Train>& for_sort, string prior_1, string prior_2) {
    vector<Train> before_sort = for_sort;
    quick_sort(for_sort, 0, for_sort.size()-1, prior_1);
    for (int i = 0; i < for_sort.size(); i++) {
        if (before_sort[i] != for_sort[i]) return;
    }
    quick_sort(for_sort, 0, for_sort.size()-1, prior_2);
}

void sort_priority_count (vector<Train>& for_sort, string prior_1) {
    vector<Train> before_sort = for_sort;
    if (prior_1 == "number") { radix_sort_number(for_sort);}
    else { count_sort_type(for_sort);}
    for (int i = 0; i < for_sort.size(); i++) {
        if (before_sort[i] != for_sort[i]) return;
    }
    if (prior_1 == "number") { count_sort_type(for_sort);}
    else {radix_sort_number(for_sort);}
}

void benchmark () {
    int count_sec = 100, count = 100, end = 0, limit_count = 0;
    vector<Train> trains, copied;
    double time = 0;
    clock_t benchmark_clock;
    ofstream benchmark_quicksort_type, benchmark_quicksort_number, benchmark_countsort_type, benchmark_radixsort_number,
    benchmark_priority_count, benchmark_priority_quick;
    bool sort = true;
    benchmark_quicksort_type.open("benchmark_quicksort_type.txt");
    benchmark_quicksort_number.open("benchmark_quicksort_num.txt");
    benchmark_countsort_type.open("benchmark_сountsort_type.txt");
    benchmark_radixsort_number.open("benchmark_radixsort_num.txt");
    benchmark_priority_count.open("benchmark_priority_count.txt");
    benchmark_priority_quick.open("benchmark_priority_quick.txt");

    for (int i = 0; i < 11000; i++) { trains.push_back(Generate_train());}

    while (sort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                copied.push_back(trains[j]);
            }
            benchmark_clock = clock();
            quick_sort(copied, 0, end-1, "type");
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
            copied.clear();
        }

        benchmark_quicksort_type << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {sort = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec/2 + count; }
    }

    count = 100;
    sort = true;
    while (sort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                copied.push_back(trains[j]);
            }
            benchmark_clock = clock();
            count_sort_type(copied);
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
            copied.clear();
        }

        benchmark_countsort_type << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {sort = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec/2 + count; }
    }

    count = 100;
    sort = true;
    while (sort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                copied.push_back(trains[j]);
            }
            benchmark_clock = clock();
            quick_sort(copied, 0, end-1, "number");
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
            copied.clear();
        }

        benchmark_quicksort_number << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {sort = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec/2 + count; }
    }

    count = 100;
    sort = true;
    while (sort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                copied.push_back(trains[j]);
            }
            benchmark_clock = clock();
            radix_sort_number(copied);
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
            copied.clear();
        }

        benchmark_radixsort_number << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {sort = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec/2 + count; }
    }

    count = 100;
    sort = true;
    while (sort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                copied.push_back(trains[j]);
            }
            benchmark_clock = clock();
            sort_priority_quick(copied, "number", "type");
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
            copied.clear();
        }

        benchmark_priority_quick << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {sort = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec/2 + count; }
    }

    count = 100;
    sort = true;
    while (sort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                copied.push_back(trains[j]);
            }
            benchmark_clock = clock();
            sort_priority_count(copied, "number");
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
            copied.clear();
        }

        benchmark_priority_count << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {sort = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec/2 + count; }
    }
}

int main() {
    srand(time(0));

    benchmark();
    return 0;
}
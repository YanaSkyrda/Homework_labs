#include <iostream>
#include<ctime>
#include<fstream>
#include<algorithm>

using namespace std;

ostream& operator << (ostream& stream, tm& time) {
    string day="", month="", hour="", min="", sec="";
    if (time.tm_mday<10) day='0';
    if (time.tm_mon<10) month='0';
    if (time.tm_hour<10) hour='0';
    if (time.tm_min<10) min='0';
    if (time.tm_sec<10) sec='0';
    stream<<day<<time.tm_mday<<'.'<<month<<time.tm_mon<<'.'<<time.tm_year<<' '
          <<hour<<time.tm_hour<<':'<<min<<time.tm_min<<':'<<sec<<time.tm_sec;
    return stream;
}

istream& operator >> (istream& stream, tm& time) {
    int day, month, year, hour, min, sec;
    stream>>day>>month>>year>>hour>>min>>sec;
    time.tm_mday = day;
    time.tm_mon = month;
    time.tm_year = year;
    time.tm_hour = hour;
    time.tm_min = min;
    time.tm_sec = sec;
    return stream;
}

tm random_time () {
    tm time;
    time.tm_mday = rand()%31+1;
    time.tm_mon = rand()%12+1;
    time.tm_year = rand()%21+2000;
    time.tm_hour = rand()%24;
    time.tm_min = rand()%60;
    time.tm_sec = rand()%60;
    return time;
}

bool operator< (tm& left, tm& right) {
    if (left.tm_year>right.tm_year) return false;
    else if (left.tm_year<right.tm_year) return true;

    if (left.tm_mon>right.tm_mon) return false;
    else if (left.tm_mon<right.tm_mon) return true;

    if (left.tm_mday>right.tm_mday) return false;
    else if (left.tm_mday<right.tm_mday) return true;

    if (left.tm_hour>right.tm_hour) return false;
    else if (left.tm_hour<right.tm_hour) return true;

    if (left.tm_min>right.tm_min) return false;
    else if (left.tm_min<right.tm_min) return true;

    if (left.tm_sec>=right.tm_sec) return false;
    else return true;
}

bool operator> (tm& left, tm& right) {
    if (left.tm_year>right.tm_year) return true;
    else if (left.tm_year<right.tm_year) return false;

    if (left.tm_mon>right.tm_mon) return true;
    else if (left.tm_mon<right.tm_mon) return false;

    if (left.tm_mday>right.tm_mday) return true;
    else if (left.tm_mday<right.tm_mday) return false;

    if (left.tm_hour>right.tm_hour) return true;
    else if (left.tm_hour<right.tm_hour) return false;

    if (left.tm_min>right.tm_min) return true;
    else if (left.tm_min<right.tm_min) return false;

    if (left.tm_sec>right.tm_sec) return true;
    else return false;
}

void swap_dates (tm& first, tm& second) {
    tm temp = first;
    first = second;
    second = temp;
}

void print_array (tm date_array[], int beg_index, int end_index) {
    for (int i = beg_index; i<=end_index; i++) {
        cout<<date_array[i]<<' ';
    }
    cout<<endl;
}

void selection_sort (tm date_array[], int low, int high, bool print) {
    for (int i = low; i < high; i++) {
        int index_of_min = i;
        for (int j = i + 1; j <= high; j++) {
            if (date_array[j]<date_array[index_of_min]) {index_of_min = j;}
        }
        if (index_of_min != i) {
            swap_dates(date_array[i], date_array[index_of_min]);
        }
        if (print) {print_array(date_array, low, high);}
    }
}

int partition (tm date_array[], int low, int high) {
    tm pivot = date_array[low];
    int first_opened_index = low+1;

    for (int i = low+1; i <= high; i++) {
        if (date_array[i] < pivot) {
            swap_dates(date_array[i], date_array[first_opened_index]);
            first_opened_index++;
        }
    }
    swap_dates(date_array[low], date_array[first_opened_index-1]);
    return (first_opened_index-1);
}
void quick_sort(tm array_of_dates[], int low, int high, bool print) {
    if (low < high) {
        int pivot_index = partition(array_of_dates, low, high);

        if (print) {print_array(array_of_dates, low, high);}

        quick_sort(array_of_dates, low, pivot_index - 1, print);
        quick_sort(array_of_dates, pivot_index + 1, high, print);
    }
}

void merge (tm array_of_dates[], int left, int right, int middle) {
    tm first_array[middle-left+1];
    tm second_array[right - middle];

    for (int i = 0; i < middle - left + 1; i++) {
        first_array[i] = array_of_dates [left+i];
    }
    for (int i = 0; i < right - middle; i++) {
        second_array[i] = array_of_dates [middle+i+1];
    }

    int i = 0, j = 0, k = left;
    while (i < middle - left +1 && j < right - middle) {
        if ((first_array[i] < second_array[j])||(first_array[i] < second_array[j])) {
            array_of_dates[k] = first_array[i];
            i++;
        } else {
            array_of_dates[k] = second_array[j];
            j++;
        }
        k++;
    }

    while (i < middle - left + 1) {
        array_of_dates[k] = first_array[i];
        i++; k++;
    }

    while (j < right - middle) {
        array_of_dates[k] = second_array[j];
        j++; k++;
    }
}
void merge_sort (tm array_of_dates[], int left, int right, bool print) {
    if (left < right) {
        int middle = (left + (right-1))/2;

        merge_sort(array_of_dates, left, middle, print);
        merge_sort(array_of_dates, middle+1, right, print);

        merge(array_of_dates, left, right, middle);
        if (print) {print_array(array_of_dates, left, right);}
    }
}

void combinated_sort (tm array_of_dates[], int low, int high, int limit, bool print) {

    if (low < high) {
        int pivot = partition(array_of_dates, low, high);

        if (print) {print_array(array_of_dates, low, high);}

        if ((pivot - low) <= limit) {
            selection_sort(array_of_dates, low, pivot - 1, print);
        } else {
            combinated_sort(array_of_dates, low, pivot - 1, limit, print);
        }

        if ((high - pivot) <= limit) {
            selection_sort(array_of_dates, pivot + 1, high, print);
        } else {
            combinated_sort(array_of_dates, pivot + 1, high, limit, print);
        }
    }
}

void demonstration_mode () {
    int amount_of_elements = rand()%10+20;
    tm array[amount_of_elements], for_sort[amount_of_elements];

    cout<<"Unsorted array: "<<endl;
    for (int i = 0; i < amount_of_elements; i++) {
        array[i] = random_time();
        cout<<array[i]<<' ';
        for_sort[i] = array[i];
    }
    cout<<endl;
    cout<<"Selection sort: "<<endl;
    selection_sort(for_sort, 0, amount_of_elements-1, true);
    cout<<"Result: ";
    for (int i = 0; i < amount_of_elements; i++) { cout<<for_sort[i]<<' '; }
    cout<<endl;

    for (int i = 0; i < amount_of_elements; i++) {for_sort[i] = array[i];}
    cout<<"Quick sort: "<<endl;
    quick_sort(for_sort, 0, amount_of_elements-1, true);
    cout<<"Result: ";
    for (int i = 0; i < amount_of_elements; i++) { cout<<for_sort[i]<<' '; }
    cout<<endl;

    for (int i = 0; i < amount_of_elements; i++) {for_sort[i] = array[i];}
    cout<<"Merge sort: "<<endl;
    merge_sort(for_sort, 0, amount_of_elements-1, true);
    cout<<"Result: ";
    for (int i = 0; i < amount_of_elements; i++) { cout<<for_sort[i]<<' '; }
    cout<<endl;

    for (int i = 0; i < amount_of_elements; i++) {for_sort[i] = array[i];}
    cout<<"Combinated sort: "<<endl;
    combinated_sort(for_sort, 0, amount_of_elements-1, 10, true);
    cout<<"Result: ";
    for (int i = 0; i < amount_of_elements; i++) { cout<<for_sort[i]<<' '; }
    cout<<endl;

}

void benchmark_mode() {
    int count_sec = 100, count = 100, end = 0, limit_count = 0;
    double time = 0;
    tm sorted[11000], array_of_dates[11000];
    clock_t benchmark_clock;
    ofstream benchmark_results_selection, benchmark_results_quick, benchmark_results_merge, benchmark_results_combinated, benchmark_results_library;
    bool selsort = true, qusort = true, mersort = true, combsort = true, libsort = true;
    benchmark_results_selection.open("benchmark_selection.txt");
    benchmark_results_quick.open("benchmark_quick.txt");
    benchmark_results_merge.open("benchmark_merge.txt");
    benchmark_results_combinated.open("benchmark_combinated.txt");
    benchmark_results_library.open("benchmark_library.txt");

    for (int i = 0; i < 11000; i++) { array_of_dates[i] = random_time(); }

    while (selsort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                sorted[j] = array_of_dates[j];
            }
            benchmark_clock = clock();
            selection_sort(sorted, 0, end, false);
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
            }

            benchmark_results_selection << count << ' ' <<time << "\r\n";
            cout<<count<<' '<<time<<endl;

            if (time > 10) {selsort = false;}
            if (time < 1) {
                count = count * 2;
                count_sec = count;
            } else { count = count_sec + count; }
    }

    count = 100;
    while (qusort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                sorted[j] = array_of_dates[j];
            }
            benchmark_clock = clock();
            quick_sort(sorted, 0, end, false);
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
        }

        benchmark_results_quick << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {qusort = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec + count; }
    }

    count = 100;
    while (mersort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                sorted[j] = array_of_dates[j];
            }
            benchmark_clock = clock();
            merge_sort(sorted, 0, end, false);
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
        }

        benchmark_results_merge << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {mersort = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec + count; }
    }

    count = 100;
    benchmark_results_combinated << "Limit for selection sort in combinated = 5" << "\r\n";
    while (combsort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                sorted[j] = array_of_dates[j];
            }
            benchmark_clock = clock();
            combinated_sort(sorted, 0, end, 15, false);
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
        }

        benchmark_results_combinated << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec + count; }
        if (time > 10) {
            limit_count++;
            count = 100;
            if (limit_count == 1) {
                benchmark_results_combinated << "Limit for selection sort in combinated = 15" << "\r\n";
            }
            if (limit_count == 2) {
                benchmark_results_combinated << "Limit for selection sort in combinated = 50" << "\r\n";
            }
            if (limit_count == 3) {
                benchmark_results_combinated << "Limit for selection sort in combinated = 75" << "\r\n";
            }
            if (limit_count == 4) { combsort = false;}
        }
    }

    count = 100;
    while (libsort) {
        time = 0;

        for (int i = 0; i <= count/10000; i++) {
            if (i == count/10000) {end = count%10000;}
            else {end = 10000;}
            for (int j = 0; j < end; j++) {
                sorted[j] = array_of_dates[j];
            }
            benchmark_clock = clock();
            sort(sorted, sorted+end);
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
        }

        benchmark_results_library << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {libsort = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec + count; }
    }
}

int main() {
    srand(time(0));

    demonstration_mode();
    benchmark_mode();

    return 0;
}
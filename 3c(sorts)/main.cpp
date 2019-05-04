#include <iostream>
#include <vector>
#include <algorithm>
#include<ctime>
#include<fstream>
#include <math.h>

using namespace std;

float random_float () {
    float a = rand()%10+1, b = rand()%91 + 10;
    return a/b;
}

void bucket_sort(vector<float>& for_sort, bool print) {
    vector<float> bucket[for_sort.size()];

    for (int i = 0; i < for_sort.size(); i++) {
        int bucket_index = for_sort.size()*for_sort[i];
        bucket[bucket_index].push_back(for_sort[i]);
    }
    if (print) {
        for (int i = 0; i < for_sort.size(); i++) {
            cout<<"bucket["<<i<<"] = ";
            for (int j = 0; j < bucket[i].size(); j++) {
                cout<<bucket[i][j]<<' ';
            }
            cout<<endl;
        }
        cout<<endl;
    }

    for (int i = 0; i < for_sort.size(); i++) {
        sort(bucket[i].begin(), bucket[i].end());
    }

    if (print) {
        for (int i = 0; i < for_sort.size(); i++) {
            cout<<"bucket["<<i<<"] = ";
            for (int j = 0; j < bucket[i].size(); j++) {
                cout<<bucket[i][j]<<' ';
            }
            cout<<endl;
        }
        cout<<endl;
    }

    int index = 0;
    for (int i = 0; i < for_sort.size(); i++) {
        for (int j = 0; j < bucket[i].size(); j++) {
            for_sort[index] = bucket[i][j];
            index++;
        }
    }
}

void demonstration () {
    vector<float> vec;
    int size = rand()%10+5;

    for (int i = 0; i < size; i++) {
        vec.push_back(random_float());
    }

    cout<<"Unsorted: "<<endl;
    for (int i=0; i<vec.size(); i++) {
        cout << vec[i] << ' ';
    }
    cout<<endl;

    bucket_sort(vec, true);
    cout<<"Sorted: "<<endl;
    for (int i=0; i<vec.size(); i++) {
        cout << vec[i] << ' ';
    }

}

void benchmark () {
    int count_sec = 100, count = 100, end = 0;
    vector<float> vec, copied;
    double time = 0;
    clock_t benchmark_clock;
    ofstream benchmark_library, benchmark_bucket;
    bool not_sorted = true;
    benchmark_library.open("benchmark_library_sort.txt");
    benchmark_bucket.open("benchmark_bucket_sort.txt");

    for (int i = 0; i < 1100; i++) { vec.push_back(random_float());}

    while (not_sorted) {
        time = 0;

        for (int i = 0; i <= count/1000; i++) {
            if (i == count/1000) {end = count%1000;}
            else {end = 1000;}
            for (int j = 0; j < end; j++) {
                copied.push_back(vec[j]);
            }
            benchmark_clock = clock();
            bucket_sort(copied, false);
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
            copied.clear();
        }

        benchmark_bucket << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {not_sorted = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec + count; }
    }

    count = 100;
    not_sorted = true;
    while (not_sorted) {
        time = 0;

        for (int i = 0; i <= count/1000; i++) {
            if (i == count/1000) {end = count%1000;}
            else {end = 1000;}
            for (int j = 0; j < end; j++) {
                copied.push_back(vec[j]);
            }
            benchmark_clock = clock();
            sort(copied.begin(), copied.end());
            time = time + (double) (clock() - benchmark_clock) / CLOCKS_PER_SEC;
            copied.clear();
        }

        benchmark_library << count << ' ' <<time << "\r\n";
        cout<<count<<' '<<time<<endl;

        if (time > 10) {not_sorted = false;}
        if (time < 1) {
            count = count * 2;
            count_sec = count;
        } else { count = count_sec + count; }
    }
}

int main() {
    srand(time(0));
    //demonstration();
    benchmark();
    return 0;
}
#include <iostream>

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

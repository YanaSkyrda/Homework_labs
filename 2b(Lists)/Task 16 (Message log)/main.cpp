#include <iostream>
#include<string>
#include<ctime>
#include<windows.h>

using namespace std;

struct  message_log {
    string text;
    tm sent_time;
    int amount;
    message_log* next;
    message_log* prev;
};

typedef message_log* msg_ptr;

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

tm random_time();
string random_text();
msg_ptr create_empty_log();
msg_ptr add_message (msg_ptr,string,tm,int);
void show_last (msg_ptr, int);
void demonstration_mode();
void interactive_mode();


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

string random_text () {
    string text = "";
    char ascii_ch;
    int text_size = rand()%18+3;
    for (int i = 0; i<text_size; i++) {
        ascii_ch = rand()%26+97;
        text += ascii_ch;
    }
    return text;
}

msg_ptr create_empty_log () {
    msg_ptr new_msg;
    new_msg = new message_log;
    new_msg->next = new_msg;
    new_msg->prev = new_msg;
    new_msg->amount = 0;

    return new_msg;
}

msg_ptr add_message (msg_ptr last_message, string msg_text, tm msg_time, int log_size) {
    msg_ptr new_msg;
    if (last_message->amount < log_size) {
        if (last_message->amount == 0) { new_msg = last_message; }
        else { new_msg = new message_log; }
        new_msg->text = msg_text;
        new_msg->sent_time = msg_time;
        new_msg->amount = last_message->amount+1;
        new_msg->next = last_message->next;
        new_msg->prev = last_message;
        (last_message->next)->prev = new_msg;
        last_message->next = new_msg;
        return new_msg;
    } else {
        (last_message->next)->text = msg_text;
        (last_message->next)->sent_time = msg_time;
        (last_message->next)->amount = log_size;
        return last_message->next;
    }
}

void show_last (msg_ptr last_message, int amount) {
    msg_ptr curr_msg = last_message;
    for (int i = amount; i > 1; i--) { curr_msg = curr_msg->prev; }
    for (int i = amount; i > 0; i--) {
        cout<<curr_msg->text<<' '<<curr_msg->sent_time<<endl;
        curr_msg = curr_msg->next;
    }
}

void demonstration_mode() {
    msg_ptr message_log;
    int amount_of_messages = 0, size = 0;

    message_log = create_empty_log();
    amount_of_messages = rand()%9+1;
    size = rand()%6+5;
    cout<<"Creating empty log with size "<<size<<" and add "<<amount_of_messages<<" new elements:"<<endl;
    Sleep(3);
    for (int i = 0; i<amount_of_messages; i++) {
        message_log = add_message(message_log, random_text(), random_time(), size);
    }
    show_last(message_log, amount_of_messages);

    cout<<"Fill log to the maximum amount";
    for (int i = amount_of_messages; i < size; i++) {
        message_log = add_message(message_log, random_text(), random_time(), size);
    }
    amount_of_messages = rand()%4+1;
    for (int i = 0; i < amount_of_messages; i++) {
        message_log = add_message(message_log, random_text(), random_time(), size);
    }
    cout<<" and add "<< amount_of_messages<<" new messages:"<<endl;
    Sleep(3);
    show_last(message_log, size);

    amount_of_messages = rand()%4+1;
    cout<<"Show last "<<amount_of_messages<<" mesaages:"<<endl;
    show_last(message_log, amount_of_messages);
}

void interactive_mode() {
    int operation = 0, size = 5, amount;
    msg_ptr message_log = create_empty_log();
    string message;
    tm time;

    do {
        cout << "Create new log - enter 1" << endl;
        cout << "Add new message in log - enter 2" << endl;
        cout << "Show last messages - enter 3" << endl;
        cout << "In main menu - enter 0" << endl;
        cin >> operation;

        switch (operation) {
            case 1: {
                message_log = create_empty_log();
                cout << "Enter size of log" << endl;
                cin >> size;
                break;
            }
            case 2: {
                cout << "Enter new message" << endl;
                cin >> message;
                cout << "Enter time of new message (DDxMMxYYYY HH:mm:ss)" << endl;
                cin >> time;
                message_log = add_message(message_log, message, time, size);
                break;
            }
            case 3: {
                cout << "Enter amount of messages you want to see" << endl;
                cin >> amount;
                show_last(message_log, amount);
                break;
            }
            case 0: {
                break;
            }
            default: {
                cout << "You've entered wrong number" << endl;
                break;
            }
        }
    } while (operation!=0);
}

int main() {
    int mode;
    srand(time(0));

    main_menu:
    cout<<"For demonstration mode - enter 1"<<endl;
    cout<<"For interactive mode - enter 2"<<endl;
    cout<<"For exit - enter 0"<<endl;
    cin>>mode;

    switch (mode) {
        case 1: {
            demonstration_mode();
            cout<<endl;
            goto main_menu;
        }
        case 2: {
            interactive_mode();
            cout<<endl;
            goto main_menu;
        }
        case 0: {
            break;
        }
        default: {
            cout<<"You've entered wrong number"<<endl;
            cout<<endl;
            goto main_menu;
        }
    }

    return 0;
}
#include <iostream>
#include<vector>
#include<ctime>
#include<windows.h>

using namespace std;

struct list_of_sets {
    vector<int> set;
    int index;
    list_of_sets* next;
};

typedef list_of_sets* sets_ptr;

sets_ptr create_empty ();
void add_set (sets_ptr, vector<int>);
void output_list (sets_ptr);
vector<int> sets_union (sets_ptr, int, int);
vector<int> sets_intersection (sets_ptr, int, int);
vector<int> set_complementary (sets_ptr, int, int, int);
vector<int> random_set (int, int);
void interactive_mode();
void demonstration_mode();

sets_ptr create_empty() {
    sets_ptr new_list;
    new_list = new list_of_sets;
    new_list->next = nullptr;
    new_list->index = -1;
    return new_list;
}
void add_set (sets_ptr first_set, vector<int> added_set) {
    sets_ptr curr_set = first_set, new_set;
    if (first_set->index == -1) {
        first_set->set = added_set;
        first_set->index = 0;
        return;
    }
    do {
        if (curr_set -> next == nullptr) {
            new_set = new list_of_sets;
            new_set->set = added_set;
            new_set->index = (curr_set->index)+1;
            new_set->next = nullptr;
            curr_set->next = new_set;
            break;
        }
        curr_set = curr_set->next;
    } while(true);
}
void output_list (sets_ptr first_set) {
    sets_ptr curr_set = first_set;
    do {
        cout<<"Set "<<curr_set->index<<": ";
        for (auto item : curr_set->set) {
            cout<<item<<' ';
        }
        cout<<endl;
        if (curr_set->next == nullptr) {break;}
        curr_set = curr_set->next;
    } while (true);
}
vector<int> sets_union (sets_ptr first_set, int first_index, int second_index) {
    sets_ptr curr_ptr = first_set;
    vector<int> first, second, result;
    bool already_in_set = false;
    do {
        if (curr_ptr->index == first_index) {first = curr_ptr->set;}
        if (curr_ptr->index == second_index) {second = curr_ptr->set;}

        if (curr_ptr->next == nullptr) {break;}
        curr_ptr = curr_ptr->next;
    } while (true);

    for (auto item : first) {
        result.push_back(item);
    }

    for (auto item : second) {
        for (auto res_item : result) {
            if (res_item == item) {
                already_in_set = true;
                break;
            }
        }
        if (!already_in_set) {result.push_back(item);}
        already_in_set = false;
    }

    return result;
}
vector<int> sets_intersection (sets_ptr first_set, int first_index, int second_index) {
    sets_ptr curr_ptr = first_set;
    vector<int> first, second, result;
    bool already_in_set = false;
    do {
        if (curr_ptr->index == first_index) {first = curr_ptr->set;}
        if (curr_ptr->index == second_index) {second = curr_ptr->set;}

        if (curr_ptr->next == nullptr) {break;}
        curr_ptr = curr_ptr->next;
    } while (true);

    for (auto fitem : first) {
        for (auto sitem : second) {
            if (fitem == sitem) {result.push_back(fitem);}
        }
    }

    return result;
}
vector<int> set_complementary (sets_ptr first_set, int set_index, int universal_start, int universal_end) {
    sets_ptr curr_ptr = first_set;
    vector<int> original_set, complement_set;
    bool in_original_set = false;

    do {
        if (curr_ptr->index == set_index) {
            original_set = curr_ptr->set;
            break;
        }
        if (curr_ptr->next == nullptr) {break;}
        curr_ptr = curr_ptr->next;
    } while (true);

    for (int i = universal_start; i <= universal_end; i++) {
        for (auto item : original_set) {
            if (item == i) {
                in_original_set = true;
                break;
            }
        }
        if (!in_original_set) {complement_set.push_back(i);}
        in_original_set = false;
    }

    return complement_set;
}
vector<int> random_set(int universal_start, int universal_end) {
    vector<int> result;
    vector <pair<int, bool>> universal_set;
    int amount_of_elements, index;

    amount_of_elements = rand()%(universal_end - universal_start + 2);
    for (int i = universal_start; i<=universal_end; i++) { universal_set.push_back(make_pair(i, false));}
    for (int i=0; i<amount_of_elements; i++) {
        do {
            index = rand()%(universal_end - universal_start + 1);
        }
        while (universal_set[index].second);
        result.push_back(universal_set[index].first);
        universal_set[index].second = true;
    }

    return result;
}
void interactive_mode() {
    int amount_of_sets, universal_set_start = 0, universal_set_end = 0, first_index_set, second_index_set, operation;
    sets_ptr list_sets = create_empty();
    vector<int> results;

    do {
        cout << "Generate new list of sets - enter 1" << endl;
        cout << "Find union of sets - enter 2" << endl;
        cout << "Find intersection of sets  - enter 3" << endl;
        cout << "Find complementary to the set  - enter 4" << endl;
        cout << "Output list of sets - enter 5"<<endl;
        cout << "In main menu - enter 0" << endl;
        cin >> operation;

        switch (operation) {
            case 1: {
                list_sets = create_empty();
                cout<<"Enter limits for universal set"<<endl;
                cin>>universal_set_start>>universal_set_end;
                cout<<"Set amount of sets in list"<<endl;
                cin>>amount_of_sets;
                for (int i = 0; i < amount_of_sets; i++) {
                    add_set(list_sets, random_set(universal_set_start, universal_set_end));
                }
                break;
            }
            case 2: {
                cout<<"Enter indexes of sets"<<endl;
                cin>>first_index_set>>second_index_set;
                cout<<"Union of set "<<first_index_set<<" and "<<second_index_set<<": ";
                results = sets_union(list_sets, first_index_set, second_index_set);
                for (auto item : results) {cout<<item<<' ';}
                cout<<endl;
                break;
            }
            case 3: {
                cout<<"Enter indexes of sets"<<endl;
                cin>>first_index_set>>second_index_set;
                cout<<"Intersection of set "<<first_index_set<<" and "<<second_index_set<<": ";
                results = sets_intersection(list_sets, first_index_set, second_index_set);
                for (auto item : results) {cout<<item<<' ';}
                cout<<endl;
                break;
            }
            case 4: {
                cout<<"Enter index of set"<<endl;
                cin>>first_index_set;
                cout<<"Complementary to set "<<first_index_set<<": ";
                results = set_complementary(list_sets, first_index_set, universal_set_start, universal_set_end);
                for (auto item : results) {cout<<item<<' ';}
                cout<<endl;
                break;
            }
            case 5: {
                output_list(list_sets);
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
void demonstration_mode() {
    int amount_of_sets, universal_set_start, universal_set_end, first_index_set, second_index_set;
    sets_ptr list_sets = create_empty();
    vector<int> results;

    cout<<"Creating list of sets..."<<endl;
    universal_set_start = rand()%20-10;
    universal_set_end = rand()%20+10;
    amount_of_sets = rand()%10+2;
    for (int i = 0; i < amount_of_sets; i++) {
        add_set(list_sets, random_set(universal_set_start, universal_set_end));
    }
    cout<<"Universal set from "<<universal_set_start<<" to "<<universal_set_end<<endl;
    output_list(list_sets);

    first_index_set = rand()%amount_of_sets;
    second_index_set = rand()%amount_of_sets;
    cout<<"Union of set "<<first_index_set<<" and "<<second_index_set<<": ";
    results = sets_union(list_sets, first_index_set, second_index_set);
    for (auto item : results) {cout<<item<<' ';}
    cout<<endl;

    first_index_set = rand()%amount_of_sets;
    second_index_set = rand()%amount_of_sets;
    cout<<"Intersection of set "<<first_index_set<<" and "<<second_index_set<<": ";
    results = sets_intersection(list_sets, first_index_set, second_index_set);
    for (auto item : results) {cout<<item<<' ';}
    cout<<endl;

    first_index_set = rand()%amount_of_sets;
    cout<<"Complementary to set "<<first_index_set<<": ";
    results = set_complementary(list_sets, first_index_set, universal_set_start, universal_set_end);
    for (auto item : results) {cout<<item<<' ';}
    cout<<endl;
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
#include <iostream>
#include <string>
#include "table.h"


using namespace std;

// params
bool max_param = false;
bool level_param = false;
bool show_only_table = false;


int max_value, random_value;
const int levels[3] = {10, 50, 100};
string name;
int attempts;
int guess;


// initializing params
void init(int argc, char* argv[]) {
    if (argc > 1) {
        for(int i = 0; i < argc; ++i) {
            string arg_value{ argv[i] };
            if (arg_value == "-table") {
                show_only_table = true;
                show_table();
                exit(0);
                
            } else if (arg_value == "-max") {
                max_param = true;
                max_value = stoi(argv[i+1]);

            } else if (arg_value == "-level") {
                level_param = true;
                max_value = levels[stoi(argv[i+1])-1];
            }
        }

    } else {
        max_value = 100;
        random_value = rand() % max_value;
    }

    random_value = rand() % max_value;
}



// main func
int main(int argc, char* argv[]) {
    srand(time(nullptr));
    init(argc, argv);

    if (max_param == true && level_param == true) {
        cout << "You cant use both -max and -level parameters while using a programm" << endl;
        exit(-1);
    }

    
    cout << "Settings\n\nparams:\n-max = " << max_param << "\n-level = " << level_param << "\n-table = " << show_only_table << "\n\nmax_value = " << max_value << endl;
    cout << "\nHi! Enter your name, please: ";
    cin >> name;

    do {
        cout << "\n" << name << ", enter your guess: ";
        cin >> guess;
        attempts++;
        if (random_value > guess) {
            cout << "greater than " << guess << endl << endl;
        } else if (random_value < guess) {
            cout << "less than " << guess << endl << endl;
        } else if (random_value == guess) {
            cout << "you win! attempts = " << attempts << endl << endl;
            break;
        }
    } while(guess != random_value);
        
    edit_table(name, attempts);
    show_table();

    return 0;
}
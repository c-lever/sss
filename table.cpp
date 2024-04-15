#include <string>
#include <iostream>
#include <fstream>
#include "table.h"

using namespace std;


void show_table() {
    string username;
    int high_score = 0;

    ifstream highscores_file("high_scores.txt");

    if (!highscores_file.is_open()) {
        cout << "Error! File does not exist" << endl;
        return;
    }

    cout << "High scores table:\n";
    while (true) {
        highscores_file >> username;
        highscores_file >> high_score;
        highscores_file.ignore();
        if (highscores_file.fail()) {
            break;
        }
        cout << username << '\t' << high_score << endl;
    }



};

void edit_table(string& name, int& attempts) {
    ofstream temp_file("temp_high_scores.txt");
    ifstream highscores_file("high_scores.txt");
    
    
    string line_name;
    int line_attempts;
    bool line_attempts_new_record;
    bool found_name = false;

    while (highscores_file >> line_name >> line_attempts) {
        if (line_name == name) {
            found_name = true;
            if (line_attempts > attempts) {
                line_attempts_new_record = true;
                continue;
            }
        }

        temp_file << line_name << " " << line_attempts << endl;
    }

    if (!found_name || line_attempts_new_record) {
        temp_file << name << " " << attempts << endl;
    }

    highscores_file.close();
    temp_file.close();

    remove("high_scores.txt");
    rename("temp_high_scores.txt", "high_scores.txt");

};
#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <limits>
#include <windows.h> // For enabling ANSI colors
#include "skiplist_impl.h" // Your skip list header

using namespace std;

// ANSI color definitions
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif


void enableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void interactiveSkipListString() {
    enableANSIColors();

    SkipList<string> list(15, 0.7f);  // Customize max size and probability

    char displayTimes;
    cout << BOLD << CYAN << "Display operation times? (Y/N): " << RESET;
    cin >> displayTimes;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << YELLOW << "\n--- Skip List Operations Menu ---\n"
         << "1. Insert\n2. Search\n3. Delete\n4. Traverse\n-1. Exit\n" << RESET;

    while (true) {
        string line;
        cout << CYAN << "\nCommand: " << RESET;
        getline(cin, line);

        stringstream ss(line);
        int command;
        string leftover; 
        if (!(ss >> command)  || (ss >> leftover)) {
            cout << RED << "Invalid input. Please enter a number.\n" << RESET;
            continue;
        }

        if (command == -1) {
            cout << GREEN << "Exiting...\n" << RESET;
            break;
        }

        chrono::high_resolution_clock::time_point start, end;

        if (command == 1) {
            cout << "Enter string to insert: ";
            string str;
            getline(cin, str);
            start = chrono::high_resolution_clock::now();
            if (list.insert(str))
                cout << GREEN << "Inserted '" << str << "'into skip list.\n" << RESET;
            else
                cout << RED << "Duplicate! '" << str << "' already exists.\n" << RESET;

            end = chrono::high_resolution_clock::now();
            

        } else if (command == 2) {
            cout << "Enter string to search: ";
            string str;
            getline(cin, str);
            start = chrono::high_resolution_clock::now();
            bool found = list.search(str);
            end = chrono::high_resolution_clock::now();
            cout << (found ? GREEN "Found!" : RED "Not Found.") << RESET << endl;

        } else if (command == 3) {
            cout << "Enter string to delete: ";
            string str;
            getline(cin, str);
            start = chrono::high_resolution_clock::now();
            bool removed = list.remove(str);
            end = chrono::high_resolution_clock::now();
            cout << (removed ? GREEN "Deleted successfully." : RED "Not found.") << RESET << endl;

        } else if (command == 4) {
            start = chrono::high_resolution_clock::now();
            cout << YELLOW << "\n--- Skip List Contents ---\n" << RESET;
            list.display();
            end = chrono::high_resolution_clock::now();

        } else {
            cout << RED << "Invalid command. Try again.\n" << RESET;
            continue;
        }

        if (displayTimes == 'Y' || displayTimes == 'y') {
            auto diff = chrono::duration_cast<chrono::microseconds>(end - start);
            cout << CYAN << "Time taken: " << diff.count() << " microseconds.\n" << RESET;
        }
    }
}
int main() {
    interactiveSkipListString();
    return 0;
}
// Name: Aaryan Sharma
// CS 251 (Fall 2023) - Prof Drishika Dey
// Project - 1 (Library Management System)




#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;


struct Lib {
    string isbn = "000-0-00-000000-0";
    string title = "";
    int status = 0;
};


// Function prototypes for all the glorious function decomposition
void printMenu ();
void seperateVal (string delim, string data_line, vector<string>& vec);
bool isbnCheck (string isbn);
void displayEntry (vector<string> entry);
void searchEntry (vector<vector<string>>& vec);
void removeEntry (vector<vector<string>>& vec);


int main()
{
    string command;
    vector<vector<string>> library_vec;                                                            // the main vector, around which the whole system has been designed.

    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do {
        // Output the menu and acquire a user selection
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";

        getline(cin, command);
        cout << endl;

        if (command == "A" || command == "a") {
            // add item to library

            vector<string> temp;
            temp.push_back("");
            temp.push_back("");
            temp.push_back("0");

            string title;
            string isbn;
            size_t idx = 0;

            cout << "What is the book title? " << endl;
            getline(cin, title);
            idx = title.find(',');

            if (idx > title.length()) {
                temp.at(0) = title;
            }

            else {
                cout << "The book title cannot contain commas." << endl;
                continue;
            }

            cout << "What is the 13-digit ISBN (with hyphens)? " << endl;
            getline(cin, isbn);
            temp.at(1) = isbn;

            cout << "The Following Entry Was Added" << endl << "-----------------------------" << endl;
            cout << temp.at(0) << " --- " << temp.at(1) << " --- " << "In Library" << endl;

            library_vec.push_back(temp);
        }

        else if (command == "C" || command == "c") {
            // clear all entries -> vector.clear();
            cout << "Your library is now empty." << endl;
            library_vec.clear();
        }

        else if (command == "D" || command == "d") {
            // Display all entries

            cout << "Your Current Library" << endl << "--------------------" << endl;

            if (library_vec.size() > 0) {
                for (int i=0; i<library_vec.size(); i++) {                                             // for loop traverses the library_vec and is used to output the library entries
                    displayEntry(library_vec.at(i));
                }
            }

            else {
                cout << "The library has no books." << endl;
            }


        }

        else if (command == "I" || command == "i") {
            // List invalid entries
            int count = 0;
            cout << "The Following Library Entries Have Invalid Data" << endl << "-----------------------------------------------" << endl;

            for (int i=0; i<library_vec.size(); i++) {
                if (!(isbnCheck(library_vec.at(i).at(1))) || stoi(library_vec.at(i).at(2)) > 3 || stoi(library_vec.at(i).at(2)) < 0) {
                    displayEntry(library_vec.at(i));
                    count++;
                }
            }

            if (library_vec.empty()) {
                cout << "The library has no books." << endl;
            }

            else if (count == 0) {
                cout << "The library has no invalid entries." << endl;
            }
        }

        else if (command == "L" || command == "l") {
            // Load library

            string load_file;
            cout << "What database to read from? ";
            getline(cin, load_file);
            cout << endl;


            fstream object_in;
            object_in.open(load_file);


            string data_line;
            // Object_in pushes a line of the input file to the string data_line.
            cout << endl;

            int count = 0;

            if (object_in.is_open()) {
                while (!object_in.eof()) {

                    getline(object_in, data_line);

                    vector<string> data_seperate;                                                       // vector containing 3 seperated values(title, isbn, status).
                    vector<string> temp_data;                                                           // temp_data is a vector which contains the newly seperated values.
                    temp_data.push_back("");
                    temp_data.push_back("000-0-00-000000-0");
                    temp_data.push_back("0");

                    seperateVal(", ", data_line, data_seperate);


                    temp_data.at(0) = data_seperate.at(0);

                    if (data_seperate.size()>1) {
                        temp_data.at(1) = data_seperate.at(1);
                    }

                    if (data_seperate.size()>2) {
                        temp_data.at(2) = data_seperate.at(2);
                    }

                    library_vec.push_back(temp_data);                                                  // temp_data is pushed into the library_vec vector, which contains data about the whole library.

                    count++;
                }

                cout << "Read in " << count << " lines from the file." << endl;

                object_in.close();
            }

            else {
                cout << "Could not find the database file." << endl;
            }
        }

        else if (command == "O" || command == "o") {
            // Output library

            string output_file;
            cout << "Where should the database output to? " << endl;
            getline(cin, output_file);
            cout << endl;

            ofstream object_out;
            object_out.open(output_file);

            for (int i=0; i<library_vec.size(); i++) {
                object_out << (library_vec.at(i)).at(0) << ", " << (library_vec.at(i)).at(1) << ", " << (library_vec.at(i)).at(2) << endl;
            }

            cout << library_vec.size() << " lines of data written to " << output_file << endl;
            object_out.close();
        }

        else if (command == "P" || command == "p") {
            // Print checkout stats
            int in = 0;
            int out = 0;
            int on = 0;
            int unk = 0;
            int other = 0;

            cout << "Your Current Library's Stats" << endl << "----------------------------" << endl;

            for (int i=0; i<library_vec.size()  ; i++) {                                           // incrementing the right variable for the print checkout stats function.
                switch (stoi((library_vec.at(i)).at(2))) {
                    case 0:
                        in++;
                        break;

                    case 1:
                        out++;
                        break;

                    case 2:
                        on++;
                        break;

                    case 3:
                        unk++;
                        break;

                    default:
                        other++;
                        break;
                }
            }

            cout << "Total Books: " << library_vec.size() << endl;
            cout << "   In Library: " << in << endl;
            cout << "   Checked Out: " << out << endl;
            cout << "   On Loan: " << on << endl;
            cout << "   Unknown: " << unk << endl;
            cout << "   Other: " << other << endl;
        }

        else if (command == "R" || command == "r") {
            // remove the last library entry.
            removeEntry(library_vec);

        }

        else if (command == "S" || command == "s") {
            // Search for an entry

            searchEntry(library_vec);
        }

        else if (command != "x" && command != "X") {
            cout << "Unknown command" << endl;
        }

        cout << endl;
    } while (!(command == "x" || command == "X"));

    return 0;
}


// Function definitions for all the glorious function decomposition


/// @brief print out the main menu of the management system
void printMenu () {
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;
    cout << "S - Search For A Library Entry" << endl;
    cout << "X - Exit Program" << endl;
}

void seperateVal (string delim, string data_line, vector<string>& vec)
{
    data_line += delim;
    size_t idx = data_line.find(delim);
    string push = "";

    while (idx < data_line.size())
    {
        push = data_line.substr(0, idx);

        vec.push_back(push);

        data_line = data_line.substr(idx+2, data_line.size()-idx);
        idx = data_line.find(delim);
    }
}

bool isbnCheck (string isbn) {
    int count = 0;
    vector<int> idx;

    for (int i=0; i<isbn.length(); i++) {
        if (isdigit(isbn.at(i))) {
            idx.push_back(i);
            count++;
        }
    }

    int last = (isbn.at(idx.at(idx.size()-1)))-'0';
    idx.pop_back();

    if (count == 13) {
        int total = 0;
        for (int j=0; j<idx.size(); j++) {
            if ((j+1)%2 == 0) {
                total += 3 * ((isbn.at(idx.at(j)))-'0');
            }

            else {
                total += ((isbn.at(idx.at(j)))-'0');
            }
        }

        if (isbn == "000-0-00-000000-0") {
            return true;
        }

        if (last == (10 - (total%10))) {
            return true;
        }


    }

    return false;
}

void displayEntry (vector<string> entry) {
    string str_status;

    switch (stoi(entry.at(2))) {                                          // switch case is used to convert the numerical status into a string.
        case 0:
            str_status = "In Library";
            break;

        case 1:
            str_status = "Checked Out";
            break;

        case 2:
            str_status = "On Loan";
            break;

        case 3:
            str_status = "Unknown State";
            break;

        default:
            str_status = "Invalid State";
            break;

    }

    cout << entry.at(0) << " --- " << entry.at(1) << " --- " << str_status << endl;
}

void searchEntry (vector<vector<string>>& vec) {
    // Function searches for an entry using the user defined input.

    string choice;
    int count = 0;
    int idx = 0;
    cout << "Would you like to search by (1) name or (2) ISBN.\nEnter the numeric choice: " << endl;
    getline(cin, choice);

    if (choice == "1") {
        // search by name
        string search_item;
        cout << "Enter the book name: ";
        getline(cin, search_item);
        cout << endl;
        cout << "The Following Are Your Search Results" << endl << "-------------------------------------" << endl;

        for (int i = 0; i < vec.size(); i++) {
            if ((vec.at(i)).at(0) == search_item) {
                count++;
                idx = i;
            }
        }

        if (count >= 1) {                                                                          // using this if condition, we can search for the latest entry with the same name.
            displayEntry(vec.at(idx));
        }

    }

    else if (choice == "2") {
        // search by name
        string search_item;
        cout << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin, search_item);
        cout << endl;
        cout << "The Following Are Your Search Results" << endl << "-------------------------------------" << endl;

        for (int j = 0; j < vec.size(); j++) {
            if ((vec.at(j)).at(1) == search_item) {
                count++;
                idx = j;
            }
        }

        if (count >= 1) {                                                                          // using this if condition, we can search for the latest entry with the same isbn.
            displayEntry(vec.at(idx));
        }

    }

    else {
        cout << "Invalid search by choice option." << endl;
        count++;
    }

    if (count < 1) {
        cout << "No matching entry found in the library." << endl;
    }
}

void removeEntry (vector<vector<string>>& vec) {
    // Function searches & removes an entry using the user defined input.


    string choice;
    int count = 0;
    int idx = 0;
    cout << "Would you like remove by (1) name or (2) ISBN.\nEnter the numeric choice: " << endl;
    getline(cin, choice);
    cout << endl;

    if (choice == "1") {
        // remove by name
        string search_item;
        cout << "Enter the book name: ";
        getline(cin, search_item);
        cout << endl;
        cout << "The Following Entry Was Removed From The Library" << endl << "------------------------------------------------" << endl;

        for (int i=0; i<vec.size(); i++) {
            if ((vec.at(i)).at(0) == search_item) {
                count++;
                idx = i;
            }
        }

        if (count >= 1) {                                                                          // using this if condition, we can remove the latest entry with the same name.
            displayEntry(vec.at(idx));
            vec.erase(vec.begin()+idx);
        }

    }

    else if (choice == "2") {
        // remove by isbn
        string search_item;
        cout << "Enter the book 13-digit ISBN (with dashes):";
        getline(cin, search_item);
        cout << endl;
        cout << "The Following Entry Was Removed From The Library" << endl << "------------------------------------------------" << endl;

        for (int j=0; j<vec.size(); j++) {
            if ((vec.at(j)).at(1) == search_item) {
                count++;
                idx = j;
            }
        }

        if (count >= 1) {                                                                          // using this if condition, we can remove the latest entry with the same isbn.
            displayEntry(vec.at(idx));
            vec.erase(vec.begin()+idx);
        }
    }

    else {
        cout << "Invalid remove by choice option." << endl;
        count++;
    }

    if (count < 1) {
        cout << "No matching entry found in the library." << endl;
    }

}
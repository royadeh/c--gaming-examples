#include <iostream>
#include <string>
#include <vector>
#include <cctype> //functions like toupper()

using namespace std;

class student {
protected:
    string name;
    char level;

public:
    // Constructor
    student(string name, char level) {
        this->name = name;
        this->level = level;
    }

    // Get the level of the student
    char getLevel() const { return this->level; }

    void showDetails() {
        cout << "Name: " << name << endl;
        cout << "Level: " << level << endl;
    }
};

class Undergraduate : public student {
public:
    double CGPA;

    // Constructor that calls the base class constructor
    Undergraduate(string _name, char _level, double _CGPA)
        : student(_name, _level), CGPA(_CGPA) {}

    void showDetails() {
        student::showDetails();
        cout << "CGPA: " << CGPA << endl;
    }
};

class Graduate : public student {
public:
    string specialization;

    // Constructor that calls the base class constructor
    Graduate(string _name, char _level, string _specialization)
        : student(_name, _level), specialization(_specialization) {}

    void showDetails() {
        student::showDetails();
        cout << "Specialization: " << specialization << endl;
    }
};

void display(vector<student *> &students) {
    int undergradCount = 0;
    int gradCount = 0;

    for (auto student : students) {
        student->showDetails();
        if (student->getLevel() == 'U') {
            undergradCount++;
        } else if (student->getLevel() == 'G') {
            gradCount++;
        }
    }

    cout << "Total Undergraduate Students: " << undergradCount << endl;
    cout << "Total Graduate Students: " << gradCount << endl;
}

int main() {
    char choice;
    string name;
    char level;
    vector<student *> students; // for polymorphism
    do {
        cout << "\nEnter Student's Full Name: ";
        getline(cin, name);

        cout << "Enter Level of Student (G = Graduate, U = Undergraduate): ";
        cin >> level;
        level = toupper(level);
        cin.ignore(); // Clear the buffer

        if (level == 'U') {
            double cgpa;
            cout << "Enter CGPA: ";
            cin >> cgpa;
            Undergraduate* undergraduate = new Undergraduate(name, level, cgpa);  // Pass arguments to the constructor
            students.push_back(undergraduate);
        } else if (level == 'G') {
            string specialization;
            cout << "Enter Specialization: ";
            cin.ignore(); // Clear the buffer before reading the string
            getline(cin, specialization);
            Graduate* graduate = new Graduate(name, level, specialization);  // Pass arguments to the constructor
            students.push_back(graduate);
        }

        cout << "\nDo you want to continue (Y/N)? ";
        cin >> choice;
        cin.ignore(); // Clear the buffer
    } while (choice == 'y' || choice == 'Y');

    display(students);  // Display student information
    for (int i = 0; i < students.size(); i++) {
        delete students[i]; // Clean up memory
    }
    return 0;
}

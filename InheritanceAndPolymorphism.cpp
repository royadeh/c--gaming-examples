#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class student{
    public:
    string name;
    char level;
    
    void setName(string name){
        this ->name = name;
    }
    
    void setLevel(char level){
        this -> level = level;
    }
    
    char getLevel()const{return this-> level;}
    
    void showDetails(){
        cout << "Name: " << name << endl;
        cout << "Level: " << level << endl;  // Corrected the output here
    }
};

class Undergraduate : public student{
    public:
    double CGPA;
    
    void setCGPA(double CGPA){
        this -> CGPA = CGPA;
    }
};

class Graduate : public student{
    public:
    string specialization;
    
    void setSpecialization(string specialization){
        this -> specialization = specialization;
    }
};

// void display(vector<Undergraduate> &students) {
//     for (auto &student : students) {
//         student.showDetails();
//     }
// }

// void display(vector<Graduate> &students) {
//     for (auto &student : students) {
//         student.showDetails();
//     }
// }

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
            Undergraduate* undergraduate = new Undergraduate();
            double cgpa;
            undergraduate->setName(name);
            undergraduate->setLevel(level);
            cout << "Enter CGPA: ";
            cin >> cgpa;
            undergraduate->setCGPA(cgpa);
            students.push_back(undergraduate);
        }
        else if (level == 'G') {
            Graduate* graduate = new Graduate();
            string specialization;
            graduate->setName(name);
            graduate->setLevel(level);
            cout << "Enter Specialization: ";
            getline(cin, specialization);
            graduate->setSpecialization(specialization);
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

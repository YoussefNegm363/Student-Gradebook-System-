#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

struct Subject {
    string name;
    string doctor;
};

struct Grade {
    float score;
    string letter;
};

struct Student {
    int id;
    string name;
    string college;
    string major;
    string year;
    vector<Subject> subjects;
    map <string , Grade> grades;
    bool gradesEntered = false;
};

vector <Student> students;

string getLetterGrade (float grade) {
    if (grade >= 97) return "A+";
    if (grade >= 93) return "A";
    if (grade >= 89) return "A-";
    if (grade >= 84) return "B+";
    if (grade >= 80) return "B";
    if (grade >= 76) return "B-";
    if (grade >= 72) return "C+";
    if (grade >= 68) return "C";
    if (grade >= 64) return "C-";
    if (grade >= 60) return "D";
    else return "F";
}

void addStudent() {   //Abram Adel
    Student s;
    cout << "Enter student ID: "; cin >> s.id;
    cin.ignore();
    cout << "Enter student name: "; getline(cin, s.name);
    cout << "Enter college: "; getline(cin, s.college);
    cout << "Enter major: "; getline(cin, s.major);
    cout << "Enter year (Freshman/Sophomore/Junior/Senior): "; getline(cin, s.year);
    students.push_back(s);
}

void addSubjectsToStudent() {   //Hana Alaa
     if (students.empty()) {
        cout << "No students available. Add a student first.\n";
        return ;
     }
     int id ;
     cout << "Enter student ID to add subjects: ";
     cin >> id ;
     cin.ignore();
     for (auto& s : students) {
        if (s.id == id) {
            int n;
            cout << "Enter number of subjects for " << s.name << ": ";
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n; ++i) {
                Subject subj;
                cout << "Enter subject name: "; getline(cin, subj.name);
                cout << "Enter doctor name: "; getline(cin, subj.doctor);
                s.subjects.push_back(subj);
            }
            return;
        }
     }
     cout << "Student not found.\n";
}

void enterGrades() {  //Ali eldib
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }
    int id;
    cout << "Enter student ID to enter grades: ";
    cin >> id;
    cin.ignore();
    for (auto& s : students) {
        if (s.id == id) {
            if (s.subjects.empty()) {
                cout << "This student has no subjects.\n";
                return;
            }
            if (s.gradesEntered) {
                cout << "Grades already entered for " << s.name << ".\n";
                return;
            }
            cout << "\nEntering grades for: " << s.name << endl;
            for (auto& subj : s.subjects) {
                Grade g;
            do {
            cout << "Enter grade for " << subj.name << " (0 - 100): ";
            cin >> g.score;
            if (g.score < 0 || g.score > 100) {
            cout << "Invalid input. Grade must be between 0 and 100.\n";
            }
            } while (g.score < 0 || g.score > 100);
                g.letter = getLetterGrade(g.score);
                s.grades[subj.name] = g;
            }
            s.gradesEntered = true;
            return;
        }
    }

    cout << "Student not found.\n";
}

void calculateAverage() {   //Youssef Negm
    for (auto& s : students) {
        if (s.grades.empty()) {
            cout << "\nNo grades found for " << s.name << ".\n";
            continue;
        }

        float total = 0;
        for (auto& [_, grade] : s.grades) {
            total += grade.score;
        }
        float avg = total / s.grades.size();
        cout << "\nAverage for " << s.name << ": " << avg
             << " -> Letter Grade: " << getLetterGrade(avg) << endl;
    }
}

void printLetterGrades() {  //Sief
    for (auto& s : students) {
        cout << "\nGrades for: " << s.name << endl;
        for (auto& [subject, grade] : s.grades) {
            cout << "  " << subject << ": " << grade.letter << " (" << grade.score << ")\n";
        }
    }
}

void exportToCSV() {  //basmala mahmoud
    ofstream file("grades.csv");
    file << "ID , Name , College , Major , Year , Subject , Doctor , Score , Letter\n";
    for (auto& s : students) {
        for (auto& subj : s.subjects) {
            file << s.id << "," << s.name << "," << s.college << ","
                 << s.major << "," << s.year << ","
                 << subj.name << "," << subj.doctor << ",";
            if (s.grades.count(subj.name)) {
                file << s.grades[subj.name].score << "," << s.grades[subj.name].letter << "\n";
            } else {
                file << "N/A,N/A\n";
            }
        }
    }
    file.close();
    cout << "Exported to grades.csv\n";
}

void menu() {  //Steven Magdy
    int choice;
    do {
        cout << "\n *** Student GradeBook Menu *** \n";
        cout << "1. Add Student\n";
        cout << "2. Add Subjects to Student\n";
        cout << "3. Enter Grades for Student\n";
        cout << "4. Calculate Average Grades\n";
        cout << "5. Print Letter Grades\n";
        cout << "6. Export to CSV\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addStudent() ; break;
            case 2: addSubjectsToStudent(); break;
            case 3: enterGrades(); break;
            case 4: calculateAverage(); break;
            case 5: printLetterGrades(); break;
            case 6: exportToCSV(); break;
            case 7: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}

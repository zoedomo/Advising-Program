// Project 2
// Zoe Domagalski
// Hash Table Advisng Software

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Course class to hold course info
class Course {
public:
    string courseNumber;
    string name;
    vector<string> prerequisites;

    Course() = default; // default constructor

    Course(const string& number, const string& courseName, const vector<string>& prereqs)
        : courseNumber(number), name(courseName), prerequisites(prereqs) {}
};

//  sorting courses alphabetically
bool compareCourses(const Course& course1, const Course& course2) {
    return course1.courseNumber < course2.courseNumber;
}

// hash table to store course objects
map<string, Course> courses;

// function to load data from file into data structure
void loadDataStructure(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) { //read each line from the file

        istringstream iss(line);
        string courseNumber, courseName;
        vector<string> prerequisites;

        getline(iss, courseNumber, ','); // extract course number
        getline(iss, courseName, ','); // extract course name 

        string prerequisite;
        while (getline(iss, prerequisite, ',')) { // extract each prerequisite 
            prerequisites.push_back(prerequisite);
        }

        Course course(courseNumber, courseName, prerequisites); // create a Course object
        courses[courseNumber] = course; //store in map
    }

    file.close();
    cout << "Data Structure loaded successfully." << endl;
}

// function to print course list in alphanumeric order
void printCourseList() {
    vector<Course> sortedCourses; // store sorted courses
    for (const auto& pair : courses) { // iterate over each course in the map
        sortedCourses.push_back(pair.second);
    }

    sort(sortedCourses.begin(), sortedCourses.end(), compareCourses);

    for (const auto& course : sortedCourses) {    // iterate over each sorted course
        cout << "Course Number: " << course.courseNumber << endl;
        cout << "Course Name: " << course.name << endl;
        cout << endl;
    }
}

//function to print course information and prerequisites
void printCourse() {
    string courseNumber;
    cout << "Enter the course number: ";
    cin >> courseNumber;

    if (courses.find(courseNumber) != courses.end()) { // check if course number exists
        const Course& course = courses[courseNumber];
        cout << "Course Number: " << course.courseNumber << endl;
        cout << "Course Name: " << course.name << endl;

        if (!course.prerequisites.empty()) { // check if there are prerequisites
            cout << "Prerequisites:" << endl;
            for (const auto& prerequisite : course.prerequisites) {
                cout << prerequisite << endl;
            }
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}

// function to display menu and prompt for user input
int getMenuChoice() {
    int choice;
    cout << "Welcome to the course planner.\n" << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "4. Exit\n" << endl;
    cout << "What would you like to do? ";

    while (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // making sure user input matches data type to prevent infinite loop 
        cout << "Invalid input. Please enter a number from the menu: ";
    }

    return choice;
}

int main() {
    string filename;
    bool dataStructureLoaded = false;

    while (true) { // loop until program is exited
        int choice = getMenuChoice(); // display menu

        switch (choice) {
        case 1: {
            cout << "Enter the filename: ";
            cin >> filename;
            loadDataStructure(filename);
            dataStructureLoaded = true; //setting to true if loaded
            break;
        }
        case 2: {
            if (!dataStructureLoaded) {
                cout << "Data Structure not loaded. Please load the data structure" << endl;
            }
            else {
                printCourseList();
            }
            break;
        }
        case 3: {
            if (!dataStructureLoaded) {
                cout << "Data Structure not loaded. Please load the data structure." << endl;
            }
            else {
                printCourse();
            }
            break;
        }
        case 4:
            cout << "Thank you for using the course planner!" << endl;
            return 0;   // exit the program
        default:
            cout << "Invalid option." << endl;
        }
    }

    return 0;
}
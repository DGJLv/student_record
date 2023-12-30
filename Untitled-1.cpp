#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;


// outStream.open("important.txt,ios::app")


// constructor for struct named Student
struct Student{
    // c-string for names
    char lastName[20];
    char firstName[20];
    char course;
    int test1;
    int test2;
    int final;
    double average;
};
// decide the letter grade for the given grade
// @parm grade: grade to evaluate
// @return: letter grade after evaluation
char letterGrade(double grade){
    if (grade >= 90){
        return 'A';
    }else if (grade >= 80){
        return 'B';
    }else if (grade >= 70){
        return 'C';
    }else if (grade >= 60){
        return 'D';
    }else{
        return 'F';
    }
    
}
// function for displaying the grade sheet on the output file
// @param outFile:
// @param students[]: array of struct to 
void gradeDisplay(ofstream &outFile, Student students[], char course, int studentNum) {
    cout << "student course is "<<students[0].course;
    outFile << setfill(' ') << left << setw(37) << "\nStudent Name" << right << setw(16) << "Test Avg" << right << setw(8) << "Grade\n";
    outFile << setfill('-') << setw(64) << "\n";
    // initialize counter and sum of the grade for average grade
    double sumAvg = 0;
    int count = 0;
    // compare course with the student's course and display student average score and letter grade
    for (int i = 0; i < studentNum; i++) {
        // when the student's course is same as the given course
        if (course == students[i].course) {
            // call letterGrade function for finding letter grade of average score
            char letterGrade1 = letterGrade(students[i].average);
            // merge student last name and first name to store it into string name
            string name = students[i].lastName + string(", ") + students[i].firstName;
            // output the student grade in the proper format
            outFile << setfill(' ') << left << setw(40) << name 
                    << right << setw(10) << fixed << setprecision(2) << students[i].average 
                    << setw(8) << letterGrade1 << "\n";
            // add each of student average to the sumAvg
            sumAvg += students[i].average;
            // add count for every student displayed
            count += 1;
        }
    }
    // when more than one student took the class
    if (count > 0) {
        // class average is on the 
        double classAvg = sumAvg / count;
        outFile << "\n" << left << setw(40) << "Class Average" 
                << right << setw(10) << fixed << setprecision(2) << classAvg 
                << setw(8) << letterGrade(classAvg) << "\n";
    }

    outFile << setfill('-') << setw(64) << "\n";  // Always write this at the end
}

bool compareByLastName(const Student &a, const Student &b) {
    return strcmp(a.lastName, b.lastName) < 0; 
}

int main()
{
    ofstream outFile;
    ifstream inFile;
    string inFileName, outFileName, line;
    bool open = false;

    while (!open) {
        cout << "Enter name of inventory file: ";
        cin >> inFileName;
        inFile.open(inFileName);
        if (inFile.is_open()) {
            open = true;
        } else {
            cout << "Error opening file. Please try again." << endl;
        }
    }
    // prompt the outfile name
    cout << "Please enter the name of the output file." <<endl;
    cout << "Filename: ";
    cin >> outFileName;
    // open file with given name
    // if no file exist new file created
    outFile.open(outFileName);

    // read the first line of the input file
    getline(inFile, line);
    // change string to integer for number of student
    int studentNum = stoi(line);
    // make struct array with read student number 
    Student student[studentNum];
    
    for (int i = 0; i < studentNum && getline(inFile, line); i++){
        stringstream sstream(line);
        char delim;
        string temp;
    // get number of students
    getline(sstream, temp, ',');
    strncpy(student[i].lastName, temp.c_str(), sizeof(student[i].lastName));
    student[i].lastName[sizeof(student[i].lastName) - 1] = '\0';  // Ensure null termination

    getline(sstream, temp, ',');
    strncpy(student[i].firstName, temp.c_str(), sizeof(student[i].firstName));

    student[i].firstName[sizeof(student[i].firstName) - 1] = '\0';
    sstream >> student[i].course >> delim;
    sstream >> student[i].test1 >> delim;
    sstream >> student[i].test2 >> delim;
    sstream >> student[i].final;

    // add element average to the struct using test1, test2 and final value
    student[i].average = student[i].test1*0.3+student[i].test2*0.3+student[i].final*0.4;
        
  
    }
    // sort the student array into alphabetical order 
    sort(student, student + studentNum, compareByLastName);
    // print the format of the grade sheet
    outFile << "Student Grade Summary\n---------------------\n";
    outFile << "\nENGLISH CLASS\n";
    // call gradeDisplay function for English class
    gradeDisplay(outFile, student, 'E', studentNum);
    outFile << "\n\nHISTORY CLASS\n";
    // call gradeDisplay function for History class
    gradeDisplay(outFile, student, 'H', studentNum);
    outFile << "\n\nMATH CLASS\n";
    // call gradeDisplay function for Math class
    gradeDisplay(outFile, student, 'M', studentNum);
    
    // close input and output file 
    inFile.close();
    outFile.close();






    return 0;
}



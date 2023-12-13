#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int skip = 90000;

class Student
{
    string name, roll_num, age, contact, course, attendance, marks;

public:
    void studentEnrolMenu();
    void displayStudent();
    void Enrol();
    void Remove();
    void Edit();
    void attendanceMenu();
    void displayAttendance();
    void markAttendance();
    void marksMenu();
    void displayMarks();
    void assignMarks();
};

class Course
{
    string code, name, instructor, credits, capacity, students;

public:
    void courseRegMenu();
    void addCourse();
    void removeCourse();
    void displayCourse();
    void courseWithdrawMenu();
    void enrolledCourse();
    void dropCourse();
};

class System
{
    string students, courses, menus;

public:
    void mainMenu();
};

void System::mainMenu() // Function of Main Menu
{
    int option;
    Student st;
    Course cr;

    cout << "Choose an option from the menu\n";
    cout << "1- Enroll a student\n2- Course Registration\n3- Attendance\n4- Marks\n5- Course Withdraw\n6- Exit\n";
    cout << "Option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        st.studentEnrolMenu();
        break;
    case 2:
        cr.courseRegMenu();
        break;
    case 3:
        st.attendanceMenu();
        break;
    case 4:
        st.marksMenu();
        break;
    case 5:
        cr.courseWithdrawMenu();
        break;
    case 6:
        cout << "Program Terminated";
        return;
    default:
        cout << "\nInvalid option";
    }
}

void Student::studentEnrolMenu() // Function of Student Enrol Menu
{
    int option;
    System sys;
    cout << "1- Display Student information\n2- Add a Student\n3- Remove a Student\n4- Edit Student\n5- back";
    cout << "\nOption: ";
    cin >> option;

    switch (option)
    {
    case 1:
        displayStudent();
        break;

    case 2:
        Enrol();
        break;

    case 3:
        Remove();
        break;

    case 4:
        Edit();
        break;

    case 5:
        sys.mainMenu();
        break;

    default:
        cout << "\nInvalid option";
    }
}

void Student::displayStudent() // Function to display enrolled students
{
    // Read and print the contents of the file
    ifstream readStudent("students.txt");
    cout << "\nContents of the file:\n";
    while (readStudent) // Reading until file ends
    {
        readStudent >> name;
        readStudent >> roll_num;
        readStudent >> age;
        readStudent >> contact;
        readStudent >> course;
        readStudent >> attendance;
        readStudent >> marks;

        cout << "Name: " << name << " Roll Number: " << roll_num << " Age: " << age << " Contact: " << contact << " Course: " << course << " Attendance: " << attendance << " Marks: " << marks << endl;
    }
    readStudent.close();
}

void Student::Enrol() // Function to Enrol students
{
    ofstream writeStudent("students.txt", ios::app); //opening file in append mode

    if (!writeStudent.is_open()) //checking if the file is successfully opened or not
        cout << "Error opening the file for writing!" << endl;

    else
    {
        cout << "Enter name, roll number, age, contact, course, attendance and marks (with spaces)\n";
        getline(cin, name, ' ');
        getline(cin, roll_num, ' ');
        getline(cin, age, ' ');
        getline(cin, contact, ' ');
        getline(cin, course, ' ');
        getline(cin, attendance, ' ');
        getline(cin, marks);

        writeStudent << name << " " << roll_num << " " << age << " " << contact << " " << course << " " << attendance << " " << marks;
        writeStudent.close();

        cout << "Student information added to the file successfully!" << endl;
    }
}

void Student::Remove() // Function to Remove students
{
    int index;
    ifstream readStudent("students.txt");

    if (!readStudent.is_open()) //checking if the file is successfully opened or not
        cout << "Error while opening the file for reading!" << endl;

    else
    {
        cout << "\nEnter the index of the student you want to remove: ";
        cin >> index;

        for (int i = 0; i < index; ++i) // Skipping until desired index is found
            readStudent.ignore(skip, '\n');

        readStudent >> name;
        readStudent >> roll_num;
        readStudent >> age;
        readStudent >> contact;
        readStudent >> course;
        readStudent >> attendance;
        readStudent >> marks;

        readStudent.close();

        cout << "Student to be removed:\nName: " << name << " Roll Number: " << roll_num << " Age: " << age << " Contact: " << contact << " Course: " << course << " Attendance: " << attendance << " Marks: " << marks << endl;

        ofstream writeStudentTemp("newfile.txt");
        if (writeStudentTemp.is_open())
        {
            ifstream readStudentTemp("students.txt");
            if (readStudentTemp.is_open())
            {
                string line;
                while (getline(readStudentTemp, line))
                    if (line != (name + ' ' + roll_num + ' ' + age + ' ' + contact + ' ' + course + ' ' + attendance + ' ' + marks))
                        writeStudentTemp << line << '\n';
                readStudentTemp.close();
            }
            writeStudentTemp.close();
        }

        if (remove("students.txt") == 0 && rename("newfile.txt", "students.txt") == 0) // Removing current file then shifting all information to a new file and then renaming it
            cout << "Student you selected has been successfully removed\n";
        else
            cout << "There is an Error while removing the student!\n";
    }
}

void Student::Edit() // Function to Edit student information
{
    int index;
    string tempName, tempRoll_num, tempAge, tempContact, tempCourse, tempAttendance, tempMarks;

    ifstream readStudent("students.txt");
    if (!readStudent.is_open()) //checking if the file is successfully opened or not
        cout << "Error while opening the file for reading!" << endl;

    else
    {
        cout << "\nEnter the index (starting from zero index) of the student you want to Edit: ";
        cin >> index;

        for (int i = 0; i < index; ++i)
            readStudent.ignore(skip, '\n');

        readStudent >> name;
        readStudent >> roll_num;
        readStudent >> age;
        readStudent >> contact;
        readStudent >> course;
        readStudent >> attendance;
        readStudent >> marks;

        readStudent.close();

        cout << "Student to be Edited:\nName: " << name << " Roll Number: " << roll_num << " Age: " << age << " Contact: " << contact << " Course: " << course << " Attendance: " << attendance << " Marks: " << marks << endl;

        ofstream writeStudentTemp("newfile.txt");
        if (writeStudentTemp.is_open())
        {
            ifstream readStudentTemp("students.txt");
            if (readStudentTemp.is_open())
            {
                string line;
                while (getline(readStudentTemp, line))
                {
                    if (line != (name + ' ' + roll_num + ' ' + age + ' ' + contact + ' ' + course + ' ' + attendance + ' ' + marks))
                        writeStudentTemp << line << '\n';
                    else
                    {
                        cout << "Edit name, roll number, age, contact, course, attendance and marks (with spaces):\n";
                        //geting the input with space as an idication to getting next input
                        getline(cin, tempName, ' ');
                        getline(cin, tempRoll_num, ' ');
                        getline(cin, tempAge, ' ');
                        getline(cin, tempContact, ' ');
                        getline(cin, tempCourse, ' ');
                        getline(cin, tempAttendance, ' ');
                        getline(cin, tempMarks);

                        line = tempName + ' ' + tempRoll_num + ' ' + tempAge + ' ' + tempContact + ' ' + tempCourse + ' ' + tempAttendance + ' ' + tempMarks;
                        writeStudentTemp << line << '\n';
                    }
                }
                readStudentTemp.close();
            }
            writeStudentTemp.close();
        }

        if (remove("students.txt") == 0 && rename("newfile.txt", "students.txt") == 0) // Removing current file then shifting all information to a new file and then renaming it
            cout << "Student information Edited successfully!" << endl;

        else
            cout << "There is an Error while editing the student!\n";
    }
}

void Student::attendanceMenu() // Function of Attendance Menu
{
    int option;
    System sys;
    cout << "1- Display attendance\n2- Mark attendance\n3- back";
    cout << "\nOption: ";
    cin >> option;

    switch (option)
    {
    case 1:
        displayAttendance();
        break;

    case 2:
        markAttendance();
        break;

    case 3:
        sys.mainMenu();
        break;

    default:
        cout << "\nError in option";
        break;
    }
}

void Student::displayAttendance() // Function of Attendance display
{
    ifstream readStudent("students.txt");
    ofstream writeAttendance("attendance.txt");

    if (!writeAttendance.is_open()) //checking if the file is successfully opened or not
        cout << "Error opening the file for writing!" << endl;

    else
    {
        while (readStudent) // Reading until file ends
        {
            readStudent >> name;
            readStudent >> roll_num;
            readStudent >> age;
            readStudent >> contact;
            readStudent >> course;
            readStudent >> attendance;
            readStudent >> marks;

            writeAttendance << name << " " << attendance << endl;
            cout << "Name: " << name << " Attendance: " << attendance << endl;
        }
        readStudent.close();
        writeAttendance.close();
    }
}

void Student::markAttendance() // Function of Attendance marking
{
    ifstream readStudent("students.txt");
    string tempAttendance;
    int index;

    cout << "\nEnter the index of the student you want to mark Attendance: ";
    cin >> index;

    for (int i = 0; i < index; ++i)
        readStudent.ignore(skip, '\n');

    readStudent >> name;
    readStudent >> roll_num;
    readStudent >> age;
    readStudent >> contact;
    readStudent >> course;
    readStudent >> attendance;
    readStudent >> marks;

    readStudent.close();

    cout << "Selected Student for Attendance:\nName: " << name << " Attendance: " << attendance << endl;

    ofstream writeStudentTemp("newfile.txt");
    if (writeStudentTemp.is_open())
    {
        ifstream readStudentTemp("students.txt");
        if (readStudentTemp.is_open())
        {
            string line;
            while (getline(readStudentTemp, line))
            {
                if (line != (name + ' ' + roll_num + ' ' + age + ' ' + contact + ' ' + course + ' ' + attendance + ' ' + marks))
                    writeStudentTemp << line << '\n';
                else
                {
                    cout << "Type P for Present or A for Absent: ";
                    cin >> tempAttendance;

                    line = name + ' ' + roll_num + ' ' + age + ' ' + contact + ' ' + course + ' ' + tempAttendance + ' ' + marks;
                    writeStudentTemp << line << '\n';
                }
            }
            readStudentTemp.close();
        }
        writeStudentTemp.close();


        if (remove("students.txt") == 0 && rename("newfile.txt", "students.txt") == 0) // Removing current file then shifting all information to a new file and then renaming it
            cout << "Student information Edited successfully!" << endl;

        else
            cout << "There is an Error while editing the student!\n";
    }
}

void Student::marksMenu()
{
    int option;
    System sys;
    cout << "1- Display Marks\n2- Assign Marks\n3- back";
    cout << "\nOption: ";
    cin >> option;

    switch (option)
    {
    case 1:
        displayMarks();
        break;

    case 2:
        assignMarks();
        break;

    case 3:
        sys.mainMenu();
        break;

    default:
        cout << "\nError in option";
        break;
    }
}

void Student::displayMarks()
{
    ifstream readStudent("students.txt");

    if (!readStudent.is_open()) //checking if the file is successfully opened or not
        cout << "Error while opening the file for writing!" << endl;

    else
    {
        ofstream writeAttendance("marks.txt"); //opening file in append mode

        if (!writeAttendance.is_open()) //checking if the file is successfully opened or not
            cout << "Error opening the file for writing!" << endl;

        while (readStudent)
        {
            readStudent >> name;
            readStudent >> roll_num;
            readStudent >> age;
            readStudent >> contact;
            readStudent >> course;
            readStudent >> attendance;
            readStudent >> marks;

            writeAttendance << name << " " << marks << endl;
            cout << "Name: " << name << " Marks: " << marks << endl;
        }
        readStudent.close();
        writeAttendance.close();
    }
}

void Student::assignMarks()
{
    ifstream readStudent("students.txt");
    string tempMarks;
    int index;

    if (!readStudent.is_open()) //checking if the file is successfully opened or not
        cout << "Error while opening the file for writing!" << endl;

    else
    {
        cout << "\nEnter the index of the student you want to Assign Marks: ";
        cin >> index;

        for (int i = 0; i < index; ++i)
            readStudent.ignore(skip, '\n');

        readStudent >> name;
        readStudent >> roll_num;
        readStudent >> age;
        readStudent >> contact;
        readStudent >> course;
        readStudent >> attendance;
        readStudent >> marks;

        readStudent.close();

        cout << "Selected Student for Attendance:\nName: " << name << " Attendance: " << marks << endl;

        ofstream writeStudentTemp("newfile.txt");
        if (writeStudentTemp.is_open())
        {
            ifstream readStudentTemp("students.txt");
            if (readStudentTemp.is_open())
            {
                string line;
                while (getline(readStudentTemp, line))
                {
                    if (line != (name + ' ' + roll_num + ' ' + age + ' ' + contact + ' ' + course + ' ' + attendance + ' ' + marks))
                        writeStudentTemp << line << '\n';
                    else
                    {
                        cout << "Enter Marks in percentage: ";
                        cin >> tempMarks;

                        line = name + ' ' + roll_num + ' ' + age + ' ' + contact + ' ' + course + ' ' + attendance + ' ' + tempMarks;
                        writeStudentTemp << line << '\n';
                    }
                }
                readStudentTemp.close();
            }
            writeStudentTemp.close();
        }

        if (remove("students.txt") == 0 && rename("newfile.txt", "students.txt") == 0) // Removing current file then shifting all information to a new file and then renaming it
            cout << "Student information Edited successfully!" << endl;

        else
            cout << "There is an Error while editing the student!\n";
    }
}

void Course::courseRegMenu()
{
    int option;
    System sys;
    cout << "1- Add a course\n2- Remove a course\n3- Display courses\n4- back";
    cout << "\nOption: ";
    cin >> option;

    switch (option)
    {
    case 1:
        addCourse();
        break;

    case 2:
        removeCourse();
        break;

    case 3:
        displayCourse();
        break;

    case 4:
        sys.mainMenu();
        break;

    default:
        cout << "\nInvalid option";
        break;
    }
}

void Course::addCourse()
{
    ofstream writeCourse("courses.txt", ios::app); //opening file in append mode

    if (!writeCourse.is_open()) //checking if the file is successfully opened or not
        cout << "Error opening the file for writing!" << endl;

    else
    {
        cout << "Enter Course Code, Course Name, Instructor Name, Credit Hours, Capacity, No. of Students(with spaces)\n";
        getline(cin, code, ' ');
        getline(cin, name, ' ');
        getline(cin, instructor, ' ');
        getline(cin, credits, ' ');
        getline(cin, capacity, ' ');
        getline(cin, students);

        writeCourse << code << " " << name << " " << instructor << " " << credits << " " << capacity << " " << students;
        writeCourse.close();

        cout << "Course information added to the file successfully!" << endl;
    }
}
void Course::removeCourse()
{
    int index;
    ifstream readCourse("courses.txt");

    if (!readCourse.is_open()) //checking if the file is successfully opened or not
        cout << "Error while opening the file for reading!" << endl;

    else
    {
        cout << "\nEnter the index of the course you want to remove: ";
        cin >> index;

        for (int i = 0; i < index; ++i)
            readCourse.ignore(skip, '\n');

        readCourse >> code;
        readCourse >> name;
        readCourse >> instructor;
        readCourse >> credits;
        readCourse >> capacity;
        readCourse >> students;

        readCourse.close();

        cout << "Course to be removed:\nCourse Code: " << code << " Course Name: " << name << " Instructor: " << instructor << " Credit Hours: " << credits << " Capacity: " << capacity << " No. of Students: " << students << endl;

        ofstream writeCourseTemp("new.txt");
        if (writeCourseTemp.is_open())
        {
            ifstream readCourseTemp("courses.txt");
            if (readCourseTemp.is_open())
            {
                string line;
                while (getline(readCourseTemp, line))
                    if (line != (code + ' ' + name + ' ' + instructor + ' ' + credits + ' ' + capacity + ' ' + students))
                        writeCourseTemp << line << '\n';
                readCourseTemp.close();
            }
            writeCourseTemp.close();
        }

        if (remove("courses.txt") == 0 && rename("new.txt", "courses.txt") == 0) // Removing current file then shifting all information to a new file and then renaming it
            cout << "Course you selected has been successfully removed\n";
        else
            cout << "There is an Error while removing the Course!\n";
    }
}
void Course::displayCourse()
{
    ifstream readCourse("courses.txt");

    if (!readCourse.is_open()) //checking if the file is successfully opened or not
        cout << "Error while opening the file for reading!" << endl;

    else
    {
        while (readCourse)
        {
            readCourse >> code;
            readCourse >> name;
            readCourse >> instructor;
            readCourse >> credits;
            readCourse >> capacity;
            readCourse >> students;

            cout << "Course Code: " << code << " Course Name: " << name << " Instructor Name: " << instructor << " Credit Hours: " << credits << " Capacity: " << capacity << " No. Students: " << students << endl;
        }
        readCourse.close();
    }
}

void Course::courseWithdrawMenu()
{
    int option;
    System sys;
    cout << "1- Enrol a course\n2- Drop a course\n3- back";
    cout << "\nOption: ";
    cin >> option;

    switch (option)
    {
    case 1:
        enrolledCourse();
        break;

    case 2:
        dropCourse();
        break;

    case 3:
        sys.mainMenu();
        break;

    default:
        cout << "\nInvalid option";
        break;
    }
}

void Course::enrolledCourse()
{
    ofstream writeCourse("courses.txt", ios::app); //opening file in append mode

    if (!writeCourse.is_open()) //checking if the file is successfully opened or not
        cout << "Error opening the file for writing!" << endl;

    else
    {
        cout << "Enter Course Code, Course Name, Instructor Name, Credit Hours, Capacity, No. of Students(with spaces)\n";
        getline(cin, code, ' ');
        getline(cin, name, ' ');
        getline(cin, instructor, ' ');
        getline(cin, credits, ' ');
        getline(cin, capacity, ' ');
        getline(cin, students);

        writeCourse << code << " " << name << " " << instructor << " " << credits << " " << capacity << " " << students;
        writeCourse.close();

        cout << "Course enrolled to the file successfully!" << endl;
    }
}

void Course::dropCourse()
{
    int index;
    ifstream readCourse("courses.txt");

    if (!readCourse.is_open()) //checking if the file is successfully opened or not
        cout << "Error while opening the file for reading!" << endl;

    else
    {
        cout << "\nEnter the index of the course you want to drop: ";
        cin >> index;

        for (int i = 0; i < index; ++i)
            readCourse.ignore(skip, '\n');

        readCourse >> code;
        readCourse >> name;
        readCourse >> instructor;
        readCourse >> credits;
        readCourse >> capacity;
        readCourse >> students;

        readCourse.close();

        cout << "Course to be droped:\nCourse Code: " << code << " Course Name: " << name << " Instructor: " << instructor << " Credit Hours: " << credits << " Capacity: " << capacity << " No. of Students: " << students << endl;

        ofstream writeCourseTemp("new.txt");
        if (writeCourseTemp.is_open())
        {
            ifstream readCourseTemp("courses.txt");
            if (readCourseTemp.is_open())
            {
                string line;
                while (getline(readCourseTemp, line))
                    if (line != (code + ' ' + name + ' ' + instructor + ' ' + credits + ' ' + capacity + ' ' + students))
                        writeCourseTemp << line << '\n';
                readCourseTemp.close();
            }
            writeCourseTemp.close();
        }

        if (remove("courses.txt") == 0 && rename("new.txt", "courses.txt") == 0) // Removing current file then shifting all information to a new file and then renaming it
            cout << "Course you selected has been successfully droped\n";
        else
            cout << "There is an Error while droping the Course!\n";
    }
}

int main()
{
    System sys;

    sys.mainMenu();

    return 0;
}
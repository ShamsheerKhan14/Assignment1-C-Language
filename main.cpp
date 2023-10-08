/*
 * Course: PROG20799 - Data Structures & Algorithm Development - C
 * Student: Shamsheer Khan
 * Student ID: 991661386
 * Date: 26/05/2023
 * Program Description: Assignment 1 - GPA calculations based on the input file grades.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COURSES 4

// Definition of the Course structure with members for course ID, credits, and grade.
struct Course {
    char courseID[20];
    int credits;
    float grade;
};

//Prototypes for all the functions used in the program
void readCoursesFromFile(struct Course courses[]);
void updateCourseGrade(struct Course courses[]);
float max(float n1, float n2);
float findMaxGradeHelper(struct Course courses[], int index, int n);
float findMaxGrade(struct Course courses[], int n);
void display(struct Course courses[]);
float gradePoints(float grade);
float computeGPA(struct Course courses[]);
void saveCourses(const char* str, struct Course courses[]);
void menu(struct Course courses[]);

/*The main Function of the program, it initializes the courses array to store Course structures
 it calls the readCoursesFromfile function to read course date from a file. it
 * calls the menu function to display the menu
 * at the end it returns 0 to indicate execution of the program.
 */
int main() {
    struct Course courses[MAX_COURSES];

    readCoursesFromFile(courses);

    menu(courses);

    return 0;
}

// Function to display the menu and handle user input
void menu(struct Course courses[]) {
    int choice;

    do {
        printf("------------------------------\n");
        printf("Operations on Courses\n");
        printf("------------------------------\n");
        
        printf("Menu:\n");
        printf("1. Update course grade\n");
        printf("2. Find maximum grade\n");
        printf("3. Display courses\n");
        printf("4. Compute Accumulative GPA\n");
        printf("5. Save courses to the file\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            updateCourseGrade(courses);
            break;
        case 2:
            printf("Maximum grade: %.2f\n", findMaxGrade(courses, MAX_COURSES));
            break;
        case 3:
            display(courses);
            break;
        case 4:
            printf("GPA: %.2f\n", computeGPA(courses));
            break;
        case 5:
            saveCourses("output.txt", courses);
            printf("Courses saved to file.\n");
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }

        printf("\n");
    } while (choice != 6);
}

// Function to read course data from a file
void readCoursesFromFile(struct Course courses[]) {
    FILE* file = fopen("grades.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    for (int i = 0; i < MAX_COURSES; i++) {
        fscanf(file, "%s %d %f", courses[i].courseID, &courses[i].credits, &courses[i].grade);
    }

    fclose(file);
}

// Function to update the grade for a specific course
void updateCourseGrade(struct Course courses[]) {
    char courseID[20];
    float newGrade;

    printf("Enter the course ID: ");
    scanf("%s", courseID);

    // Clear the input buffer
    while (getchar() != '\n')
        ;

    for (int i = 0; i < MAX_COURSES; i++) {
        if (strcmp(courseID, courses[i].courseID) == 0) {
            printf("Enter the new grade for %s: ", courses[i].courseID);
            scanf("%f", &newGrade);

            courses[i].grade = newGrade;
            printf("Grade updated successfully.\n");
            return;
        }
    }

    printf("Course not found.\n");
}

// Function to find the maximum of two numbers
float max(float n1, float n2) {
    return (n1 > n2) ? n1 : n2;
}

// Recursive helper function to find the maximum grade in the courses array
float findMaxGradeHelper(struct Course courses[], int index, int n) {
    if (index == n - 1) {
        return courses[index].grade;
    }
    else {
        float currentGrade = courses[index].grade;
        float maxGrade = findMaxGradeHelper(courses, index + 1, n);
        return max(currentGrade, maxGrade);
    }
}

// Function to find the maximum grade among all courses
float findMaxGrade(struct Course courses[], int n) {
    return findMaxGradeHelper(courses, 0, n);
}

// Function to display the course information
void display(struct Course courses[]) {
    printf("Display courses:\n");
    for (int i = 0; i < MAX_COURSES; i++) {
        printf("%s %d %.0f\n", courses[i].courseID, courses[i].credits, courses[i].grade);
    }
}

// Function to calculate the grade points based on the grade
float gradePoints(float grade) {
    if (grade >= 90) {
        return 4.0;
    }
    else if (grade >= 80) {
        return 3.0;
    }
    else if (grade >= 70) {
        return 2.0;
    }
    else if (grade >= 60) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

// Function to compute the GPA (Grade Point Average) for all courses
float computeGPA(struct Course courses[]) {
    float totalGradePoints = 0.0;
    int totalCredits = 0;

    for (int i = 0; i < MAX_COURSES; i++) {
        float courseGradePoints = gradePoints(courses[i].grade);
        totalGradePoints += (courseGradePoints * courses[i].credits);
        totalCredits += courses[i].credits;
    }

    return totalGradePoints / totalCredits;
}

// Function to save the course data to a file 
void saveCourses(const char* str, struct Course courses[]) {
    FILE* file = fopen(str, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < MAX_COURSES; i++) {
        fprintf(file, "%s %d %.2f\n", courses[i].courseID, courses[i].credits, courses[i].grade);
    }

    fclose(file);
}
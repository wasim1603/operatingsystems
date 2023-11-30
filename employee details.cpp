#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee_details.dat"
#define MAX_EMPLOYEES 50
#define MAX_NAME_LENGTH 50
#define MAX_DEPARTMENT_LENGTH 50

struct Employee {
    int empID;
    char name[MAX_NAME_LENGTH];
    char department[MAX_DEPARTMENT_LENGTH];
    float salary;
};

void addEmployee();
void viewEmployee();
void updateEmployee();
void deleteEmployee();

int main() {
    int choice;

    do {
        printf("\nEmployee Details Management System\n");
        printf("1. Add Employee\n");
        printf("2. View Employee\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                viewEmployee();
                break;
            case 3:
                updateEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}

void addEmployee() {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    struct Employee emp;

    printf("Enter employee ID: ");
    scanf("%d", &emp.empID);

    printf("Enter employee name: ");
    scanf(" %[^\n]s", emp.name);

    printf("Enter employee department: ");
    scanf(" %[^\n]s", emp.department);

    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(struct Employee), 1, file);

    fclose(file);
}

void viewEmployee() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    struct Employee emp;
    int empID;

    printf("Enter employee ID to view details: ");
    scanf("%d", &empID);

    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID == empID) {
            found = 1;
            printf("Employee ID: %d\n", emp.empID);
            printf("Name: %s\n", emp.name);
            printf("Department: %s\n", emp.department);
            printf("Salary: %.2f\n", emp.salary);
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", empID);
    }

    fclose(file);
}

void updateEmployee() {
    FILE *file = fopen(FILENAME, "r+b");
    if (file == NULL) {
        printf("Error opening file for updating!\n");
        return;
    }

    struct Employee emp;
    int empID;

    printf("Enter employee ID to update details: ");
    scanf("%d", &empID);

    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID == empID) {
            found = 1;

            printf("Enter new employee name: ");
            scanf(" %[^\n]s", emp.name);

            printf("Enter new employee department: ");
            scanf(" %[^\n]s", emp.department);

            printf("Enter new employee salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            printf("Employee details updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", empID);
    }

    fclose(file);
}

void deleteEmployee() {
    FILE *file = fopen(FILENAME, "r+b");
    if (file == NULL) {
        printf("Error opening file for deleting!\n");
        return;
    }

    struct Employee emp, emptyEmp = {0, "", "", 0};
    int empID;

    printf("Enter employee ID to delete details: ");
    scanf("%d", &empID);

    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID == empID) {
            found = 1;
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emptyEmp, sizeof(struct Employee), 1, file);
            printf("Employee details deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", empID);
    }

    fclose(file);
}


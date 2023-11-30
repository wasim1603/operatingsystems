#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

void writeEmployeeData(FILE *file, Employee emp) {
    fwrite(&emp, sizeof(Employee), 1, file);
}

void readEmployeeData(FILE *file, int index, Employee *emp) {
    fseek(file, index * sizeof(Employee), SEEK_SET);
    fread(emp, sizeof(Employee), 1, file);
}

void updateEmployeeData(FILE *file, int index, Employee emp) {
    fseek(file, index * sizeof(Employee), SEEK_SET);
    fwrite(&emp, sizeof(Employee), 1, file);
}

void deleteEmployeeData(FILE *file, int index) {
    Employee emp = {0, "", 0.0};
    updateEmployeeData(file, index, emp);
}

void printEmployeeDetails(Employee emp) {
    printf("Employee ID: %d\n", emp.id);
    printf("Employee Name: %s\n", emp.name);
    printf("Employee Salary: %.2f\n", emp.salary);
}

int main() {
    srand(time(0));
    FILE *file = fopen("employees.bin", "a+b");
    if (file == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int choice;
    Employee emp;

    do {
        printf("\n1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display Employee Details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp.id);
                getchar();
                printf("Enter Employee Name: ");
                fgets(emp.name, sizeof(emp.name), stdin);
                emp.name[strlen(emp.name) - 1] = '\0';
                printf("Enter Employee Salary: ");
                scanf("%f", &emp.salary);
                writeEmployeeData(file, emp);
                break;
            case 2:
                printf("Enter Employee ID to update: ");
                scanf("%d", &emp.id);
                updateEmployeeData(file, emp.id - 1, emp);
                break;
            case 3:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &emp.id);
                deleteEmployeeData(file, emp.id - 1);
                break;
            case 4:
                printf("Enter Employee ID to display details: ");
                scanf("%d", &emp.id);
                readEmployeeData(file, emp.id - 1, &emp);
                printEmployeeDetails(emp);
                break;
            case 5:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    fclose(file);
    return 0;
}

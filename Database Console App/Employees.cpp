#include <iostream>
#include <string>
#include <iomanip>
#include "Submenus.h"
#include "QueryBuilder.h"

void printEmployeeUI() {
    std::string text = "Employees Page";

    std::cout << std::endl
        << "****************************************" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "*            " << std::setfill(' ') << std::left << std::setw(26) << text << "*" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "****************************************" << std::endl;

    std::cout << std::endl << "1. View All Employees"
        << std::endl << "2. Look Up Employee"
        << std::endl << "3. Add Employee"
        << std::endl << "4. Remove Employee"
        << std::endl << "5. Edit Employee Salary"
        << std::endl << "0. Exit" << std::endl;
    std::cout << std::endl;
}

void Submenus::employeeSubMenu(int storeID) {
    QueryBuilder dbQuery;
    int choice;

    do {
        printEmployeeUI();
        std::cout << "What would you like to do: ";
        std::cin >> choice;

        system("cls");

        switch (choice) {
        case 1:
            dbQuery.getAllEmployeeInfo(storeID);
            break;
        case 2:
        {
            std::string name;

            std::cout << std::endl << "Enter name of employee to look up: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << std::endl;

            dbQuery.getEmployeeInfoByName(name);
            break;
        }
        case 3:
        {
            std::string name;
            std::string dob;
            double salary;

            std::cout << std::endl << "Enter employee name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << std::endl << "\nEnter employee date of birth (in yyyy-mm-dd format): ";
            std::cin >> dob;
            std::cout << std::endl << "Enter employee salary: ";
            std::cin >> salary;
            std::cout << std::endl;

            dbQuery.insertEmployee(name, dob, salary, storeID);
            break;
        }
        case 4:
        {
            int employeeID;

            std::cout << std::endl << "Enter employee ID of employee to be REMOVED: ";
            std::cin >> employeeID;
            std::cout << std::endl;

            dbQuery.removeEmployee(employeeID, storeID);
            break;
        }
        case 5:
        {
            int employeeID;
            double salary;

            std::cout << std::endl << "Enter Employee ID to change salary: ";
            std::cin >> employeeID;
            std::cout << std::endl << "Enter new salary: ";
            std::cin >> salary;

            dbQuery.updateEmployeeSalary(employeeID, salary, storeID);
            break;
        }
        case 0:
            break;
        default: std::cout << std::endl << "invalid input. Try Again";
        }
    } while (choice != 0);
}
#include <iostream>
#include <string>
#include <iomanip>
#include "Submenus.h"
#include "QueryBuilder.h"


void printEmployeeOwnerUI()
{
    std::string text = "Employees Owner Page";

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
        << std::endl << "6. Promote Employee"
        << std::endl << "7. Demote Employee"
        << std::endl << "0. Exit" << std::endl;
    std::cout << std::endl;
}

void Submenus::ownerEmployeeSubMenu() {
    QueryBuilder dbQuery;
    int choice;

    do {
        printEmployeeOwnerUI();
        std::cout << "What would you like to do: ";
        std::cin >> choice;

        system("cls");

        switch (choice) {
        case 1:
            dbQuery.getAllEmployeeInfo();
            break;
        case 2:
        {
            std::string name;

            std::cout << "Enter name of employee to look up: ";
            std::cin >> name;

            dbQuery.getEmployeeInfoByName(name);
            break;
        }
        case 3:
        {
            int storeID;
            std::string name;
            std::string dob;
            double salary;

            std::cout << std::endl << "Enter store ID of hire: ";
            std::cin >> storeID;
            std::cout << std::endl << "Enter employee name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << std::endl << "Enter employee date of birth (in yyyy-mm-dd format): ";
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

            dbQuery.removeEmployee(employeeID);
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

            dbQuery.updateEmployeeSalary(employeeID, salary);
            break;
        }
        case 6:
        {
            int employeeID;

            std::cout << std::endl << "Enter Employee ID to PROMOTE: ";
            std::cin >> employeeID;

            dbQuery.promoteEmployee(employeeID);
            break;
        }
        case 7:
        {
            int employeeID;

            std::cout << std::endl << "Enter Employee ID to DEMOTE: ";
            std::cin >> employeeID;

            dbQuery.demoteEmployee(employeeID);
            break;
        }
        case 0:
            break;
        default: std::cout << std::endl << "invalid input. Try Again";
        }
    } while (choice != 0);
}
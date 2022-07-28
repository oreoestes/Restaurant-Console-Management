#include <iostream>
#include <iomanip>
#include <pqxx/pqxx>
#include "QueryBuilder.h"
#include "Submenus.h"

void printManagerPortalUI() {
    std::string text = "Manager Portal";

    std::cout << std::endl
        << "****************************************" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "*            " << std::setfill(' ') << std::left << std::setw(26) << text << "*" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "****************************************" << std::endl;

    std::cout << std::endl << "1. Store"
        << std::endl << "2. Employee"
        << std::endl << "3. Orders"
        << std::endl << "4. My Info"
        << std::endl << "0. Exit" << std::endl;
    std::cout << std::endl;
}

void printEmployeePortalUI() {
    std::string text = "Employee Portal";

    std::cout << std::endl
        << "****************************************" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "*          " << std::setfill(' ') << std::left << std::setw(28) << text << "*" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "****************************************" << std::endl;

    std::cout << std::endl << "1. View Restaurant Information"
        << std::endl << "2. View Orders" 
        << std::endl << "3. My Info"
        << std::endl << "0. Exit" << std::endl;
    std::cout << std::endl;
}

int main()
{
    // initialization properties
    std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password=5E#asOL32";
    std::string user;
    std::string pass;
    std::string itemName;
    std::string supplier;
    bool validUser = false;

    int ownerID = 8;

    // current user properties
    int userEmployeeID;
    int userStoreID;
    bool isManager;

    try {
        // Generate a connection with the database and create a transaction to interface with it
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        // Generate a prepared statement to check user credentials
        // Done outside of the while loop so that it is not repeatedly created and disposed, and instead reused when invalid credentials are input
        connectionObject.prepare("loginCheck", "SELECT EmployeeID, Password FROM Accounts WHERE Username = $1");

        // Continually ask for login info until valid credentials are entered
        while (!validUser) {
            std::cout << "Please enter your username: ";
            std::cin >> user;
            std::cout << "Please enter your password: ";
            std::cin >> pass;

            // Run the previously created prepared statement with user parameter
            pqxx::result loginCheck = worker.exec_prepared("loginCheck", user);

            // Check if the given user exists in db and then check if the password is correct
            // Typically the password would be stored encrypted and decryption would happen here but that's really sweaty coding for a school project
            if (loginCheck.size() > 0 && loginCheck[0][1].as<std::string>() == pass) {
                validUser = true;
                userEmployeeID = loginCheck[0][0].as<int>();

                // Pull user data from employees and also check if user is a manager
                std::string query = "SELECT StoreID FROM Employees WHERE EmployeeID = " + std::to_string(userEmployeeID);
                pqxx::row userInfoResult = worker.exec1(query);
                userStoreID = userInfoResult[0].as<int>();

                query = "SELECT COUNT(*) FROM Managers WHERE EmployeeID = " + std::to_string(userEmployeeID);
                userInfoResult = worker.exec1(query);
                isManager = userInfoResult[0].as<int>() > 0;
            }
            else {
                std::cout << std::endl;
                std::cout << "Failed to login. Your username or password were incorrect." << std::endl;
                system("pause");
                system("cls");
            }
        }
        // Exit 
        connectionObject.unprepare("loginCheck");
        connectionObject.close();
        system("cls");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    QueryBuilder dbQuery;
    int choice;

    if (isManager) {
        // Main loop to ask user for instructions and carry them out (for managers)
        do {
            printManagerPortalUI();
            std::cout << "Which submenu would you like to enter? Enter the index of your choice: ";
            std::cin >> choice;

            system("cls");

            if (choice < 0 || choice > 4) {
                std::cout << "Invalid option, please try again.";
                choice = 100;
            }

            switch (choice) {
            case 1:
                if (userEmployeeID == ownerID)
                    Submenus::ownerRestaurantSubMenu();
                else
                    Submenus::restaurantSubMenu(userStoreID);
                break;
            case 2:
                if (userEmployeeID == ownerID)
                    Submenus::ownerEmployeeSubMenu();
                else
                    Submenus::employeeSubMenu(userStoreID);
                break;
            case 3:
                if (userEmployeeID == ownerID)
                    Submenus::ownerOrderSubMenu(userEmployeeID);
                else
                    Submenus::orderSubMenu(userStoreID, userEmployeeID);
                break;
            case 4:
                dbQuery.getManagerInfo(userEmployeeID);
                break;
            case 0:
                std::cout << "Exiting program.";
                exit(0);
                break;
            default:
                break;
            }
        } while (choice > 0);
    }
    else {
        // Employee version
        do {
            printEmployeePortalUI();
            std::cout << "What would you like to do? Enter the index of your choice: ";
            std::cin >> choice;

            system("cls");

            if (choice < 0 || choice > 3) {
                std::cout << "Invalid option, please try again.";
                choice = 100;
            }

            std::cout << std::endl;

            switch (choice) {
            case 1:
                dbQuery.getStoreInfoById(userStoreID);
                break;
            case 2:
                dbQuery.getOrderInfo(userStoreID);
                break;
            case 3:
                dbQuery.getEmployeeInfoById(userEmployeeID);
                break;
            case 0:
                std::cout << "Exiting program.";
                exit(0);
                break;
            default:
                break;
            }
        } while (choice > 0);
    }
}
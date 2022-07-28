#include <iostream>
#include <string>
#include <iomanip>
#include "Submenus.h"
#include "QueryBuilder.h"

void printOrderUI() {
    std::string text = "Orders Page";

    std::cout << std::endl
        << "****************************************" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "*            " << std::setfill(' ') << std::left << std::setw(26) << text << "*" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "****************************************" << std::endl;

    std::cout << std::endl << "1. View All Orders"
        << std::endl << "2. Log New Order"
        << std::endl << "3. View Supplier List"
        << std::endl << "4. Look Up Supplier"
        << std::endl << "0. Exit" << std::endl;
    std::cout << std::endl;
}

void Submenus::orderSubMenu(int storeID, int userID) {
    QueryBuilder dbQuery;
    int choice;

    do {
        printOrderUI();
        std::cout << "What would you like to do: ";
        std::cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
            dbQuery.getOrderInfo(storeID);
            break;
        case 2:
        {
            std::string name;
            double cost;
            int supplierID;

            std::cout << std::endl << "Enter name of item: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "\nEnter total cost of order: ";
            std::cin >> cost;
            std::cout << std::endl << "Enter ID number of supplier: ";
            std::cin >> supplierID;
            std::cout << std::endl;

            dbQuery.insertOrder(name, storeID, supplierID, cost, userID);
            break;
        }
        case 3:
            dbQuery.getAllSupplierInfo();
            break;
        case 4:
        {
            std::string name;

            std::cout << std::endl << "Enter name of supplier to look up: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << std::endl;

            dbQuery.getSupplierInfoByName(name);
            break;
        }
        case 0:
            break;
        default: std::cout << std::endl << "Invalid input. Try Again";
        }
    } while (choice != 0);
}
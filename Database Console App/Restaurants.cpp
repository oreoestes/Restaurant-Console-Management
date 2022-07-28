#include <iostream>
#include <string>
#include <iomanip>
#include "Submenus.h"
#include "QueryBuilder.h"

void printRestaurantUI() {
    std::string text = "Restaurants Page";

    std::cout << std::endl
        << "****************************************" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "*            " << std::setfill(' ') << std::left << std::setw(26) << text << "*" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "****************************************" << std::endl;

    std::cout << std::endl << "1. View Resturant Information"
        << std::endl << "2. View Monthly Profits"
        << std::endl << "3. Change Restaurant Hours"
        << std::endl << "0. Exit" << std::endl;
    std::wcout << std::endl;
}

void Submenus::restaurantSubMenu(int storeID) {
    QueryBuilder dbQuery;
    int choice;

    do {
        printRestaurantUI();
        std::cout << "What would you like to do: ";
        std::cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
            dbQuery.getStoreInfoById(storeID);
            break;
        case 2:
            dbQuery.getProfitInfo(storeID);
            break;
        case 3:
        {
            std::string startTime;
            std::string endTime;

            std::cout << std::endl << "Enter the new opening time in 24 hour format (ex. 17:00): ";
            std::cin >> startTime;
            std::cout << std::endl << "Enter the new closing time in 24 hour format: ";
            std::cin >> endTime;

            dbQuery.updateStoreHours(storeID, startTime, endTime);
            break;
        }
        case 0:
            break;
        default: std::cout << std::endl << "invalid input. Try Again";
        }
    } while (choice != 0);
}
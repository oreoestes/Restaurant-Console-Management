#include <iostream>
#include <string>
#include <iomanip>
#include "Submenus.h"
#include "QueryBuilder.h"

void printRestaurantOwnerUI()
{
    std::string text = "Restaurants Owner Page";

    std::cout << std::endl
        << "****************************************" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "*            " << std::setfill(' ') << std::left << std::setw(26) << text << "*" << std::endl
        << "*                                      *" << std::endl
        << "*                                      *" << std::endl
        << "****************************************" << std::endl;

    std::cout << std::endl << "1. View All Locations"
        << std::endl << "2. Look Up Restaurant ID"
        << std::endl << "3. View Month Profits"
        << std::endl << "4. Create Resturant"
        << std::endl << "5. Remove Resturant"
        << std::endl << "0. Exit" << std::endl;
    std::cout << std::endl;
}
void Submenus::ownerRestaurantSubMenu()
{
    QueryBuilder dbQuery;
    int choice;

    do
    {
        printRestaurantOwnerUI();
        std::cout << std::endl << "What would you like to do: ";
        std::cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
            dbQuery.getAllStoreInfo();//shows row
            break;
        case 2: 
        {
            std::string location;

            std::cout << "Enter location of store to look up: ";
            std::cin.ignore();
            std::getline(std::cin, location);

            dbQuery.getStoreInfoByLocation(location);
            break;
        }
        case 3:
            dbQuery.getProfitInfo();
            break;
        case 4:
        {
            std::string startTime;
            std::string endTime;
            std::string location;

            std::cout << "Enter the opening time in 24 hour format (ex. 17:00): ";//adds to colum
            std::cin >> startTime;
            std::cout << std::endl << "Enter the closing time in 24 hour format: " ;//adds to colum
            std::cin >> endTime;
            std::cout << std::endl << "Enter store location: ";//adds to colum
            std::cin >> location;

            dbQuery.insertStore(startTime, endTime, location);
            break;
        }
        case 5:
        {
            int restaurantID;
            std::cout << std::endl << "Enter Resturant ID to REMOVED: ";// removes row
            std::cin >> restaurantID;

            dbQuery.removeStore(restaurantID);
            break;
        }
        case 0:
            break;
        default: std::cout << std::endl << "invalid input. Try Again";
        }
    } while (choice != 0);
}
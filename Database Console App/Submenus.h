#pragma once

class Submenus {
public:
	static void employeeSubMenu(int storeID);
	static void orderSubMenu(int storeID, int userID);
	static void restaurantSubMenu(int storeID);

	static void ownerEmployeeSubMenu();
	static void ownerOrderSubMenu(int userID);
	static void ownerRestaurantSubMenu();
};
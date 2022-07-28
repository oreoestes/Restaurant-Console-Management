#pragma once

#include <string>

class QueryBuilder {
public:
	QueryBuilder();
	void getAllStoreInfo();
	void getStoreInfoByLocation(std::string location);
	void getStoreInfoById(int storeID);
	void insertStore(std::string startTime, std::string endTime, std::string location);
	void removeStore(int storeID);
	void updateStoreHours(int storeID, std::string startTime, std::string endTime);

	void getProfitInfo();
	void getProfitInfo(int storeID);

	void getAllEmployeeInfo();
	void getAllEmployeeInfo(int storeID);
	void getEmployeeInfoById(int employeeID);
	void getEmployeeInfoByName(std::string employeeName);
	void insertEmployee(std::string name, std::string dob, double salary, int storeID);
	void removeEmployee(int employeeID);
	void removeEmployee(int employeeID, int storeID);
	void promoteEmployee(int employeeID);
	void demoteEmployee(int employeeID);
	void updateEmployeeSalary(int employeeID, double salary);
	void updateEmployeeSalary(int employeeID, double salary, int storeID);

	void getOrderInfo();
	void getOrderInfo(int storeID);
	void insertOrder(std::string itemName, int storeID, int supplierID, double cost, int userID);

	void getAllSupplierInfo();
	void getSupplierInfoByName(std::string supplierName);
	void insertSupplier(std::string name);
	void removeSupplier(int supplierID);

	void getManagerInfo(int employeeID);
private:
	std::string connectionString = "host=localhost port=5432 dbname=postgres user=postgres password=password";
};

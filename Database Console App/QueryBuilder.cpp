#include <sstream>
#include <iostream>
#include <iomanip>
#include <pqxx/pqxx>
#include "QueryBuilder.h"

QueryBuilder::QueryBuilder() {}

void QueryBuilder::getAllStoreInfo() {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT StoreID, Location, StartTime, EndTime FROM Restaurants";
        pqxx::result response = worker.exec(query);

        std::cout << std::left
            << std::setw(16) << "Store ID"
            << std::setw(19) << "Location"
            << std::setw(16) << "StartTime"
            << std::setw(16) << "EndTime" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<int>()
                << std::setw(19) << response[i][1].as<std::string>()
                << std::setw(16) << response[i][2].as<std::string>()
                << std::setw(16) << response[i][3].as<std::string>() << std::endl;
        }
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns generic information about a restaurant
void QueryBuilder::getStoreInfoById(int storeId) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT StoreID, Location, StartTime, EndTime FROM Restaurants WHERE StoreID = " + std::to_string(storeId);
        pqxx::row response = worker.exec1(query);

        std::cout << std::left
            << std::setw(16) << "Store ID"
            << std::setw(19) << "Location"
            << std::setw(16) << "StartTime"
            << std::setw(16) << "EndTime" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(19) << response[1].as<std::string>()
            << std::setw(16) << response[2].as<std::string>()
            << std::setw(16) << response[3].as<std::string>() << std::endl;

        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

void QueryBuilder::getStoreInfoByLocation(std::string location) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT StoreID, Location, StartTime, EndTime FROM Restaurants WHERE StoreID LIKE $1";
        connectionObject.prepare("getStoreByLocation", query);
        pqxx::result response = worker.exec_prepared("getStoreByLocation", "%" + location + "%");

        std::cout << std::left
            << std::setw(16) << "Store ID"
            << std::setw(19) << "Location"
            << std::setw(16) << "StartTime"
            << std::setw(16) << "EndTime" << std::endl;


        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<int>()
                << std::setw(19) << response[i][1].as<std::string>()
                << std::setw(16) << response[i][2].as<std::string>()
                << std::setw(16) << response[i][3].as<std::string>() << std::endl;
        }
        connectionObject.unprepare("getStoreByLocation");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Inserts stuff
void QueryBuilder::insertStore(std::string startTime, std::string endTime, std::string location) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "INSERT INTO Restaurants(location, StartTime, EndTime) "
            "VALUES($1, $2, $3) RETURNING StoreId, Location, StartTime, EndTime";
        connectionObject.prepare("insertStore", query);
        pqxx::row response = worker.exec_prepared1("insertStore", location, startTime, endTime);

        std::cout << std::left
            << std::setw(16) << "Store ID"
            << std::setw(19) << "Location"
            << std::setw(16) << "StartTime"
            << std::setw(16) << "EndTime" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(19) << response[1].as<std::string>()
            << std::setw(16) << response[2].as<std::string>()
            << std::setw(16) << response[3].as<std::string>() << std::endl;

        connectionObject.unprepare("insertStore");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

void QueryBuilder::removeStore(int storeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "DELETE FROM Restaurants WHERE StoreId = $1";
        connectionObject.prepare("removeStore", query);
        worker.exec_prepared0("removeStore", storeID);
        connectionObject.unprepare("removeStore");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Updates the opening and closing times of a restaurant to the given values
void QueryBuilder::updateStoreHours(int storeID, std::string startTime, std::string endTime) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "UPDATE Restaurants SET StartTime = $1, EndTime = $2 WHERE StoreId = $3";
        connectionObject.prepare("updateHours", query);
        worker.exec_prepared0("updateHours", startTime, endTime, storeID);
        worker.commit();

        connectionObject.unprepare("updateHours");
        connectionObject.close();

        std::cout << std::endl << "Successfully updated hours." << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

void QueryBuilder::getAllEmployeeInfo() {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT EmployeeId, Name, Salary, DateOfBirth, StoreId FROM Employees ORDER BY Name ASC";
        pqxx::result response = worker.exec(query);

        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(16) << "Name"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth" 
            << std::setw(16) << "Store ID" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<int>()
                << std::setw(16) << response[i][1].as<std::string>()
                << std::setw(16) << response[i][2].as<double>()
                << std::setw(16) << response[i][3].as<std::string>() 
                << std::setw(16) << response[i][4].as<int>() << std::endl;
        }
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns all records from employee table that are associated with the given store ID
void QueryBuilder::getAllEmployeeInfo(int storeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT EmployeeId, Name, Salary, DateOfBirth FROM Employees "
            "WHERE StoreId = " + std::to_string(storeID) + " ORDER BY Name ASC";
        pqxx::result response = worker.exec(query);

        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(16) << "Name"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<int>()
                << std::setw(16) << response[i][1].as<std::string>()
                << std::setw(16) << response[i][2].as<double>()
                << std::setw(16) << response[i][3].as<std::string>() << std::endl;
        }
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns all records from employee table with the given string in their name
void QueryBuilder::getEmployeeInfoByName(std::string employeeName) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT EmployeeId, Name, Salary, DateOfBirth, StoreId FROM Employees "
            "WHERE Name LIKE $1 ORDER BY Name ASC";
        connectionObject.prepare("getEmployeeByName", query);
        pqxx::result response = worker.exec_prepared("getEmployeeByName", "%" + employeeName + "%");

        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(16) << "Name"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth"
            << std::setw(16) << "Store ID" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<int>()
                << std::setw(16) << response[i][1].as<std::string>()
                << std::setw(16) << response[i][2].as<double>()
                << std::setw(16) << response[i][3].as<std::string>()
                << std::setw(16) << response[i][4].as<int>() << std::endl;
        }
        connectionObject.unprepare("getEmployeeByName");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns a record from employee table with the given employee ID
void QueryBuilder::getEmployeeInfoById(int employeeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT EmployeeId, Name, Salary, DateOfBirth, StoreId FROM Employees "
            "WHERE EmployeeId = " + std::to_string(employeeID) + " ORDER BY Name ASC";
        pqxx::result response = worker.exec(query);

        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(16) << "Name"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth"
            << std::setw(16) << "Store ID" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<int>()
                << std::setw(16) << response[i][1].as<std::string>()
                << std::setw(16) << response[i][2].as<double>()
                << std::setw(16) << response[i][3].as<std::string>()
                << std::setw(16) << response[i][4].as<int>() << std::endl;
        }
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Inserts an employee to employee table with given values and prints the inserted record
void QueryBuilder::insertEmployee(std::string name, std::string dob, double salary, int storeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "INSERT INTO Employees(Name, Salary, DateOfBirth, StoreId) "
            "VALUES($1, $2, $3, $4) "
            "RETURNING EmployeeId, Name, Salary, DateOfBirth, StoreId";
        connectionObject.prepare("insertEmployee", query);
        pqxx::row response = worker.exec_prepared1("insertEmployee", name, salary, dob, storeID);
        worker.commit();

        std::cout << "Successfully added:" << std::endl;
        std::cout << std::endl;

        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(16) << "Name"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth"
            << std::setw(16) << "Store ID" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(16) << response[1].as<std::string>()
            << std::setw(16) << response[2].as<double>()
            << std::setw(16) << response[3].as<std::string>() 
            << std::setw(16) << response[4].as<int>() << std::endl;

        connectionObject.unprepare("insertEmployee");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Removes an employee from employee table and prints the deleted record
void QueryBuilder::removeEmployee(int employeeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "DELETE FROM Employees WHERE EmployeeId = $1 RETURNING EmployeeId, Name, Salary, DateOfBirth, StoreId";
        connectionObject.prepare("deleteEmployee", query);
        pqxx::row response = worker.exec_prepared1("deleteEmployee", employeeID);
        worker.commit();

        std::cout << "Successfully deleted:" << std::endl;
        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(19) << "Name"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth" 
            << std::setw(16) << "Store ID" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(19) << response[1].as<std::string>()
            << std::setw(16) << response[2].as<double>()
            << std::setw(16) << response[3].as<std::string>() 
            << std::setw(16) << response[4].as<int>() << std::endl;

        connectionObject.unprepare("deleteEmployee");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Removes an employee from employee table and prints the deleted record
// Store ID is a parameter to ensure managers cannot fire workers of other locations
void QueryBuilder::removeEmployee(int employeeID, int storeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "DELETE FROM Employees WHERE EmployeeId = $1 AND StoreId = $2 RETURNING EmployeeId, Name, Salary, DateOfBirth";
        connectionObject.prepare("deleteEmployee", query);
        pqxx::row response = worker.exec_prepared1("deleteEmployee", employeeID, storeID);
        worker.commit();

        std::cout << "Successfully deleted:" << std::endl;
        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(16) << "Name"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(16) << response[1].as<std::string>()
            << std::setw(16) << response[2].as<double>()
            << std::setw(16) << response[3].as<std::string>() << std::endl;

        connectionObject.unprepare("deleteEmployee");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

void QueryBuilder::promoteEmployee(int employeeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "INSERT INTO Managers VALUES($1, current_date)";
        connectionObject.prepare("insertManager", query);
        worker.exec_prepared0("insertManager", employeeID);
        worker.commit();

        connectionObject.unprepare("insertManager");
        connectionObject.close();

        std::cout << "Promotion successful." << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

void QueryBuilder::demoteEmployee(int employeeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "DELETE FROM Managers WHERE EmployeeId = $1";
        connectionObject.prepare("removeManager", query);
        worker.exec_prepared0("removeManager", employeeID);
        worker.commit();

        connectionObject.unprepare("removeManager");
        connectionObject.close();

        std::cout << "Demotion successful." << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Updates the salary of a given employee and prints the updated record
void QueryBuilder::updateEmployeeSalary(int employeeID, double salary) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "UPDATE Employees SET Salary = $1 WHERE EmployeeId = $2 "
            "RETURNING EmployeeId, Name, Salary, DateOfBirth";
        connectionObject.prepare("employeeSalary", query);
        pqxx::row response = worker.exec_prepared1("employeeSalary", salary, employeeID);
        worker.commit();

        std::cout << "Successfully updated:" << std::endl;
        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(16) << "Name"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(16) << response[1].as<std::string>()
            << std::setw(16) << response[2].as<double>()
            << std::setw(16) << response[3].as<std::string>() << std::endl;

        connectionObject.unprepare("employeeSalary");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Updates the salary of a given employee and prints the updated record
// Store ID is a parameter to ensure managers cannot raise the pay of workers of other locations
void QueryBuilder::updateEmployeeSalary(int employeeID, double salary, int storeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "UPDATE Employees SET Salary = $1 WHERE EmployeeId = $2 AND StoreId = $3 "
            "RETURNING EmployeeId, Name, Salary, DateOfBirth";
        connectionObject.prepare("employeeSalary", query);
        pqxx::row response = worker.exec_prepared1("employeeSalary", salary, employeeID, storeID);
        worker.commit();

        std::cout << "Successfully updated:" << std::endl;
        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(16) << "Name"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(16) << response[1].as<std::string>()
            << std::setw(16) << response[2].as<double>()
            << std::setw(16) << response[3].as<std::string>() << std::endl;

        connectionObject.unprepare("employeeSalary");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns all records from the orders table that are associated with the given store ID sorted by date
void QueryBuilder::getOrderInfo() {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT o.ItemName, r.Location, s.Name AS Supplier, o.Cost, e.Name, o.Date "
            "FROM Orders o JOIN Employees e ON o.OrderedBy = e.employeeId "
            "JOIN Suppliers s ON o.supplier = s.supplierId " 
            "JOIN Restaurants r ON o.StoreId = r.StoreId "
            "ORDER BY Date DESC";
        pqxx::result response = worker.exec(query);

        std::cout << std::left
            << std::setw(18) << "Item Name"
            << std::setw(18) << "Location"
            << std::setw(18) << "Supplier"
            << std::setw(16) << "Cost"
            << std::setw(16) << "Ordered By"
            << std::setw(16) << "Date Ordered" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(18) << response[i][0].as<std::string>()
                << std::setw(18) << response[i][1].as<std::string>()
                << std::setw(18) << response[i][2].as<std::string>()
                << std::setw(16) << response[i][3].as<double>()
                << std::setw(16) << response[i][4].as<std::string>()
                << std::setw(16) << response[i][5].as<std::string>() << std::endl;
        }
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns all records from the orders table that are associated with the given store ID sorted by date
void QueryBuilder::getOrderInfo(int storeId) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT o.ItemName, s.Name AS Supplier, o.Cost, e.Name as OrderedBy, o.Date "
            "FROM Orders o JOIN Employees e ON o.OrderedBy = e.employeeId "
            "JOIN Suppliers s ON o.supplier = s.supplierId "
            "WHERE o.StoreId = " + std::to_string(storeId) + " ORDER BY Date DESC";
        pqxx::result response = worker.exec(query);

        std::cout << std::left
            << std::setw(16) << "Item Name"
            << std::setw(18) << "Supplier"
            << std::setw(16) << "Cost"
            << std::setw(16) << "Ordered By"
            << std::setw(16) << "Date Ordered" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<std::string>()
                << std::setw(18) << response[i][1].as<std::string>()
                << std::setw(16) << response[i][2].as<double>()
                << std::setw(16) << response[i][3].as<std::string>()
                << std::setw(16) << response[i][4].as<std::string>() << std::endl;
        }
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Inserts an order to order table with given values and prints the inserted record
void QueryBuilder::insertOrder(std::string itemName, int storeID, int supplierID, double cost, int userID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "INSERT INTO Orders VALUES($1, $2, $3, $4, $5, current_date) "
            "RETURNING ItemName, Supplier, Cost, Date";
        connectionObject.prepare("insertOrder", query);
        pqxx::row response = worker.exec_prepared1("insertOrder", itemName, storeID, supplierID, cost, userID);
        worker.commit();

        std::cout << "Successfully logged: " << std::endl;
        std::cout << std::left
            << std::setw(16) << "Item Name"
            << std::setw(18) << "Supplier ID"
            << std::setw(16) << "Cost"
            << std::setw(16) << "Date Ordered" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<std::string>()
            << std::setw(18) << response[1].as<std::string>()
            << std::setw(16) << response[2].as<double>()
            << std::setw(16) << response[3].as<std::string>() << std::endl;

        connectionObject.unprepare("insertOrder");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns a list of all suppliers in the suppliers table
void QueryBuilder::getAllSupplierInfo() {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT SupplierID, Name FROM Suppliers ORDER BY Name ASC";
        pqxx::result response = worker.exec(query);

        std::cout << std::left
            << std::setw(16) << "Supplier ID"
            << std::setw(16) << "Name" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<int>()
                << std::setw(16) << response[i][1].as<std::string>() << std::endl;
        }
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns all records from supplier table with the given string in their name
void QueryBuilder::getSupplierInfoByName(std::string supplierName) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT SupplierId, Name FROM Suppliers WHERE Name LIKE $1";
        connectionObject.prepare("getSupplierByName", query);
        pqxx::result response = worker.exec_prepared("getSupplierByName", "%" + supplierName + "%");

        std::cout << std::left
            << std::setw(16) << "Supplier ID"
            << std::setw(16) << "Name" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<int>()
                << std::setw(16) << response[i][1].as<std::string>() << std::endl;
        }
        connectionObject.unprepare("getSupplierByName");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

void QueryBuilder::insertSupplier(std::string supplierName) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "INSERT INTO Suppliers(Name) VALUES($1) RETURNING SupplierId, Name";
        connectionObject.prepare("insertSupplier", query);
        pqxx::row response = worker.exec_prepared1("insertSupplier", supplierName);
        worker.commit();

        std::cout << std::left
            << std::setw(16) << "Supplier ID"
            << std::setw(16) << "Name" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(16) << response[1].as<std::string>() << std::endl;

        connectionObject.unprepare("insertSupplier");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

void QueryBuilder::removeSupplier(int supplierID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "DELETE FROM Suppliers WHERE SupplierId = $1 RETURNING SupplierId, Name";
        connectionObject.prepare("removeSupplier", query);
        pqxx::row response = worker.exec_prepared1("removeSupplier", supplierID);
        worker.commit();

        std::cout << std::left
            << std::setw(16) << "Supplier ID"
            << std::setw(16) << "Name" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(16) << response[1].as<std::string>() << std::endl;

        connectionObject.unprepare("removeSupplier");
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns a record from employee table along with promotion date
void QueryBuilder::getManagerInfo(int employeeID) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT e.EmployeeId, e.Name, m.Promoted, e.Salary, e.DateOfBirth, e.StoreID FROM Employees e "
            "INNER JOIN Managers m ON e.EmployeeID = m.EmployeeID "
            "WHERE e.EmployeeID = " + std::to_string(employeeID);
        pqxx::row response = worker.exec1(query);

        std::cout << std::left
            << std::setw(16) << "Employee ID"
            << std::setw(16) << "Name"
            << std::setw(16) << "Promoted On"
            << std::setw(16) << "Salary"
            << std::setw(16) << "Date Of Birth"
            << std::setw(16) << "Store ID" << std::endl;

        std::cout << std::left
            << std::setw(16) << response[0].as<int>()
            << std::setw(16) << response[1].as<std::string>()
            << std::setw(16) << response[2].as<std::string>()
            << std::setw(16) << response[3].as<float>()
            << std::setw(16) << response[4].as<std::string>()
            << std::setw(16) << response[5].as<int>() << std::endl;

        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

void QueryBuilder::getProfitInfo() {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT StoreId, RecordedOn, Upkeep, Sales FROM Profits ORDER BY RecordedOn DESC, StoreId ASC";
        pqxx::result response = worker.exec(query);

        std::cout << std::left
            << "Monthly profits:" << std::endl
            << std::setw(16) << "Store ID"
            << std::setw(16) << "Date"
            << std::setw(16) << "Upkeep"
            << std::setw(16) << "Sales"
            << std::setw(16) << "Total profit" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<int>()
                << std::setw(16) << response[i][1].as<std::string>()
                << std::setw(16) << response[i][2].as<double>()
                << std::setw(16) << response[i][3].as<double>()
                << std::setw(16) << (response[i][3].as<double>() - response[i][2].as<double>()) << std::endl;
        }
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}

// Returns all records from profits table sorted by date
void QueryBuilder::getProfitInfo(int storeId) {
    try {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);

        std::string query = "SELECT RecordedOn, Upkeep, Sales FROM Profits WHERE StoreID = " + std::to_string(storeId) + " ORDER BY RecordedOn DESC";
        pqxx::result response = worker.exec(query);

        std::cout << std::left
            << "Monthly profits:" << std::endl
            << std::setw(16) << "Date"
            << std::setw(16) << "Upkeep"
            << std::setw(16) << "Sales"
            << std::setw(16) << "Total profit" << std::endl;

        for (int i = 0; i < response.size(); i++) {
            std::cout << std::left
                << std::setw(16) << response[i][0].as<std::string>()
                << std::setw(16) << response[i][1].as<double>()
                << std::setw(16) << response[i][2].as<double>()
                << std::setw(16) << (response[i][2].as<double>() - response[i][1].as<double>()) << std::endl;
        }
        connectionObject.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    system("pause");
    system("cls");
}
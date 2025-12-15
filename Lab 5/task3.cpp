#include <iostream>
#include <string>

using namespace std;

class CEmployee{
    private:
        string name;
        int id;
        int salary;
    public:
        void setName(string empName) {
            name = empName;
        }
        string getName() {
            return name;
        }
        void setId(int empId) {
            id = empId;
        }
        int getId() {
            return id;
        }
        void setSalary(int empSalary) {
            salary = empSalary;
        }
        int getSalary() {
            return salary;
        }
};

class CEmployeeFunction {
    private:
        string department;
        bool isManager;
    public:
        void setDepartment(string dept) {
            department = dept;
        }
        string getDepartment() {
            return department;
        }
        void setIsManager(bool managerStatus) {
            isManager = managerStatus;
        }
        bool getIsManager() {
            return isManager;
        }
};

int main() {
    int toSender = 0;
    return toSender;
}
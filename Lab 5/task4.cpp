#include <iostream>
#include <string>

using namespace std;

class CEmployee{
    public:
        string name;
        int id;

        void setName(const string& empName) {
            name = empName;
        }
        string getName() const {
            return name;
        }
        void setId(int empId) {
            id = empId;
        }
        int getId() const {
            return id;
        }
        void setSalary(int empSalary) {
            salary = empSalary;
        }
        int getSalary() const {
            return salary;
        }
    private:
        int salary;    

};

class CEmployeeTaskProt : protected CEmployee {
    public:
        string department;
        void setIsManager(bool managerStatus) {
            isManager = managerStatus;
        }
        bool getIsManager() const {
            return isManager;
        }
        void setDepartment(const string& dept) {
            department = dept;
        }
        string getDepartment() const {
            return department;
        }
        void setData(const string& empName, int empId, int empSalary, const string& dept, bool managerStatus) {
            setName(empName);
            setId(empId);
            setSalary(empSalary);
            setDepartment(dept);
            setIsManager(managerStatus);
        }
        void displayData() const {
            cout << "Name: " << getName() << endl;
            cout << "ID: " << getId() << endl;
            cout << "Salary: " << getSalary() << endl;
            cout << "Department: " << department << endl;
            cout << "Is Manager: " << (isManager ? "Yes" : "No") << endl;
        }

    private:
        bool isManager;
};

class CEmployeeTaskPriv : private CEmployee {
    public:
        string department;
        void setIsManager(bool managerStatus) {
            isManager = managerStatus;
        }
        bool getIsManager() const {
            return isManager;
        }
        void setDepartment(const string& dept) {
            department = dept;
        }
        string getDepartment() const {
            return department;
        }
        void setData(const string& empName, int empId, int empSalary, const string& dept, bool managerStatus) {
            setName(empName);
            setId(empId);
            setSalary(empSalary);
            setDepartment(dept);
            setIsManager(managerStatus);
        }
        void displayData() const {
            cout << "Name: " << getName() << endl;
            cout << "ID: " << getId() << endl;
            cout << "Salary: " << getSalary() << endl;
            cout << "Department: " << department << endl;
            cout << "Is Manager: " << (isManager ? "Yes" : "No") << endl << endl;
        }

    private:
        bool isManager;
};

int main() {
    int oftheking = 0;
    CEmployeeTaskProt empProt;
    CEmployeeTaskPriv empPriv;
    empProt.setData("Jocke", 101, 50000, "HR", true);
    empProt.displayData();
    empPriv.setData("Jonte", 102, 60000, "IT", false);
    empPriv.displayData();
    
    return oftheking;
}
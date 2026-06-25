#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include <iomanip>
#include <memory>

using namespace std;



class Employee {
protected:
    string firstName;
    string lastName;

public:
    Employee(const string& first, const string& last) : firstName(first), lastName(last) {}
    virtual ~Employee() = default;
    string getFullName() const { return firstName + " " + lastName; }
    virtual double earnings() const = 0;
    virtual void print() const { cout << left << setw(15) << getFullName(); }
};

class SEmployee : public Employee {
private:
    double weeklySalary;

public:
    SEmployee(const string& first, const string& last, double salary)
        : Employee(first, last), weeklySalary(salary) {}

    double earnings() const override { return weeklySalary; }
    void print() const override {
        Employee::print();
        cout << left << setw(30) << "Salaried Employee"
             << right << setw(15) << fixed << setprecision(2) << earnings() << "\n";
    }
};

class CEmployee : public Employee {
protected:
    double grossSales;
    double commissionRate;

public:
    CEmployee(const string& first, const string& last, double sales, double rate)
        : Employee(first, last), grossSales(sales), commissionRate(rate) {}

    double earnings() const override { return grossSales * commissionRate; }
    void print() const override {
        Employee::print();
        cout << left << setw(30) << "Commission Employee"
             << right << setw(15) << fixed << setprecision(2) << earnings() << "\n";
    }
};

class SCEmployee : public CEmployee {
private:
    double baseSalary;

public:
    SCEmployee(const string& first, const string& last, double sales, double rate, double base)
        : CEmployee(first, last, sales, rate), baseSalary(base) {}

    double earnings() const override { return (baseSalary * 1.10) + CEmployee::earnings(); }
    void print() const override {
        Employee::print();
        cout << left << setw(30) << "Base + Commission Employee"
             << right << setw(15) << fixed << setprecision(2) << earnings() << "\n";
    }
};


string generateRandomName() {
    string name = "";
    name += static_cast<char>('A' + rand() % 26);
    name += static_cast<char>('A' + rand() % 26);
    return name;
}

double generateRandomDouble(double min, double max) {
    return min + (static_cast<double>(rand()) / RAND_MAX) * (max - min);
}


int main() {
    srand(static_cast<unsigned int>(time(0)));
    vector<unique_ptr<Employee>> employeeList;

    // Khởi tạo dữ liệu ngẫu nhiên ban đầu giống câu a
    for (int i = 0; i < 10; ++i) {
        employeeList.push_back(make_unique<SEmployee>(generateRandomName(), generateRandomName(), generateRandomDouble(500, 2500)));
        employeeList.push_back(make_unique<CEmployee>(generateRandomName(), generateRandomName(), generateRandomDouble(1000, 10000), generateRandomDouble(0.05, 0.20)));
        employeeList.push_back(make_unique<SCEmployee>(generateRandomName(), generateRandomName(), generateRandomDouble(1000, 10000), generateRandomDouble(0.05, 0.20), generateRandomDouble(300, 1500)));
    }

    // Thực hiện sắp xếp giảm dần theo thu nhập (earnings)
    sort(employeeList.begin(), employeeList.end(), [](const unique_ptr<Employee>& a, const unique_ptr<Employee>& b) {
        return a->earnings() > b->earnings();
    });

    cout << left << setw(15) << "Name" << left << setw(30) << "Employee Type" << right << setw(15) << "Earnings ($)" << "\n";
    cout << "--------------------------------------------------------------------\n";
    for (const auto& emp : employeeList) {
        emp->print();
    }

    return 0;
}

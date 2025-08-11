#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

const string DATA_FILE = "employees.dat";
const string INDEX_FILE = "index.dat";
const int RECORD_SIZE = 100;

struct Employee {
    string id;
    string name;
    string designation;
    float salary;

    string serialize() const {
        string record = id + "|" + name + "|" + designation + "|" + to_string(salary);
        record.resize(RECORD_SIZE, '#'); // pad with # for fixed size
        return record;
    }

    static Employee deserialize(const string& record) {
        Employee emp;
        size_t pos1 = record.find('|');
        size_t pos2 = record.find('|', pos1 + 1);
        size_t pos3 = record.find('|', pos2 + 1);

        emp.id = record.substr(0, pos1);
        emp.name = record.substr(pos1 + 1, pos2 - pos1 - 1);
        emp.designation = record.substr(pos2 + 1, pos3 - pos2 - 1);
        emp.salary = stof(record.substr(pos3 + 1));
        return emp;
    }
};

map<string, int> loadIndex() {
    map<string, int> index;
    ifstream fin(INDEX_FILE);
    string id;
    int pos;
    while (fin >> id >> pos) {
        index[id] = pos;
    }
    return index;
}

void saveIndex(const map<string, int>& index) {
    ofstream fout(INDEX_FILE);
    for (const auto& pair : index) {
        fout << pair.first << " " << pair.second << "\n";
    }
}

void addEmployee() {
    auto index = loadIndex();
    Employee emp;

    cout << "Enter Employee ID: ";
    cin >> emp.id;
    if (index.find(emp.id) != index.end()) {
        cout << "Employee ID already exists.\n";
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, emp.name);
    cout << "Enter Designation: ";
    getline(cin, emp.designation);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    ofstream fout(DATA_FILE, ios::app | ios::binary);
    int position = fout.tellp();
    string data = emp.serialize();
    fout.write(data.c_str(), RECORD_SIZE);
    fout.close();

    index[emp.id] = position;
    saveIndex(index);
    cout << "Employee added successfully.\n";
}

void deleteEmployee() {
    auto index = loadIndex();
    string emp_id;
    cout << "Enter Employee ID to delete: ";
    cin >> emp_id;

    if (index.erase(emp_id)) {
        saveIndex(index);
        cout << "Employee removed from index.\n";
    } else {
        cout << "Employee does not exist.\n";
    }
}

void displayEmployee() {
    auto index = loadIndex();
    string emp_id;
    cout << "Enter Employee ID to display: ";
    cin >> emp_id;

    if (index.find(emp_id) == index.end()) {
        cout << "Employee does not exist.\n";
        return;
    }

    int position = index[emp_id];
    ifstream fin(DATA_FILE, ios::binary);
    fin.seekg(position);
    char buffer[RECORD_SIZE];
    fin.read(buffer, RECORD_SIZE);
    string record(buffer, RECORD_SIZE);
    fin.close();

    Employee emp = Employee::deserialize(record);
    cout << "\nEmployee Details:\n";
    cout << "ID: " << emp.id << "\n";
    cout << "Name: " << emp.name << "\n";
    cout << "Designation: " << emp.designation << "\n";
    cout << "Salary: " << emp.salary << "\n";
}

int main() {
    while (true) {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: deleteEmployee(); break;
            case 3: displayEmployee(); break;
            case 4: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
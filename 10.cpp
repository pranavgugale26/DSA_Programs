#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Patient 
{
    string name;
    int priority;

    Patient(string n, int p) : name(n), priority(p) {}

    bool operator<(const Patient& other) const 
    {
        return priority > other.priority;
    }
};

int main() 
{
    priority_queue<Patient> pq;
    int choice;

    do 
    {
        cout << "\nHospital Queue Menu:\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Display Queue Size\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) 
        {
            case 1: 
            {
                string name;
                int p;
                cout << "Enter patient name: ";
                cin >> name;
                cout << "Enter condition:\n";
                cout << "1. Serious\n2. Non-Serious\n3. General Checkup\n";
                cin >> p;

                if (p < 1 || p > 3) 
                {
                    cout << "Invalid priority.\n";
                } 
                else 
                {
                    pq.push(Patient(name, p));
                    cout << "Patient added to queue.\n";
                }
                break;
            }
            case 2:
                if (pq.empty()) 
                {
                    cout << "No patients in queue.\n";
                } else 
                {
                    Patient top = pq.top();
                    pq.pop();
                    cout << "Serving patient: " << top.name << " (Priority " << top.priority << ")\n";
                }
                break;
            case 3:
                cout << "Current queue size: " << pq.size() << endl;
                break;
            case 4:
                cout << "Exiting system.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}

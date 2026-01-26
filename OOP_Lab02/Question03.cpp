#include<iostream>
#include<string>
#include<cstring>
using namespace std;
class Employee{
	private:
		char *first_name;
		string last_name;
		int salary;
		
	public:
	    Employee(char* fname, string lname, int monthlysal){
        first_name = new char[strlen(fname) + 1];
        strcpy(first_name, fname);
        last_name = lname;
        if (monthlysal > 0)
            salary = monthlysal;
        else
            salary = 0;
        }
        
        char* getFirstName(){
            return first_name;
        }

         string getLastName(){
            return last_name;
        }

        int getMonthlySalary(){
            return salary;
        }

        int getYearlySalary(){
            return salary * 12;
        }

        void giveRaise(){
            salary = salary + (salary * 10 / 100);
        }

        ~Employee(){
            delete[] first_name;
        }
};
int main()
{
    Employee e1((char*)"John", "Doe", 3000);
    Employee e2((char*)"Jane", "Smith", 4000);

    cout << "Before Raise:\n";
    cout << e1.getFirstName() << " " << e1.getLastName()
         << " Yearly Salary: " << e1.getYearlySalary() << endl;

    cout << e2.getFirstName() << " " << e2.getLastName()
         << " Yearly Salary: " << e2.getYearlySalary() << endl;

    e1.giveRaise();
    e2.giveRaise();

    cout << "\nAfter 10% Raise:\n";
    cout << e1.getFirstName() << " " << e1.getLastName()
         << " Yearly Salary: " << e1.getYearlySalary() << endl;

    cout << e2.getFirstName() << " " << e2.getLastName()
         << " Yearly Salary: " << e2.getYearlySalary() << endl;

    return 0;
}




		
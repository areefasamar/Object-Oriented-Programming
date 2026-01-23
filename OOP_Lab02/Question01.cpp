#include<iostream>
#include<string>
using namespace std;
class Student{
	public:
		string name;
		int roll_no;
		int semester;
		char section;
	
	    Student(string n, int r, int sem, int sec){
	    	name = n;
	    	roll_no = r;
	    	semester = sem;
	    	section = sec;
		}
		
	    void display(){
		    cout<<"Name: "<<name<<endl;
		    cout<<"Roll No: "<<roll_no<<endl;
		    cout<<"Semester: "<<semester<<endl;
		    cout<<"Section: "<<section<<endl<<endl;
	    }			
};
int main(){

	Student s1("Areefa", 101, 3, 'A');
    Student s2("Saita", 102, 3, 'B');
    Student s3("Amna", 103, 2, 'A');
    Student s4("Ayesha", 104, 1, 'C');
    
    cout<<"------Section 'A' Student Information------"<<endl<<endl;
    if (s1.section == 'A'){
	    s1.display();
	}
    if (s2.section == 'A'){
	    s2.display();
	}
	if (s3.section == 'A'){
	    s3.display();
	}
	if (s4.section == 'A'){
	    s4.display();
	}
    return 0;

}

#include<iostream>
using namespace std;
int main(){
	int rollnum;
	float marks[5];
	float total=0;
	float percentage;
	
	cout<<"Enter Roll Number:";
	cin>>rollnum;
	
	cout<<"\nEnter Marks:"<<endl;
	for ( int i=0 ; i<5 ; i++){
		cout<<"Enter "<<i+1<<" Subject Marks:";
		cin>>marks[i];
		total += marks[i];
	}
	
	percentage = (total/500) * 100;
	
	cout<<"\nTotal Marks: "<<total<<endl;
	cout<<"Percentage: "<<percentage<<endl;
	return 0;
	
}
#include<iostream>
using namespace std;
int main(){
	int *num1, *num2, *num3;
	int a, b, c, temp;
	
	cout<<"Enter Number 01:";
	cin>>a;
	
	cout<<"Enter Number 02:";
	cin>>b;
	
	cout<<"Enter Number 03:";
	cin>>c;
	
	num1=&a;
	num2=&b;
	num3=&c;
	
	temp = *num1;
	*num1 = *num2;
	*num2 = *num3;
	*num3 = temp;
	
	cout<<"\nSwapped Numbers:"<<endl;
	cout<<"Number 01: "<<a<<endl;
	cout<<"Number 02: "<<b<<endl;
	cout<<"Number 03: "<<c<<endl;
	return 0;
}

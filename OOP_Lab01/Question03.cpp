#include<iostream>
using namespace std;
int main(){
	float fahrenheit, celsius;
	cout << "Enter Temperature (in Fahrenheit): ";
	cin >> fahrenheit;
	
	celsius = (fahrenheit - 32) / 1.8;
	
	cout<<"Temperature in Celsius: "<< celsius << endl;
	return 0;
	
}
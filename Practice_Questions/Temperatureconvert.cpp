#include<iostream>
#include<iomanip>
using namespace std;
class Celsius{
	private:
		float fahrenheit;
	public:
	
	Celsius(float f): fahrenheit(f){
		
	}
	
	float convert(){
		float celsius;
		celsius = (fahrenheit - 32 )/ 1.8 ;
		return celsius;
	}
	
	~Celsius(){
	}	
};
int main(){
	float fah;
	cout<<"Enter the Temperature in Fahrenheit: ";
	cin>>fah;
	
	Celsius c(fah);
	cout<<fixed<<setprecision(3);
	cout<<"Temperature in Celcius: ";
	cout<<c.convert();
	return 0;
}
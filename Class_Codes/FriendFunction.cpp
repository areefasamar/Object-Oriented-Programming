#include<iostream>
using namespace std;
class complex{
	int real, imag;
	public:
		complex(int r=0, int i=0): real(r), imag(i){
		}
		void display();
		
//		complex operator+(complex ob1){
//				return complex(real+ob1.real, imag+ob1.imag);
//		}

		friend complex Add(complex ob1, complex ob2);
		friend complex operator+(complex ob1, complex ob2);
};
complex Add(complex ob1, complex ob2){
	return complex(ob1.real+ob2.real, ob1.imag+ob2.imag);
}
void complex::display(){
	cout<<"Real: "<<real<<" "<<"Imaginary:"<<imag<<endl;
}

complex operator+(complex ob1, complex ob2){
	return complex(ob1.real+ob2.real, ob1.imag+ob2.imag);
}
int main(){
	complex c1(2,3), c2(3,3), c3;
    c3 = c1+c2;
	c3.display();
	return 0;
}
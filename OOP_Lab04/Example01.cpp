#include<iostream>
using namespace std;

class example{
private:
    int x;
public:
    void set(int x){
        (*this).x = x;
    }
    int get( ){
        return x;
    }
    void printAddressAndValue( ){
        cout << "The address is "<<this<<"and the value is "<<(*this).x<<endl;
    }
};

int main(){
    example obj1, obj2;
    obj1.set(7);
    obj1.printAddressAndValue();
    obj2.set(10);
    obj2.printAddressAndValue();
    return 0;
}

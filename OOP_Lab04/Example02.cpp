#include<iostream>
using namespace std;

class Test{
private:
    int x;
    int y;
public:
    Test(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }
    void print( ){
        cout<<"x="<<x<<" y="<< y <<endl;
    }
};

int main( ){
    Test obj1(10, 20);
    obj1.print( );
}

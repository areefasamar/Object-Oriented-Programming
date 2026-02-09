#include <iostream>
using namespace std;

class Demo{
private:
    static int x;
public:
    static void fun( ){
        cout<<"value of X: " << x << endl;
    }
};

//defining
int Demo::x = 10;

int main( ){
    Demo X;
    X.fun( );
    return 0;
}

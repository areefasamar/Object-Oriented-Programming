#include<iostream>
using namespace std;

class beta; // Forward declaration

class alpha{
    private:
        int data;

    public:
        alpha() : data(3) { }

        // Friend function declaration
        friend int frifunc(alpha, beta);
};

class beta{
    private:
        int data;

    public:
        beta() : data(7) { }

        // Friend function declaration
        friend int frifunc(alpha, beta);
};

// Function definition accessing private data from both classes
int frifunc(alpha a, beta b){
    return(a.data + b.data);
}

int main(){
    alpha aa;
    beta bb;

    cout << frifunc(aa, bb) << endl;

    return 0;
}
#include <iostream>
using namespace std;

class Base {
private:
    int privateInt;

protected:
    int protectedInt;

public:
    int publicInt;

    void setPrivate(int x) { 
	    privateInt = x; 
	}
	
    int getPrivate() const { 
	    return privateInt; 
	}

    void setProtected(int x) { 
	    protectedInt = x; 
	}
	
    int getProtected() const { 
	    return protectedInt; 
	}

    void setPublic(int x) { 
	    publicInt = x; 
	}
	
    int getPublic() const { 
	    return publicInt; 
	}
};

class publicChild : public Base {
public:
    void showAccess() {
        protectedInt = 20;
        publicInt = 30;

        cout << "publicChild Access:" << endl;
        cout << "Protected accessed directly: " << protectedInt << endl;
        cout << "Public accessed directly: " << publicInt << endl;
        cout << "Private accessed using getter: " << getPrivate() << endl;
    }
};

class protectedChild : protected Base {
public:
	void setValue(int x) { 
	    setPrivate(x); 
	}
	
    void showAccess() {
        protectedInt = 40;
        publicInt = 50;

        cout << "\nprotectedChild Access:" << endl;
        cout << "Protected accessed directly: " << protectedInt << endl;
        cout << "Public accessed directly (now protected): " << publicInt << endl;
        cout << "Private accessed using getter: " << getPrivate() << endl;
    }
};

class privateChild : private Base {
public:
	void setValue(int x) { 
	    setPrivate(x); 
	}
	
    void showAccess() {
        protectedInt = 60;
        publicInt = 70;

        cout << "\nprivateChild Access:" << endl;
        cout << "Protected accessed directly: " << protectedInt << endl;
        cout << "Public accessed directly (now private): " << publicInt << endl;
        cout << "Private accessed using getter: " << getPrivate() << endl;
    }
};

int main() {
    publicChild obj1;
    obj1.setPrivate(10);
    obj1.showAccess();
    cout << "Accessing publicInt directly from object: " << obj1.publicInt << endl;

    protectedChild obj2;
    obj2.setValue(15);
    obj2.showAccess();
    // obj2.publicInt;  // Not accessible outside

    privateChild obj3;
    obj3.setValue(25);
    obj3.showAccess();
    // obj3.publicInt;  // Not accessible outside

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

class Shape {
private:
    const int id;
    static int counter; // Static counter to automatically assign IDs

public:
    // Automatically increments the ID for every new object
    Shape() : id(++counter) {} 
    
    // Explicit constructor just in case, though the auto-one handles the requirement
    Shape(int i) : id(i) {}

    // Added 'const' to ensure proper overriding down the chain
    virtual void draw() const {
        cout << "Drawing a shape" << endl;
    }

    int getid() const {
        return id;
    }
};

// Initialize the static member variable outside the class
int Shape::counter = 0;


class ColoredShape : virtual public Shape {
protected:
    string color;

public:
    ColoredShape(string c) : Shape(), color(c) {}
    
    // Matched the 'const' signature and exact string output from the prompt
    void draw() const override {
        cout << "Drawing a colored shape" << endl;
    }

    void setcolor(string c) {
        color = c;
    }

    string getcolor() const {
        return color;
    }
};


class TexturedShape : virtual public Shape {
protected:
    string texture;

public:
    TexturedShape(string t) : Shape(), texture(t) {}

    // Matched the 'const' signature and exact string output
    void draw() const override {
        cout << "Drawing a textured shape" << endl;
    }

    void settexture(string t) {
        texture = t;
    }

    string gettexture() const {
        return texture;
    }
};


class ColoredTexturedShape : public ColoredShape, public TexturedShape {
public:
    // CRITICAL FIX: Explicitly calling the virtual base constructor Shape() here
    ColoredTexturedShape(string c, string t) : Shape(), ColoredShape(c), TexturedShape(t) {}

    // Matched the 'const' signature and exact string output
    void draw() const override {
        cout << "Drawing a colored and textured shape" << endl;
    }
};


int main() {
    // Demonstration of object creation (Notice no IDs are passed manually!)
    Shape s1;
    ColoredShape s2("blue");
    TexturedShape s3("wavy");
    ColoredTexturedShape s4("pink", "soft");

    // Demonstration of correct usage and polymorphism
    Shape* shapes[] = { &s1, &s2, &s3, &s4 };

    for (int i = 0; i < 4; i++) {
        cout << "Object ID: " << shapes[i]->getid() << " -> ";
        shapes[i]->draw();
    }

    return 0;
}

//Step-by-Step Breakdown of Manual Initialization
//if shape id is manually initialized
//If you want to pass an explicit ID without a counter, your constructors must look like this:
//
//1. The Intermediate Classes
//ColoredShape and TexturedShape still need to take an id in their constructors so that they can function normally when created on their own.
//
//C++
//class ColoredShape : virtual public Shape {
//public:
//    // When you create a ColoredShape directly, this Shape(i) call executes.
//    ColoredShape(int i, string c) : Shape(i), color(c) {}
//};
//2. The Final Derived Class (Where the bug happens)
//When you instantiate ColoredTexturedShape, it is the "most derived class." Therefore, it must explicitly pass the ID all the way back to Shape directly, bypassing the intermediate classes.
//
//C++
//class ColoredTexturedShape : public ColoredShape, public TexturedShape {
//public:
//    // YOU MUST EXPLICITLY CALL Shape(i) HERE:
//    ColoredTexturedShape(int i, string c, string t) 
//        : Shape(i), ColoredShape(i, c), TexturedShape(i, t) {}
//};
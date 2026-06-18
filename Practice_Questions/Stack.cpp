#include <iostream>
using namespace std;

class Stack
{
private:
    int* ptr;
    int capacity;
    int currentsize;

    void resize()
    {
        capacity *= 2;

        int* temp = new int[capacity];

        for(int i = 0; i < currentsize; i++)
        {
            temp[i] = ptr[i];
        }

        delete[] ptr;
        ptr = temp;
    }

public:

    Stack()
    {
        capacity = 5;
        currentsize = 0;
        ptr = new int[capacity];
    }

    Stack(int c)
    {
        capacity = c;
        currentsize = 0;
        ptr = new int[capacity];
    }

    Stack(const Stack& obj)
    {
        capacity = obj.capacity;
        currentsize = obj.currentsize;

        ptr = new int[capacity];

        for(int i = 0; i < currentsize; i++)
        {
            ptr[i] = obj.ptr[i];
        }
    }

    Stack& operator=(const Stack& obj)
    {
        if(this == &obj)
            return *this;

        delete[] ptr;

        capacity = obj.capacity;
        currentsize = obj.currentsize;

        ptr = new int[capacity];

        for(int i = 0; i < currentsize; i++)
        {
            ptr[i] = obj.ptr[i];
        }

        return *this;
    }

    bool isEmpty() const
    {
        return currentsize == 0;
    }

    bool isFull() const
    {
        return currentsize == capacity;
    }

    void push(int value)
    {
        if(isFull())
        {
            resize();
        }

        ptr[currentsize] = value;
        currentsize++;
    }

    void pop()
    {
        if(isEmpty())
        {
            cout << "Stack Underflow" << endl;
            return;
        }

        currentsize--;
    }

    int top() const
    {
        if(isEmpty())
        {
            cout << "Stack is Empty" << endl;
            return -1;
        }

        return ptr[currentsize - 1];
    }

    int size() const
    {
        return currentsize;
    }

    void display() const
    {
        if(isEmpty())
        {
            cout << "Stack is Empty" << endl;
            return;
        }

        cout << "Top -> ";

        for(int i = currentsize - 1; i >= 0; i--)
        {
            cout << ptr[i] << " ";
        }

        cout << endl;
    }

    ~Stack()
    {
        delete[] ptr;
    }
};
int main()
{
    Stack s(3);

    s.push(10);
    s.push(20);
    s.push(30);

    s.display();

    cout << "Top: " << s.top() << endl;

    s.push(40);

    s.display();

    s.pop();

    cout << "After Pop: ";
    s.display();

    cout << "Size: " << s.size() << endl;

    return 0;
}
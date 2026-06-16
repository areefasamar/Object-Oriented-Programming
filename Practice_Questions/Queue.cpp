#include <iostream>
using namespace std;

class Queue
{
private:
    int* ptr;
    int capacity;
    int currentsize;
    int front;
    int rear;

public:

    Queue()
    {
        capacity = 5;
        ptr = new int[capacity];

        currentsize = 0;
        front = 0;
        rear = -1;
    }

    Queue(int c)
    {
        capacity = c;
        ptr = new int[capacity];

        currentsize = 0;
        front = 0;
        rear = -1;
    }

    Queue(const Queue& obj)
    {
        capacity = obj.capacity;
        currentsize = obj.currentsize;
        front = obj.front;
        rear = obj.rear;

        ptr = new int[capacity];

        for(int i = 0; i < capacity; i++)
        {
            ptr[i] = obj.ptr[i];
        }
    }

    Queue& operator=(const Queue& obj)
    {
        if(this == &obj)
            return *this;

        delete[] ptr;

        capacity = obj.capacity;
        currentsize = obj.currentsize;
        front = obj.front;
        rear = obj.rear;

        ptr = new int[capacity];

        for(int i = 0; i < capacity; i++)
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
        return rear == capacity - 1;
    }

    void enqueue(int value)
    {
        if(isFull())
        {
            cout << "Queue Overflow" << endl;
            return;
        }

        rear++;
        ptr[rear] = value;
        currentsize++;
    }

    void dequeue()
    {
        if(isEmpty())
        {
            cout << "Queue Underflow" << endl;
            return;
        }

        front++;
        currentsize--;

        // Reset queue when empty
        if(currentsize == 0)
        {
            front = 0;
            rear = -1;
        }
    }

    int getFront() const
    {
        if(isEmpty())
        {
            cout << "Queue is Empty" << endl;
            return -1;
        }

        return ptr[front];
    }

    int getRear() const
    {
        if(isEmpty())
        {
            cout << "Queue is Empty" << endl;
            return -1;
        }

        return ptr[rear];
    }

    int size() const
    {
        return currentsize;
    }

    void display() const
    {
        if(isEmpty())
        {
            cout << "Queue is Empty" << endl;
            return;
        }

        for(int i = front; i <= rear; i++)
        {
            cout << ptr[i] << " ";
        }

        cout << endl;
    }

    ~Queue()
    {
        delete[] ptr;
    }
};
int main()
{
    Queue q(5);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Queue: ";
    q.display();

    cout << "Front: "
         << q.getFront() << endl;

    cout << "Rear: "
         << q.getRear() << endl;

    q.dequeue();

    cout << "After Dequeue: ";
    q.display();

    cout << "Size: "
         << q.size() << endl;

    return 0;
}
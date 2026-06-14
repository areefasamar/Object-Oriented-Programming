//Changes in:
//isFull()
//enqueue()
//dequeue()
//display()

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

    // CHANGED:
    // Linear Queue:
    // return rear == capacity - 1;

    bool isFull() const
    {
        return currentsize == capacity;
    }

    void enqueue(int value)
    {
        if(isFull())
        {
            cout << "Queue Overflow" << endl;
            return;
        }

        // CHANGED:
        // Linear Queue:
        // rear++;

        rear = (rear + 1) % capacity;

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

        // CHANGED:
        // Linear Queue:
        // front++;

        front = (front + 1) % capacity;

        currentsize--;

        // Optional reset when queue becomes empty
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

        // CHANGED:
        // Linear Queue:
        //
        // for(int i = front; i <= rear; i++)
        // {
        //     cout << ptr[i] << " ";
        // }

        int index = front;

        for(int i = 0; i < currentsize; i++)
        {
            cout << ptr[index] << " ";

            index = (index + 1) % capacity;
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
    q.enqueue(40);
    q.enqueue(50);

    cout << "Initial Queue: ";
    q.display();

    q.dequeue();
    q.dequeue();

    cout << "After 2 Dequeues: ";
    q.display();

    q.enqueue(60);
    q.enqueue(70);

    cout << "After Circular Insertions: ";
    q.display();

    cout << "Front: " << q.getFront() << endl;
    cout << "Rear : " << q.getRear() << endl;

    return 0;
}
#include <iostream>
using namespace std;

template <class T>
class AbstractArray {
    protected:
        T* data;
        int capacity;
        int currentSize;

    public:
        AbstractArray(int cap) {
                capacity = cap;
                currentSize = 0;
                data = new T[capacity];
        }

        virtual ~AbstractArray() {
                delete[] data;
        }

        virtual void resize() = 0;
        virtual bool isEmpty() = 0;
        virtual bool isFull() = 0;
};

template <class T>
class Queue : public AbstractArray<T> {
    private:
        int frontIdx;
        int rearIdx;

    public:
        Queue(int cap) : AbstractArray<T>(cap) {
                frontIdx = 0;
                rearIdx = -1;
        }

        bool isEmpty() {
                return this->currentSize == 0;
        }

        bool isFull() {
                return this->currentSize == this->capacity;
        }

        int size() {
                return this->currentSize;
        }

        void resize() {
                int newCapacity = this->capacity * 2;
                T* newData = new T[newCapacity];
                
                for (int i = 0; i < this->currentSize; i++) {
                        newData[i] = this->data[(frontIdx + i) % this->capacity];
                }

                delete[] this->data;
                this->data = newData;
                this->capacity = newCapacity;
                frontIdx = 0;
                rearIdx = this->currentSize - 1;
        }

        void enqueue(T val) {
                if (isFull()) {
                        resize();
                }
                rearIdx = (rearIdx + 1) % this->capacity;
                this->data[rearIdx] = val;
                this->currentSize++;
        }

        void dequeue() {
                if (isEmpty()) {
                        cout << "Queue Empty" << endl;
                        return;
                }
                frontIdx = (frontIdx + 1) % this->capacity;
                this->currentSize--;
        }

        T Front() {
                if (!isEmpty()) return this->data[frontIdx];
                return T();
        }

        T Rear() {
                if (!isEmpty()) return this->data[rearIdx];
                return T();
        }
};

int main() {
        Queue<int> q(3);

        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);

        cout << "Size after 3 enqueues: " << q.size() << endl;
        cout << "Front: " << q.Front() << " | Rear: " << q.Rear() << endl;

        q.enqueue(40);
        cout << "Size after resize (4th enqueue): " << q.size() << endl;

        q.dequeue();
        cout << "Front after dequeue: " << q.Front() << endl;

        return 0;
}


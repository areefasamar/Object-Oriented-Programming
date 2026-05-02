#include <iostream>
#include <string>
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
                if (isEmpty()) return;
                frontIdx = (frontIdx + 1) % this->capacity;
                this->currentSize--;
        }

        T Front() {
                if (!isEmpty()) return this->data[frontIdx];
                return T();
        }
};

int main() {
        Queue<string> printerQueue(5);

        cout << "--- Receiving Print Jobs ---" << endl;
        printerQueue.enqueue("Assignment_Final.pdf");
        printerQueue.enqueue("Resume_2026.docx");
        printerQueue.enqueue("Concert_Tickets.png");
        printerQueue.enqueue("Budget_Report.xlsx");
        
        cout << "Total jobs in queue: " << printerQueue.size() << endl;

        cout << "\n--- Processing Printer Queue ---" << endl;
        while (!printerQueue.isEmpty()) {
                string currentJob = printerQueue.Front();
                cout << "Printer: Now printing [" << currentJob << "]" << endl;
                
                printerQueue.dequeue();
                
                if (!printerQueue.isEmpty()) {
                        cout << "Status: Job completed. Next in line: " << printerQueue.Front() << endl;
                } else {
                        cout << "Status: All jobs completed. Printer is now idle." << endl;
                }
                cout << "------------------------------------------" << endl;
        }

        return 0;
}


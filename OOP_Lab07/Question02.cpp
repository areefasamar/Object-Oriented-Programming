#include<iostream>
#include<cstdlib>
using namespace std;

class Array2D{
    int rows, cols;
    int **ptr;

    public:
        Array2D(int r = 0, int c = 0) : rows(r), cols(c){
            if(rows > 0 && cols > 0){
                ptr = new int*[rows];
                for(int i = 0; i < rows; i++){
                    ptr[i] = new int[cols];
                }
            }
            else{
                ptr = NULL;
            }
        }

        int* operator[](int index){
            return ptr[index];
        }

        bool search(int target){
            if(ptr == NULL || rows == 0 || cols == 0) return false;

            int low = 0;
            int high = (rows * cols) - 1;

            while(low <= high){
                int mid = low + (high - low) / 2;
                int midValue = ptr[mid / cols][mid % cols];

                if(midValue == target){
                    return true;
                }
                else if(midValue < target){
                    low = mid + 1;
                }
                else{
                    high = mid - 1;
                }
            }
            return false;
        }

        ~Array2D(){
            for(int i = 0; i < rows; i++){
                delete[] ptr[i];
            }
            delete[] ptr;
        }
};

int main(){
    int m = 3, n = 4;
    Array2D matrix(m, n);

    int values[3][4] = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = values[i][j];
        }
    }

    int target1 = 3;
    cout << "Target " << target1 << " found: " << (matrix.search(target1) ? "true" : "false") << endl;

    int target2 = 13;
    cout << "Target " << target2 << " found: " << (matrix.search(target2) ? "true" : "false") << endl;

    return 0;
}


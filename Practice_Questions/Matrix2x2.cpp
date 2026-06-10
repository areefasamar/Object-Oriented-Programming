#include<iostream>
#include<string>
using namespace std;
class Matrix{
	private:
		int matrix[2][2];
	public:
	
	Matrix(){
		matrix[0][0]=0;
		matrix[0][1]=0;
		matrix[1][0]=0;
		matrix[1][1]=0;
	}
	
	Matrix(int a, int b, int c, int d){
		matrix[0][0]=a;
		matrix[0][1]=b;
		matrix[1][0]=c;
		matrix[1][1]=d;
	}
	
	Matrix Add(const Matrix& m){
		Matrix result;
		for ( int i=0; i<2 ; i++){
			for(int j=0; j<2 ; j++){
				result.matrix[i][j]=matrix[i][j]+m.matrix[i][j];
			}
		}
		return result;
	}
	
	Matrix Multiply(const Matrix& m){
		Matrix result;
		for ( int i=0; i<2 ; i++){
			for(int j=0; j<2 ; j++){
				result.matrix[i][j]=0;
				for(int k=0 ; k<2 ; k++){
					result.matrix[i][j]+=matrix[i][k]*m.matrix[k][j];
				}
			}
		}
		return result;
	}
	
	void display() const{
		for(int i=0; i<2; i++){
			cout<<"[";
			for(int j=0; j<2 ; j++){
				cout<<matrix[i][j]<<" ";
			}
			cout<<"]"<<endl;
		}
		cout<<endl;
	}
	
	~Matrix(){
	}
};
int main(){
	Matrix m1(1,2,3,4);
	Matrix m2(5,6,7,8);
	Matrix result1 = m1.Add(m2);
	result1.display();
	Matrix result2= m1.Multiply(m2);
	result2.display();
	
	return 0;
	
}
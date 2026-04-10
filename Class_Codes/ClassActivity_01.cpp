#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Book{
	private:
		const int bookid;
		string title;
		string author;
		float price;
		static int total_books;
		bool isIssued = false;
	
	public:	
		Book(int id, string t, string a, float p): bookid(id) {
			title = t;
			author = a;
			if ( p > 0.0){
				price = p;
			}
			else{
				cout<<"Incsufficient Price!"<<endl;
				price = 0.0;
			}
			total_books++;
    	}
		
		const int getbookID() const{
			return bookid;
		}
		
		string gettitle() const{
			return title;
		}
		
		string getauthor() const{
			return author;
		}
		
		float getprice() const{
			return price;
		}
		
		void setprice(float p){
			if ( p > 0.0){
				price = p;
			}
			else{
				cout<<"Insufficient Price!"<<endl;
				price = 0.0;
			}
		}
		
		static int gettotalbooks(){
			return total_books;
		}
		
		bool getisIssued() const{
			return isIssued;
		}
		
		void setisIssued(bool status){
			isIssued = status;
		}
};

class Member{
	private:
		int memberid;
		string name;
		static int total_members;
		vector<int> borrowedBookIDs;
		
	public:
		static const int maxbooksallowed;
		
	     Member(int id, string n){
	     	memberid = id;
	     	name = n;
	     	total_members++;
		 }	
		 
		int getmemberID() const{
			return memberid;
		} 
		
		string getname() const{
			return name;
		}
		
		static int gettotalmembers(){
			return total_members;
		}
	
	    void borrowBook(int bookID){ 
		    borrowedBookIDs.push_back(bookID);
		}
   
        int getBorrowedCount() const{ 
		    return borrowedBookIDs.size(); 
		}
		
};

class Library{
	private:
		vector<Book> books;
		vector<Member> members;
		
	public:
		void addBook(const Book& b){
            books.push_back(b);
        }
        
        void registerMember(const Member& m){
            members.push_back(m);
        }
        
        void displayBooks() const{
            for (const Book& b : books){
                 cout << b.getbookID() << " " << b.gettitle() << " " << b.getauthor() << " " << b.getprice() << endl;
            }
        }
        
        void DisplayMembers()const{
            for (const Member& m : members){   
                cout << m.getmemberID() << " " << m.getname() << endl;
            }
        }
        
        bool issueBook(int bookID, int memberID){
		    Book* bookPtr = nullptr;
            for (Book& b : books){
                if (b.getbookID() == bookID){
                    bookPtr = &b;
                    break;
                }
            }
            if (bookPtr == nullptr){
                cout << "Book not found!" << endl;
                 return false;
            }
  
            if (bookPtr->getisIssued()){
                cout << "Book is already issued!" << endl;
                 return false;
            }

            Member* memberPtr = nullptr;
                for (Member& m : members){
                    if (m.getmemberID() == memberID){
                        memberPtr = &m;
                        break;
                    }
                }
            if (memberPtr == nullptr){
                    cout << "Member not found!" << endl;
                    return false;
             }

            if (memberPtr->getBorrowedCount() >= Member::maxbooksallowed){
                    cout << "Member has reached maximum allowed books!" << endl;
                    return false;
            }

            bookPtr->setisIssued(true);
            memberPtr->borrowBook(bookID);
			cout << "Book issued successfully!" << endl;
            return true;
}
};
	int Book::total_books = 0;
	int Member::total_members = 0;
	const int Member::maxbooksallowed = 3;
	
int main(){
    Library lib;

    Book b1(1, "1984", "Orwell", 250.0);
    Book b2(2, "Hobbit", "Tolkien", 300.0);
    lib.addBook(b1);
    lib.addBook(b2);

    Member m1(1, "Alice");
    Member m2(2, "Bob");
    lib.registerMember(m1);
    lib.registerMember(m2);

    lib.issueBook(1, 1);
    lib.issueBook(2, 1); 
    lib.issueBook(1, 2);

    lib.displayBooks();
    lib.DisplayMembers();

    return 0;
}


#include <iostream>
#include <string>
using namespace std;

class Media {
    protected:
        string title;
        bool isBorrowed;

    public:
        Media(string t) : title(t), isBorrowed(false) {}

        void borrowMedia() {
                if (!isBorrowed) {
                        isBorrowed = true;
                        cout << title << " has been successfully borrowed." << endl;
                } else {
                        cout << "Sorry, " << title << " is currently out of stock/borrowed." << endl;
                }
        }

        void returnMedia() {
                if (isBorrowed) {
                        isBorrowed = false;
                        cout << title << " has been returned successfully." << endl;
                } else {
                        cout << title << " was not borrowed." << endl;
                }
        }

        virtual void display() {
                cout << "Title: " << title << endl;
                cout << "Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
        }
};

class Author {
    protected:
        string authorName;

    public:
        Author(string a) : authorName(a) {}

        string getAuthorName(){ 
                return authorName; 
        }
};

class IssueDetails {
    protected:
        int issueNumber;

    public:
        IssueDetails(int issue) : issueNumber(issue) {}

        int getIssueNumber(){ 
                return issueNumber; 
        }
};

class Director {
    protected:
        string directorName;

    public:
        Director(string d) : directorName(d) {}

        string getDirectorName(){ 
                return directorName; 
        }
};

class Book : public Media, public Author {
    public:
        Book(string t, string a) : Media(t), Author(a) {}

        void display() {
                cout << "==== Book Info ====" << endl;
                Media::display();
                cout << "Author: " << authorName << endl;
                cout << "===================" << endl;
        }
};

class Magazine : public Media, public IssueDetails {
    public:
        Magazine(string t, int issue) : Media(t), IssueDetails(issue) {}

        void display() {
                cout << "==== Magazine Info ====" << endl;
                Media::display();
                cout << "Issue Number: " << issueNumber << endl;
                cout << "=======================" << endl;
        }
};

class DVD : public Media, public Director {
    public:
        DVD(string t, string d) : Media(t), Director(d) {}

        void display() {
                cout << "==== DVD Info ====" << endl;
                Media::display();
                cout << "Director: " << directorName << endl;
                cout << "==================" << endl;
        }
};

int main(void) {
        Book myBook("The Great Gatsby", "F. Scott Fitzgerald");
        Magazine myMagazine("National Geographic", 205);
        DVD myDVD("Inception", "Christopher Nolan");

        cout << "\n--- Displaying Initial States ---" << endl;
        myBook.display();
        myMagazine.display();
        myDVD.display();

        cout << "\n--- Testing Borrow Operations ---" << endl;
        myBook.borrowMedia();
        myDVD.borrowMedia();
        
        cout << "\n--- Testing Double Borrow (Should Fail) ---" << endl;
        myBook.borrowMedia();

        cout << "\n--- Displaying States After Borrowing ---" << endl;
        myBook.display();
        myDVD.display();

        cout << "\n--- Testing Return Operations ---" << endl;
        myBook.returnMedia();
        
        cout << "\n--- Testing DVD Return ---" << endl;
        myDVD.returnMedia();
        
        cout << "\n--- Displaying Final State ---" << endl;
        myBook.display();

        return 0;
}



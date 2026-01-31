#include <iostream>
#include <string>
using namespace std;
class bookType{
private:
    string title;
    string authors[4];
    int authorCount;
    string publisher;
    string ISBN;
    double price;
    int copiesInStock;

public:
    bookType(){
        title = "";
        publisher = "";
        ISBN = "";
        price = 0.0;
        copiesInStock = 0;
        authorCount = 0;
    }

    void setBookDetails(string t, string a[], int aCount, string pub, string isbn, double p, int copies){
        title = t;
        publisher = pub;
        ISBN = isbn;
        price = p;
        copiesInStock = copies;

        if (aCount > 4)
            authorCount = 4;
        else
            authorCount = aCount;

        for (int i = 0; i < authorCount; i++)
            authors[i] = a[i];
    }

    void displayBook(){
        cout << "Title: " << title << endl;
        cout << "Authors: ";
        for (int i = 0; i < authorCount; i++){
            cout << authors[i];
            if (i < authorCount - 1) cout << ", ";
        }
        cout << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Price: " << price << endl;
        cout << "Copies in Stock: " << copiesInStock << endl;
        cout << "------------------------" << endl;
    }

    bool checkTitle(string t){
        if (title == t)
            return true;
        else
            return false;
    }

    bool checkISBN(string isbn){
        if (ISBN == isbn)
            return true;
        else
            return false;
    }

    void updateCopies(int newCopies){
        copiesInStock = newCopies;
    }

    int getCopies(){
        return copiesInStock;
    }
};

void searchByTitle(bookType library[], int size, string searchTitle){
    bool found = false;
    for (int i = 0; i < size; i++){
        if (library[i].checkTitle(searchTitle)){
            cout << "\nBook found by title:\n";
            library[i].displayBook();
            found = true;
            break;
        }
    }
    if (!found)
        cout << "\nBook not found by title.\n";
}

void searchByISBN(bookType library[], int size, string searchISBN){
    bool found = false;
    for (int i = 0; i < size; i++){
        if (library[i].checkISBN(searchISBN)){
            cout << "\nBook found by ISBN:\n";
            library[i].displayBook();
            found = true;
            break;
        }
    }
    if (!found)
        cout << "\nBook not found by ISBN.\n";
}
int main(){
    bookType library[100]; 
    int bookCount = 2;    

    string authors1[2] = {"Dennis Ritchie", "Brian Kernighan"};
    library[0].setBookDetails("The C Programming Language", authors1, 2, "Prentice Hall", "9780131103627", 650.0, 10);

    string authors2[1] = {"Mark Allen Weiss"};
    library[1].setBookDetails(
        "Data Structures and Algorithm Analysis", authors2, 1, "Pearson", "9780132847377", 550.0, 5);

    string searchTitle = "The C Programming Language";
    searchByTitle(library, bookCount, searchTitle);

    string searchISBN = "9780132847377";
    searchByISBN(library, bookCount, searchISBN);

    library[0].updateCopies(15);
    cout << "\nAfter updating copies of first book:\n";
    library[0].displayBook();

    return 0;
}

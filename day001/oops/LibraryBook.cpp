/**
 Design a Book class that represents one physical library copy. Its title, author, and ISBN identify the book, while its availability changes as 
 people borrow and return it. A copy is always in one of two states: available on the shelf or currently borrowed.

 Implement the Book class:
 
 Book(String title, String author, String isbn) creates a copy with the given details. Every new copy starts available.
 boolean borrow() checks out an available copy, changes its state to borrowed, and returns true. If the copy is already borrowed, leave it unchanged and 
 return false.
 boolean returnBook() returns a borrowed copy to the shelf, changes its state to available, and returns true. If the copy is already available, leave it 
 unchanged and return false.
 boolean isAvailable() returns true when the copy is on the shelf and false when it is borrowed. It does not change the state.
 String getInfo() returns the copy's current details in the exact format "<title> by <author> (ISBN: <isbn>) - <status>". Use Available or Borrowed for 
 <status> based on the state at the time of the call.
 For example, an available copy of Clean Code by Robert Martin with ISBN 978-0132350884 returns "Clean Code by Robert Martin (ISBN: 978-0132350884) 
 - Available".
 
 Keep the book's state encapsulated. Callers may borrow, return, or inspect the copy, but they must not be able to assign its availability directly.
*/
#include <iostream>
#include <string>

using namespace std;

class Book{
  private:
    string title;
    string author;
    string isbn;
    bool state;
  public:
    Book(string title_, string author_, string isbn_):title{title_}, author{author_}, isbn{isbn_}{
        this->state = true;
    }

    bool borrow(){
        if(this->state){
            this->state = false;
            return true;
        }
        return false;
    }

    bool returnBook(){
        if(!this->state){
            this->state = true;
            return true;
        }
        return false;
    }

    bool isAvailable(){
        if(this->state){
            return true;
        }
        return false;
    }

    string getInfo(){
        string str = (this->state?"Available":"Borrowed");
        return ("---------------\nTitle: " + this->title + "\nAuthor: " +
            this->author + 
            "\nIsbn: " + this->isbn 
            +"\nState: " + str + "\n---------------");
    }

    ~Book(){

    }
};

int main(){
    Book bk("Catch Me", "Vishal", "SBI8723");
    bool temp = bk.borrow();
    temp = bk.returnBook();
    temp = bk.isAvailable();
    string str = (bk.isAvailable()?"Yes":"No");
    cout << "Is availabe: " << str << endl;
    cout << bk.getInfo() << endl;

    return 0;
}
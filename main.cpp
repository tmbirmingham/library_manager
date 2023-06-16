#include <iostream>
#include <string>
#include <utility>

const int MAX_BOOKS = 100; // Maximum number of books in the library

class Book {
    std::string title, author;
    bool isPartOfSeries{};
    int seriesNumber{};
    int idNumber{};

public:
    Book(std::string  bookTitle, const std::string& bookAuthor, bool isSeries, int seriesNum, int idNum)
            : title(std::move(bookTitle)), author(bookAuthor), isPartOfSeries(isSeries), seriesNumber(seriesNum), idNumber(idNum) {}

    void new_book() { // Function to create a new book
        std::cout << "*****************************\n";
        std::cout << "ENTER THE BOOK ID NUMBER: ";
        std::cin >> idNumber;
        std::cin.ignore();
        std::cout << "ENTER THE NAME OF THE BOOK: ";
        std::getline(std::cin, title);
        std::cout << "ENTER THE NAME OF THE AUTHOR: ";
        std::getline(std::cin, author);
        std::cout << "IS IT PART OF A SERIES? (1 = Yes, 0 = No): ";
        std::cin >> isPartOfSeries;
        if (isPartOfSeries) {
            std::cout << "ENTER THE SERIES NUMBER: ";
            std::cin >> seriesNumber;
        }
        std::cout << "\n\tNEW ENTRY CREATED\n";
    }

    void show_book() { // Function that displays the books
        std::cout << "ID number: " << idNumber << '\n';
        std::cout << "Name: " << title << '\n';
        std::cout << "Author: " << author << '\n';
        if (isPartOfSeries) {
            std::cout << "Part of Series: Yes\n";
            std::cout << "Number in the Series: " << seriesNumber << '\n';
        } else {
            std::cout << "Part of Series: No\n";
        }
    }

    int getIdNumber() const {
        return idNumber;
    }
};

int find_book_index(Book* library[], int id, int size) {
    for (int i = 0; i < size; ++i) {
        if (library[i]->getIdNumber() == id) {
            return i;
        }
    }
    return -1;  // Book not found
}

void delete_book(Book* library[], int& size) {
    int id;
    std::cout << "Enter the ID number of the book to delete: ";
    std::cin >> id;

    int index = find_book_index(library, id, size);
    if (index != -1) {
        delete library[index];  // Delete the book object
        // Shift the pointers after the deleted book to fill the gap
        for (int i = index; i < size - 1; ++i) {
            library[i] = library[i + 1];
        }
        size--;
        std::cout << "Book deleted successfully.\n";
    } else {
        std::cout << "Book not found.\n";
    }
}

int main() {
    int choice;
    Book* library[MAX_BOOKS];
    int size = 0;
    std::cout << "Welcome to the library!";

    do {
        std::cout << "\nPlease choose the action you would like to perform:\n";
        std::cout << "1. Add a book\n2. Delete a book\n3. Display books\n4. Exit\n";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                if (size < MAX_BOOKS) {
                    Book* newBook = new Book("", "", false, 0, 0);
                    newBook->new_book();
                    library[size] = newBook;
                    size++;
                } else {
                    std::cout << "The library is full. Cannot add more books.\n";
                }
                break;
            }
            case 2:
                delete_book(library, size);
                break;
            case 3:
                std::cout << "Displaying books\n";
                for (int i = 0; i < size; ++i) {
                    library[i]->show_book();
                    std::cout << "-----------------------------\n";
                }
                break;
            case 4:
                std::cout << "\tGoodbye.\n";
                break;
            default:
                std::cout << "Invalid Operation, please try again.\n";
                break;
        }
    } while (choice != 4);

    // Free the dynamically allocated memory for book objects
    for (int i = 0; i < size; ++i) {
        delete library[i];
    }

    return 0;
}

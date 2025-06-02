#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

struct Book 
{
    int id;
    string title;
    string author;
    string description;
    float rating;

    void displayBrief() const 
    {
        cout << "[" << id << "] " << title << " by " << author << endl;
    }

    void displayDetails() const 
    {
        cout << "Title: " << title << "\nAuthor: " << author
             << "\nDescription: " << description
             << "\nRating: " << rating << "\n";
    }
};

vector<Book> loadBooks(const string& filename) 
{
    ifstream file(filename);
    json data;
    file >> data;

    vector<Book> books;
    for (auto& item : data) 
    {
        books.push_back({
            item["id"],
            item["title"],
            item["author"],
            item["description"],
            item["rating"]
        });
    }
    return books;
}

unordered_set<int> loadFavorites(const string& filename) 
{
    ifstream file(filename);
    unordered_set<int> favs;
    int id;
    while (file >> id) favs.insert(id);
    return favs;
}

void saveFavorites(const unordered_set<int>& favs, const string& filename) 
{
    ofstream file(filename);
    for (int id : favs) file << id << endl;
}

int main() 
{
    vector<Book> books = loadBooks("books.json");
    unordered_set<int> favorites = loadFavorites("favorites.txt");

    int choice;
    while (true) 
    {
        cout << "\n--- Book Review App ---\n";
        cout << "1. View all books\n2. View book details\n3. Mark as favorite\n4. View favorites\n5. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) 
        {
            for (const auto& book : books) book.displayBrief();
        } 
        else if (choice == 2) 
        {
            int id;
            cout << "Enter book ID: ";
            cin >> id;
            auto it = find_if(books.begin(), books.end(), [id](const Book& b){ return b.id == id; });
            if (it != books.end()) it->displayDetails();
            else cout << "Book not found.\n";
        } 
        else if (choice == 3) 
        {
            int id;
            cout << "Enter book ID to favorite: ";
            cin >> id;
            favorites.insert(id);
            saveFavorites(favorites, "favorites.txt");
            cout << "Book added to favorites.\n";
        } 
        else if (choice == 4) 
        {
            cout << "--- Favorite Books ---\n";
            for (const auto& book : books)
                if (favorites.count(book.id)) book.displayBrief();
        } 
        else 
        {
            break;
        }
    }

    return 0;
}

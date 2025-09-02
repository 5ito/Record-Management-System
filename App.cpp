#include "App.hpp"
#include <iostream>
#include <limits>

int App::menu() {
    std::cout << "\n=== Record Management System ===\n"
        << "1) Add book\n"
        << "2) Display all\n"
        << "3) Search by ID\n"
        << "4) Update book\n"
        << "5) Delete book\n"
        << "6) Sort & display\n"
        << "7) Export CSV\n"
        << "0) Exit\n"
        << "Choose: ";
    int c{};
    if (!(std::cin >> c)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return c;
}

void App::run() {
    while (true) {
        switch (menu()) {
        case 1: addRecord();    break;
        case 2: displayAll();   break;
        case 3: searchById();   break;
        case 4: updateRecord(); break;
        case 5: deleteRecord(); break;
        case 6: sortRecords();  break;
        case 7: exportCsv();    break;
        case 0: std::cout << "Bye.\n"; return;
        default: std::cout << "Invalid option.\n"; break;
        }
    }
}

void App::addRecord() {
    Book b;

    while (true) {
        std::cout << "Enter ID (number): ";
        if (std::cin >> b.id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "Invalid ID. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter Title: ";
    std::getline(std::cin, b.title);

    std::cout << "Enter Author: ";
    std::getline(std::cin, b.author);

    while (true) {
        std::cout << "Enter Year: ";
        if (std::cin >> b.year) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "Invalid Year. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter ISBN: ";
    std::getline(std::cin, b.isbn);

    std::cout << "Enter Status (available/loaned): ";
    std::getline(std::cin, b.status);

    if (store.add(b))
        std::cout << "Book added successfully!\n";
    else
        std::cout << "Failed to add book (duplicate ID or file error).\n";
}

void App::displayAll() {
    auto all = store.getAll();
    if (all.empty()) {
        std::cout << "No books found.\n";
        return;
    }

    std::cout << "\n--- Book Records ---\n";
    for (const auto& b : all) {
        std::cout << "ID: " << b.id
            << " | Title: " << b.title
            << " | Author: " << b.author
            << " | Year: " << b.year
            << " | ISBN: " << b.isbn
            << " | Status: " << b.status << "\n";
    }
}

// Other features not yet implemented
void App::searchById() { std::cout << "[stub] searchById\n"; }
void App::deleteRecord() { std::cout << "[stub] deleteRecord\n"; }
void App::updateRecord() { std::cout << "[stub] updateRecord\n"; }
void App::sortRecords() { std::cout << "[stub] sortRecords\n"; }
void App::exportCsv() { std::cout << "[stub] exportCsv\n"; }

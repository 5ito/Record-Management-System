#include "FileBookStore.hpp"
#include <fstream>
#include <filesystem>
#include <algorithm>

using namespace std;

static void writeString(ofstream& out, const string& s) {
    size_t len = s.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(s.data(), static_cast<streamsize>(len));
}

static bool readString(ifstream& in, string& s) {
    size_t len{};
    if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) return false;
    s.resize(len);
    return static_cast<bool>(in.read(s.data(), static_cast<streamsize>(len)));
}

FileBookStore::FileBookStore(string dataFilePath)
    : path(std::move(dataFilePath)) {
    filesystem::path p(path);
    if (!p.parent_path().empty())
        filesystem::create_directories(p.parent_path());
    if (!filesystem::exists(path)) {
        ofstream out(path, ios::binary); // create empty file
    }
}

bool FileBookStore::add(const Book& b) {
    for (const auto& ex : getAll()) if (ex.id == b.id) return false;

    ofstream out(path, ios::binary | ios::app);
    if (!out) return false;

    out.write(reinterpret_cast<const char*>(&b.id), sizeof(b.id));
    out.write(reinterpret_cast<const char*>(&b.year), sizeof(b.year));
    writeString(out, b.title);
    writeString(out, b.author);
    writeString(out, b.isbn);
    writeString(out, b.status);

    return static_cast<bool>(out);
}

vector<Book> FileBookStore::getAll() {
    vector<Book> books;
    ifstream in(path, ios::binary);
    if (!in) return books;

    while (true) {
        Book b;
        if (!in.read(reinterpret_cast<char*>(&b.id), sizeof(b.id))) break;
        if (!in.read(reinterpret_cast<char*>(&b.year), sizeof(b.year))) break;
        if (!readString(in, b.title)) break;
        if (!readString(in, b.author)) break;
        if (!readString(in, b.isbn)) break;
        if (!readString(in, b.status)) break;

        books.push_back(std::move(b));
    }
    return books;
}

// Stubs for features we’ll implement later
optional<Book> FileBookStore::findById(int) { return nullopt; }
bool FileBookStore::update(int, const Book&) { return false; }
bool FileBookStore::remove(int) { return false; }
bool FileBookStore::exportCsv(const string&) { return false; }
vector<Book> FileBookStore::sortBy(SortKey, bool) { return {}; }

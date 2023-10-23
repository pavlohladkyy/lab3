#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <Windows.h>

using namespace std;

class Record {
public:
    string lastName;
    string firstName;
    string phoneNumber;
    string dateOfBirth;

    Record(const string& lastName, const string& firstName, const string& phoneNumber, const string& dateOfBirth)
        : lastName(lastName), firstName(firstName), phoneNumber(phoneNumber), dateOfBirth(dateOfBirth) {}

    bool operator==(const Record& other) const {
        return lastName == other.lastName && firstName == other.firstName;
    }

    bool operator+(const Record& other) const {
        // Додавання рекордів, якщо об'єкт поточного запису розположений після об'єкта other за датою народження
        return dateOfBirth > other.dateOfBirth;
    }

    bool operator-(const Record& other) const {
        // Віднімання рекордів, якщо об'єкт поточного запису розположений перед об'єктом other за датою народження
        return dateOfBirth < other.dateOfBirth;
    }

    // Перевантажений оператор = для копіювання записів
    Record& operator=(const Record& other) {
        if (this != &other) {
            lastName = other.lastName;
            firstName = other.firstName;
            phoneNumber = other.phoneNumber;
            dateOfBirth = other.dateOfBirth;
        }
        return *this;
    }

    void displayRecord() const {
        cout << "Ім'я: " << lastName << "\n";
        cout << "Прізвище: " << firstName << "\n";
        cout << "Номер телефону: " << phoneNumber << "\n";
        cout << "Дата народження: " << dateOfBirth << "\n";
    }
};

class Notebook {
private:
    vector<Record> records;

public:
    // Оператор + для додавання запису до записника
    Notebook& operator+(const Record& record) {
        records.push_back(record);
        return *this;
    }

    // Оператор - для видалення запису з записника
    Notebook& operator-(const Record& record) {
        auto it = remove(records.begin(), records.end(), record);
        if (it != records.end()) {
            records.erase(it, records.end());
        }
        return *this;
    }

    // Перевантажений оператор = для сортування за датами народження
    Notebook& operator=(const Notebook& other) {
        if (this != &other) {
            records = other.records;
            sortRecordsByDateOfBirth();
        }
        return *this;
    }

    void sortRecordsByDateOfBirth() {
        sort(records.begin(), records.end());
        for (const Record& record : records) {
            record.displayRecord();
            cout << endl;
        }
    }
};

void promptSortByDateOfBirth(Notebook& notebook) {
    string response;
    cout << "Чи бажаєте відсортувати записи за датою народження? (так/ні): ";
    cin >> response;

    if (response == "так") {
        notebook.sortRecordsByDateOfBirth();
        cout << "Записи відсортовані за датою народження." << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Notebook notebook;
    Record record1("Сидоров", "Іван", "123-456", "01.01.1990");
    Record record2("Андрієнко", "Світлана", "987-654", "05.05.1985");
    
    // Додавання записів до записника за допомогою оператора +
    notebook + record1 + record2;

    // Видалення запису з записника за допомогою оператора -
    notebook - record1;

    // Сортування записника за датами народження за допомогою оператора =
    Notebook sortedNotebook;
    sortedNotebook = notebook;

    int searchType;
    cout << "Виберіть тип пошуку (1 - за ім'ям, 2 - за датою народження): ";
    cin >> searchType;

    if (searchType == 1) {
        string searchName;
        cout << "Введіть ім'я для пошуку: ";
        cin >> searchName;

        try {
            Record searchByLastName = notebook.findRecordByLastName(searchName);
            searchByLastName.displayRecord();
        }
        catch (runtime_error& e) {
            cerr << e.what() << endl;
        }
    }
    else if (searchType == 2) {
        string searchDateOfBirth;
        cout << "Введіть дату народження для пошуку (у форматі dd.mm.yyyy): ";
        cin >> searchDateOfBirth;

        try {
            Record searchByDateOfBirth = notebook.findRecordByDateOfBirth(searchDateOfBirth);
            searchByDateOfBirth.displayRecord();
        }
        catch (runtime_error& e) {
            cerr << e.what() << endl;
        }
    }
    else {
        cerr << "Невірний тип пошуку." << endl;
    }

    promptSortByDateOfBirth(notebook);

    return 0;
}
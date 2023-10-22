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

    bool operator>(const Record& other) const {
        return dateOfBirth > other.dateOfBirth;
    }

    bool operator<(const Record& other) const {
        return dateOfBirth < other.dateOfBirth;
    }

    void displayRecord() const {
        cout << "Прізвище: " << lastName << "\n";
        cout << "Ім'я: " << firstName << "\n";
        cout << "Номер телефону: " << phoneNumber << "\n";
        cout << "Дата народження: " << dateOfBirth << "\n";
    }
};

class Notebook {
private:
    vector<Record> records;

public:
    void addRecord(const Record& record) {
        records.push_back(record);
    }

    void deleteRecord(const Record& record) {
        auto it = remove(records.begin(), records.end(), record);
        if (it != records.end()) {
            records.erase(it, records.end());
        }
    }

    Record findRecordByLastName(const string& lastName) const {
        for (const Record& record : records) {
            if (record.lastName == lastName) {
                return record;
            }
        }
        throw runtime_error("Запис не знайдено");
    }

    Record findRecordByDateOfBirth(const string& dateOfBirth) const {
        for (const Record& record : records) {
            if (record.dateOfBirth == dateOfBirth) {
                return record;
            }
        }
        throw runtime_error("Запис не знайдено");
    }

    void sortRecordsByDateOfBirth() {
        sort(records.begin(), records.end());
        for (const Record& record : records) {
            record.displayRecord();
            cout << endl;
        }
    }
};

// Функція для запиту користувача про сортування записів за датою народження
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
    Record record1("Сміт", "Іван", "123-456", "01.01.1990");
    Record record2("Джонсон", "Сара", "987-654", "05.05.1985");
    Record record3("Петренко", "Марія", "111-222", "10.10.1992");
    Record record4("Іванов", "Олег", "555-888", "15.03.1987");
    Record record5("Коваль", "Оксана", "999-777", "20.12.1995");
    Record record6("Василенко", "Віталій", "777-123", "30.06.1980");
    Record record7("Мельничук", "Наталія", "456-789", "04.04.1988");
    Record record8("Лисенко", "Ірина", "222-333", "12.08.1994");
    Record record9("Гриценко", "Олексій", "333-555", "25.07.1999");
    Record record10("Павленко", "Лариса", "777-999", "22.11.1982");



    notebook.addRecord(record1);
    notebook.addRecord(record2);
    notebook.addRecord(record3);
    notebook.addRecord(record4);
    notebook.addRecord(record5);
    notebook.addRecord(record6);
    notebook.addRecord(record7);
    notebook.addRecord(record8);
    notebook.addRecord(record9);
    notebook.addRecord(record10);

    int searchType;
    cout << "Оберіть тип пошуку (1 - за прізвищем, 2 - за датою народження): ";
    cin >> searchType;

    if (searchType == 1) {
        string searchName;
        cout << "Введіть прізвище для пошуку: ";
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
        cerr << "Неправильний тип пошуку." << endl;
    }

    // Виклик функції для запиту про сортування
    promptSortByDateOfBirth(notebook);

    return 0;
}

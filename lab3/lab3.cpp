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
        cout << "�������: " << lastName << "\n";
        cout << "��'�: " << firstName << "\n";
        cout << "����� ��������: " << phoneNumber << "\n";
        cout << "���� ����������: " << dateOfBirth << "\n";
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
        throw runtime_error("����� �� ��������");
    }

    Record findRecordByDateOfBirth(const string& dateOfBirth) const {
        for (const Record& record : records) {
            if (record.dateOfBirth == dateOfBirth) {
                return record;
            }
        }
        throw runtime_error("����� �� ��������");
    }

    void sortRecordsByDateOfBirth() {
        sort(records.begin(), records.end());
        for (const Record& record : records) {
            record.displayRecord();
            cout << endl;
        }
    }
};

// ������� ��� ������ ����������� ��� ���������� ������ �� ����� ����������
void promptSortByDateOfBirth(Notebook& notebook) {
    string response;
    cout << "�� ������ ����������� ������ �� ����� ����������? (���/�): ";
    cin >> response;

    if (response == "���") {
        notebook.sortRecordsByDateOfBirth();
        cout << "������ ���������� �� ����� ����������." << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Notebook notebook;
    Record record1("���", "����", "123-456", "01.01.1990");
    Record record2("�������", "����", "987-654", "05.05.1985");
    Record record3("��������", "����", "111-222", "10.10.1992");
    Record record4("������", "����", "555-888", "15.03.1987");
    Record record5("������", "������", "999-777", "20.12.1995");
    Record record6("���������", "³����", "777-123", "30.06.1980");
    Record record7("���������", "������", "456-789", "04.04.1988");
    Record record8("�������", "�����", "222-333", "12.08.1994");
    Record record9("��������", "������", "333-555", "25.07.1999");
    Record record10("��������", "������", "777-999", "22.11.1982");



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
    cout << "������ ��� ������ (1 - �� ��������, 2 - �� ����� ����������): ";
    cin >> searchType;

    if (searchType == 1) {
        string searchName;
        cout << "������ ������� ��� ������: ";
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
        cout << "������ ���� ���������� ��� ������ (� ������ dd.mm.yyyy): ";
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
        cerr << "������������ ��� ������." << endl;
    }

    // ������ ������� ��� ������ ��� ����������
    promptSortByDateOfBirth(notebook);

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Contact {
private:
    string name;
    string phone;
    string email;

public:
    Contact() = default;

    Contact(string n, string p, string e) : name(n), phone(p), email(e) {}

    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }

    void setName(const string &n) { name = n; }
    void setPhone(const string &p) { phone = p; }
    void setEmail(const string &e) { email = e; }

    void displayContact() const {
        cout << "Name: " << name << ", Phone: " << phone << ", Email: " << email << endl;
    }

    // Overloading << operator to save contacts in file
    friend ofstream &operator<<(ofstream &ofs, const Contact &c) {
        ofs << c.name << "\n" << c.phone << "\n" << c.email << "\n";
        return ofs;
    }

    // Overloading >> operator to load contacts from file
    friend ifstream &operator>>(ifstream &ifs, Contact &c) {
        getline(ifs, c.name);
        getline(ifs, c.phone);
        getline(ifs, c.email);
        return ifs;
    }
};

class PhoneBook {
private:
    vector<Contact> contacts;

public:
    void addContact() {
        string name, phone, email;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter Email: ";
        getline(cin, email);
        contacts.push_back(Contact(name, phone, email));
        cout << "Contact added successfully!\n";
    }

    void displayAllContacts() const {
        if (contacts.empty()) {
            cout << "Phone book is empty!\n";
        } else {
            for (size_t i = 0; i < contacts.size(); ++i) {
                cout << i + 1 << ". ";
                contacts[i].displayContact();
            }
        }
    }

    void searchContact() const {
        string keyword;
        cout << "Enter name, phone, or email to search: ";
        cin.ignore();
        getline(cin, keyword);

        for (const auto &contact : contacts) {
            if (contact.getName() == keyword || contact.getPhone() == keyword || contact.getEmail() == keyword) {
                cout << "Contact found:\n";
                contact.displayContact();
                return;
            }
        }
        cout << "Contact not found!\n";
    }

    void deleteContact() {
        string name;
        cout << "Enter the name of the contact to delete: ";
        cin.ignore();
        getline(cin, name);

        auto it = remove_if(contacts.begin(), contacts.end(),
                            [&name](const Contact &contact) { return contact.getName() == name; });
        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            cout << "Contact deleted successfully!\n";
        } else {
            cout << "Contact not found!\n";
        }
    }

    void updateContact() {
        string name;
        cout << "Enter the name of the contact to update: ";
        cin.ignore();
        getline(cin, name);

        for (auto &contact : contacts) {
            if (contact.getName() == name) {
                string phone, email;
                cout << "Enter new Phone: ";
                getline(cin, phone);
                cout << "Enter new Email: ";
                getline(cin, email);
                contact.setPhone(phone);
                contact.setEmail(email);
                cout << "Contact updated successfully!\n";
                return;
            }
        }
        cout << "Contact not found!\n";
    }

    void saveToFile(const string &filename) const {
        ofstream ofs(filename);
        if (!ofs) {
            cout << "Error opening file for saving contacts.\n";
            return;
        }
        for (const auto &contact : contacts) {
            ofs << contact;
        }
        cout << "Contacts saved to " << filename << " successfully!\n";
    }

    void loadFromFile(const string &filename) {
        ifstream ifs(filename);
        if (!ifs) {
            cout << "Error opening file for loading contacts.\n";
            return;
        }

        contacts.clear();
        Contact temp;
        while (ifs >> temp) {
            contacts.push_back(temp);
        }
        cout << "Contacts loaded from " << filename << " successfully!\n";
    }
};

// Main menu for the phone book management system
void menu() {
    cout << "\n--- Phone Book Management System ---\n";
    cout << "1. Add Contact\n";
    cout << "2. Display All Contacts\n";
    cout << "3. Search Contact\n";
    cout << "4. Delete Contact\n";
    cout << "5. Update Contact\n";
    cout << "6. Save Contacts to File\n";
    cout << "7. Load Contacts from File\n";
    cout << "8. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    PhoneBook phoneBook;
    const string filename = "contacts.txt";
    int choice;

    while (true) {
        menu();
        cin >> choice;

        switch (choice) {
            case 1:
                phoneBook.addContact();
                break;
            case 2:
                phoneBook.displayAllContacts();
                break;
            case 3:
                phoneBook.searchContact();
                break;
            case 4:
                phoneBook.deleteContact();
                break;
            case 5:
                phoneBook.updateContact();
                break;
            case 6:
                phoneBook.saveToFile(filename);
                break;
            case 7:
                phoneBook.loadFromFile(filename);
                break;
            case 8:
                cout << "Exiting the program...\n";
                return 0;
            default:
                cout << "Invalid option! Please try again.\n";
        }
    }
}

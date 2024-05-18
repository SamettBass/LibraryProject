#include "LibrarySystem.h"

User::User(const string& _username, const string& _password, int _userType) : username(_username), password(_password), userType(_userType) {}

string User::getUsername() const {
    return username;
}

int User::getUserType() const {
    return userType;
}

bool User::authenticate(const string& _password) const {
    return (password == _password);
}

Student::Student(const string& _username, const string& _password, const string& _school) : User(_username, _password, 0), school(_school) {}

string Student::getSchool() const {
    return school;
}


Lecturer::Lecturer(const string& _username, const string& _password) : User(_username, _password, 1) {}

PublicUser::PublicUser(const string& _username, const string& _password) : User(_username, _password, 2) {}

void UserManagement::addUser(User* user) {
    users.push_back(user);
}

User* UserManagement::getUserByUsername(const string& username) {
    for (auto& user : users) {
        if (user->getUsername() == username) {
            return user;
        }
    }
    return nullptr;
}

bool UserManagement::usernameExists(const string& username) {
    for (auto& user : users) {
        if (user->getUsername() == username) {
            return true;
        }
    }
    return false;
}

Resource::Resource(const string& _title) : title(_title), available(true), dueDate(0) {}

Resource::~Resource() {}

string Resource::getTitle() const {
    return title;
}

bool Resource::isAvailable() const {
    return available;
}

Book::Book(const string& _title, const string& _author, const string& _ISBN, int _pages) : Resource(_title), author(_author), ISBN(_ISBN), pages(_pages) {}

void Book::lendItem(User* user) {
    if (!isAvailable()) {
        cout << getTitle() << " is not available for lending." << endl;
        return;
    }

    time_t lendingPeriod = calculateLendingPeriod(user->getUserType());
    time_t lendDate = time(nullptr);
    dueDate = lendDate + lendingPeriod;

    available = false;
    cout << getTitle() << " lent successfully to " << user->getUsername() << ". Due date: " << ctime(&dueDate);
}

void Book::returnItem(User* user) {
    if (isAvailable()) {
        cout << getTitle() << " is already available." << endl;
        return;
    }
    available = true;
    cout << getTitle() << " returned successfully by " << user->getUsername() << "." << endl;
}

bool Book::isOverdue() const {
    return (!isAvailable() && dueDate < time(nullptr));
}

time_t Book::calculateLendingPeriod(int userType) const {
    if (userType == 2) {
        return 864000;
    } else if (userType == 1) {
        return 1296000;
    } else {
        return 2592000;
    }
}

DVD::DVD(const string& _title, const string& _director, const string& _format, int _duration, const string& _genre) : Resource(_title), director(_director), format(_format), duration(_duration), genre(_genre) {}

void DVD::lendItem(User* user) {
    if (!isAvailable()) {
        cout << getTitle() << " is not available for lending." << endl;
        return;
    }

    time_t lendingPeriod = calculateLendingPeriod(user->getUserType());
    time_t lendDate = time(nullptr);
    dueDate = lendDate + lendingPeriod;

    available = false;
    cout << getTitle() << " lent successfully to " << user->getUsername() << ". Due date: " << ctime(&dueDate);
}

void DVD::returnItem(User* user) {
    if (isAvailable()) {
        cout << getTitle() << " is already available." << endl;
        return;
    }
    available = true;
    cout << getTitle() << " returned successfully by " << user->getUsername() << "." << endl;
}

bool DVD::isOverdue() const {
    return (!isAvailable() && dueDate < time(nullptr));
}

time_t DVD::calculateLendingPeriod(int userType) const {
    if (userType == 2) {
        return 864000;
    } else if (userType == 1) {
        return 1296000;
    } else {
        return 2592000;
    }
}

Magazine::Magazine(const string& _title, const string& _publisher, int _issueNumber, int _issue) : Resource(_title), publisher(_publisher), issueNumber(_issueNumber), issue(_issue) {}

void Magazine::lendItem(User* user) {
    if (!isAvailable()) {
        cout << getTitle() << " is not available for lending." << endl;
        return;
    }

    time_t lendingPeriod = calculateLendingPeriod(user->getUserType());
    time_t lendDate = time(nullptr);
    dueDate = lendDate + lendingPeriod;

    available = false;
    cout << getTitle() << " lent successfully to " << user->getUsername() << ". Due date: " << ctime(&dueDate);
}

void Magazine::returnItem(User* user) {
    if (isAvailable()) {
        cout << getTitle() << " is already available." << endl;
        return;
    }
    available = true;
    cout << getTitle() << " returned successfully by " << user->getUsername() << "." << endl;
}

bool Magazine::isOverdue() const {
    return (!isAvailable() && dueDate < time(nullptr));
}

time_t Magazine::calculateLendingPeriod(int userType) const {
    if (userType == 2) {
        return 864000;
    } else if (userType == 1) {
        return 1296000;
    } else {
        return 2592000;
    }
}

LibrarySystem::LibrarySystem() : loggedInUser(nullptr) {}

void LibrarySystem::createAccount() {
    string username, password;
    int userType;
    cout << "Enter username: ";
    cin >> username;
    if (userManager.usernameExists(username)) {
        cout << "Username already exists. Please choose another username." << endl;
        return;
    }
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter user type (0 for student, 1 for lecturer, 2 for public): ";
    cin >> userType;

    if (userType < 0 || userType > 2) {
        cout << "Invalid user type. Account creation failed." << endl;
        return;
    }

    if (userType == 0) {
        string school;
        cout << "Enter school: ";
        cin >> school;
        userManager.addUser(new Student(username, password, school));
    } else if (userType == 1) {
        userManager.addUser(new Lecturer(username, password));
    } else if (userType == 2) {
        userManager.addUser(new PublicUser(username, password));
    }
    cout << "Account created successfully." << endl;
}

void LibrarySystem::login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    User* user = userManager.getUserByUsername(username);
    if (user != nullptr && user->authenticate(password)) {
        loggedInUser = user;
        cout << "Login successful. Welcome, " << loggedInUser->getUsername() << "!" << endl;
    } else {
        cout << "Invalid username or password. Login failed." << endl;
    }
}

void LibrarySystem::logout() {
    loggedInUser = nullptr;
    cout << "Logged out successfully." << endl;
}

void LibrarySystem::addResource(Resource* resource) {
    resources.push_back(resource);
}

void LibrarySystem::lendResource(const string& title) {
    if (loggedInUser == nullptr) {
        cout << "Please login first." << endl;
        return;
    }
    for (auto& resource : resources) {
        if (resource->isOverdue()) {
            cout << "This resource is overdue. Please return it before lending again." << endl;
            return;
        }
        if (resource->getTitle() == title) {
            resource->lendItem(loggedInUser);
            return;
        }
    }
    cout << "Resource not found." << endl;
}

void LibrarySystem::returnResource(const string& title) {
    if (loggedInUser == nullptr) {
        cout << "Please login first." << endl;
        return;
    }
    for (auto& resource : resources) {
        if (resource->getTitle() == title) {
            resource->returnItem(loggedInUser);
            return;
        }
    }
    cout << "Resource not found." << endl;
}

void LibrarySystem::showAvailableResources() {
    cout << "Available Resources:" << endl;

    vector<vector<Resource*>> resourceCategories(3);

    for (auto& resource : resources) {
        if (resource->isOverdue()) {
            continue;
        }
        if (dynamic_cast<Book*>(resource) != nullptr) {
            resourceCategories[0].push_back(resource);
        } else if (dynamic_cast<DVD*>(resource) != nullptr) {
            resourceCategories[1].push_back(resource);
        } else if (dynamic_cast<Magazine*>(resource) != nullptr) {
            resourceCategories[2].push_back(resource);
        }
    }

    if (!resourceCategories[0].empty()) {
        cout << "Books:" << endl;
        for (auto& resource : resourceCategories[0]) {
            cout << "- " << resource->getTitle() << endl;
        }
    }

    if (!resourceCategories[1].empty()) {
        cout << "DVDs:" << endl;
        for (auto& resource : resourceCategories[1]) {
            cout << "- " << resource->getTitle() << endl;
        }
    }

    if (!resourceCategories[2].empty()) {
        cout << "Magazines:" << endl;
        for (auto& resource : resourceCategories[2]) {
            cout << "- " << resource->getTitle() << endl;
        }
    }
}

void LibrarySystem::addNewItem(int itemType, const string& title, const string& additional1, const string& additional2, int additional3, const string& additional4) {
    Resource* newItem = nullptr;
    switch (itemType) {
        case 0:
            newItem = new Book(title, additional1, additional2, additional3);
            break;
        case 1:
            newItem = new DVD(title, additional1, additional2, additional3, additional4);
            break;
        case 2:
            newItem = new Magazine(title, additional1, additional3, stoi(additional2));
            break;
        default:
            cout << "Invalid item type. Item addition failed." << endl;
            return;
    }
    resources.push_back(newItem);
    cout << "New item '" << title << "' added successfully." << endl;
}

int main() {
    LibrarySystem library;

    Book book1("A Tale of Two Cities", "Charles Dickens", "9780743273565", 448);
    Book book2("Think and Grow Rich", "Napoleon Hill", "9780061120084", 238);
    DVD dvd1("Inception", "Christopher Nolan", "DVD", 148, "Science Fiction");
    DVD dvd2("The Dark Knight", "Christopher Nolan", "Blu-ray", 152, "Action");
    Magazine magazine1("National Geographic", "National Geographic Society", 202405, 1078);
    Magazine magazine2("Time", "Time USA, LLC", 202405, 96);

    library.addResource(&book1);
    library.addResource(&book2);
    library.addResource(&dvd1);
    library.addResource(&dvd2);
    library.addResource(&magazine1);
    library.addResource(&magazine2);

    while (true) {
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Logout" << endl;
        cout << "4. Lend Resource" << endl;
        cout << "5. Return Resource" << endl;
        cout << "6. Show Available Resources" << endl;
        cout << "7. Add New Item" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                library.createAccount();
                break;
            case 2:
                library.login();
                break;
            case 3:
                library.logout();
                break;
            case 4: {
                string title;
                cout << "Enter the title of the resource you want to lend: ";
                cin.ignore();
                getline(cin, title);
                library.lendResource(title);
                break;
            }
            case 5: {
                string title;
                cout << "Enter the title of the resource you want to return: ";
                cin.ignore();
                getline(cin, title);
                library.returnResource(title);
                break;
            }
            case 6:
                library.showAvailableResources();
                break;
            case 7: {
                int itemType;
                string title, additional1, additional2, additional4;
                int additional3;

                cout << "Enter item type (0 for Book, 1 for DVD, 2 for Magazine): ";
                cin >> itemType;
                cout << "Enter the title of the new item: ";
                cin.ignore();
                getline(cin, title);

                if (itemType == 0) {
                    cout << "Enter author: ";
                    getline(cin, additional1);
                    cout << "Enter ISBN: ";
                    getline(cin, additional2);
                    cout << "Enter number of pages: ";
                    cin >> additional3;
                } else if (itemType == 1) {
                    cout << "Enter director: ";
                    getline(cin, additional1);
                    cout << "Enter format: ";
                    getline(cin, additional2);
                    cout << "Enter duration (minutes): ";
                    cin >> additional3;
                    cout << "Enter genre: ";
                    cin.ignore();
                    getline(cin, additional4);
                } else if (itemType == 2) {
                    cout << "Enter publisher: ";
                    getline(cin, additional1);
                    cout << "Enter issue number: ";
                    getline(cin, additional2);
                    cout << "Enter issue: ";
                    cin >> additional3;
                } else {
                    cout << "Invalid item type." << endl;
                    break;
                }

                library.addNewItem(itemType, title, additional1, additional2, additional3, additional4);
                break;
            }
            case 8:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl;
    }

    return 0;
}

#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class User {
private:
    string username;
    string password;
    int userType;

public:
    User(const string& _username, const string& _password, int _userType);

    string getUsername() const;
    int getUserType() const;
    bool authenticate(const string& _password) const;
};

class Student : public User {
private:
    string school;

public:
    Student(const string& _username, const string& _password, const string& _school);

    string getSchool() const;
};

class Lecturer : public User {
public:
    Lecturer(const string& _username, const string& _password);
};

class PublicUser : public User {
public:
    PublicUser(const string& _username, const string& _password);
};

class UserManagement {
private:
    vector<User*> users;

public:
    void addUser(User* user);
    User* getUserByUsername(const string& username);
    bool usernameExists(const string& username);
};

class Resource {
protected:
    string title;
    bool available;
    time_t dueDate;

public:
    Resource(const string& _title);
    virtual ~Resource();

    string getTitle() const;
    virtual void lendItem(User* user) = 0;
    virtual void returnItem(User* user) = 0;
    virtual bool isOverdue() const = 0;
    bool isAvailable() const;
};

class Book : public Resource {
private:
    string author;
    string ISBN;
    int pages;

public:
    Book(const string& _title, const string& _author, const string& _ISBN, int _pages);

    void lendItem(User* user) override;
    void returnItem(User* user) override;
    bool isOverdue() const override;
    time_t calculateLendingPeriod(int userType) const;
};

class DVD : public Resource {
private:
    string director;
    string format;
    int duration;
    string genre;

public:
    DVD(const string& _title, const string& _director, const string& _format, int _duration, const string& _genre);

    void lendItem(User* user) override;
    void returnItem(User* user) override;
    bool isOverdue() const override;
    time_t calculateLendingPeriod(int userType) const;
};

class Magazine : public Resource {
private:
    string publisher;
    int issueNumber;
    int issue;

public:
    Magazine(const string& _title, const string& _publisher, int _issueNumber, int _issue);

    void lendItem(User* user) override;
    void returnItem(User* user) override;
    bool isOverdue() const override;
    time_t calculateLendingPeriod(int userType) const;
};

class LibrarySystem {
private:
    UserManagement userManager;
    vector<Resource*> resources;
    User* loggedInUser;

public:
    LibrarySystem();

    void createAccount();
    void login();
    void logout();
    void addResource(Resource* resource);
    void lendResource(const string& title);
    void returnResource(const string& title);
    void showAvailableResources();
    void addNewItem(int itemType, const string& title, const string& additional1, const string& additional2, int additional3, const string& additional4);
};

#endif // LIBRARYSYSTEM_H

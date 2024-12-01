#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>

class Account
{
private:
	std::string m_username;
	std::string m_password;
	int m_maxScore;
public:
	Account(std::string username, std::string password, int maxScore);
	~Account();

	std::string getUsername() const;
	std::string getPassword() const;
	int getMaxScore() const;
};

class AccountManager
{
private:
	static AccountManager* m_instance;
	
	std::vector<Account> m_accounts;
public:
	static AccountManager* getInstance();

	AccountManager(const std::string& filepath = "Resources/Accounts/Accounts.csv");
	~AccountManager();

	// if return false, third parameter Account* return nullptr;
	bool isPasswordCorrect(const std::string& username, const std::string& password, Account*& account);
	void writeToFile(const std::string& filepath = "Resources/Accounts/Accounts.csv");
};


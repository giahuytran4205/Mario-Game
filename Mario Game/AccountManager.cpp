#include "AccountManager.hpp"

Account::Account(std::string username, std::string password, int maxScore) : m_username(username), m_password(password), m_maxScore(maxScore) {}

Account::~Account()
{
}

std::string Account::getUsername() const
{
    return m_username;
}

std::string Account::getPassword() const
{
    return m_password;
}

int Account::getMaxScore() const
{
    return m_maxScore;
}

AccountManager* AccountManager::m_instance = nullptr;

AccountManager* AccountManager::getInstance()
{
	return m_instance;
}

AccountManager::AccountManager(const std::string& filepath)
{
    if (!m_instance) {
        m_instance = this;
    }

    std::ifstream fin(filepath);

    if (!fin.is_open()) {
        throw std::ios_base::failure("Failed to open file: " + filepath);
    }

    std::string header;
    std::getline(fin, header);

    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty() || std::all_of(line.begin(), line.end(), ::isspace)) { // pass empty line
            continue;
        }

        std::string username, password, maxScoreString;
        std::stringstream ss(line);
        std::getline(ss, username, ',');
        std::getline(ss, password, ',');
        std::getline(ss, maxScoreString, ',');
        int maxScore = 0;
        try {
            maxScore = std::stoi(maxScoreString);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Invalid number for maxScore: " << maxScoreString << std::endl;
            continue;
        }
        catch (const std::out_of_range& e) {
            std::cout << "Out of range for maxScore: " << maxScoreString << std::endl;
            continue;
        }
        m_accounts.push_back(Account(username, password, maxScore));
    }

    fin.close();

    std::cout << "Load AccountManager from File Successfully" << std::endl;
}

AccountManager::~AccountManager()
{
}

bool AccountManager::isPasswordCorrect(const std::string& username, const std::string& password, Account*& account)
{
    auto it = std::find_if(m_accounts.begin(), m_accounts.end(), [&username](const Account& account)
    {
        return account.getUsername() == username;
    });

    if (it != m_accounts.end())
    {
        if (it->getPassword() == password)
        {
            account = &(*it);
            return true;
        }
    }

    return false;
}

void AccountManager::writeToFile(const std::string& filepath)
{
    std::ofstream fout(filepath);

    if (!fout.is_open()) {
        throw std::ios_base::failure("Failed to open file: " + filepath);
    }

    fout << "Username,Password,MaxScore\n";

    for (const Account& account : m_accounts) {
        fout << account.getUsername() << ","
            << account.getPassword() << ","
            << account.getMaxScore() << "\n";
    }

    fout.close();

    std::cout << "Write AccountManager to File Successfully" << std::endl;
}

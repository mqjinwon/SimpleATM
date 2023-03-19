#include "../include/account.hpp"

Account::Account(const std::string pin_number) {
    pin_number_ = pin_number;
    // random number generator 8 digits
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000000, 99999999);
    account_number_ = std::to_string(dis(gen));
    balance_ = 0;
}

Account::Account(std::string pin_number, int balance) {
    pin_number_ = pin_number;
    // random number generator 8 digits
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000000, 99999999);
    account_number_ = std::to_string(dis(gen));
    balance_ = balance;
}

void Account::SetBalance(int balance) {
    balance_ = balance;
}

int Account::GetBalance() const {
    return balance_;
}

std::string Account::GetAccountNumber() const {
    return account_number_;
}
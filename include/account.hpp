#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <random>

class Account {
public:
    Account(const std::string pin_number);
    Account(std::string pin_number, int balance);

    void SetBalance(int balance);
    int GetBalance() const;

    std::string GetAccountNumber() const;

private:
    std::string pin_number_;
    std::string account_number_;
    int balance_;
};
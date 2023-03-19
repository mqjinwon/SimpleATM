#pragma once
//key value pair
#include <map>
#include <vector>

#include "../include/account.hpp"

class Bank {
public:
    enum ErrorCode {
        NO_ERROR = 0,
        PIN_IS_NOT_VALID,
        ACCOUNT_NOT_FOUND,
        ACCOUNT_NOT_SELECTED,
        ACCOUNT_ALREADY_EXISTS,
        INSUFFICIENT_FUNDS,
        ACCOUNT_HAS_FUNDS
    };
    Bank();
    Bank(std::map<std::string, std::vector<std::shared_ptr<Account> > > database);
    
    Bank::ErrorCode ValidPinNum(std::string pin_number);
    const std::vector<std::shared_ptr<Account> > GetAccountList(std::string pin_number);
    
    Bank::ErrorCode SelectAccount(std::string pin_number, int idx);
    void UnLinkAccount();

    Bank::ErrorCode Deposit(int amount);
    Bank::ErrorCode Withdraw(int amount);
    int GetBalance();

    Bank::ErrorCode MakeAccount(std::string pin_number, int balance);
    
private:
    // account array for multiple accounts
    std::map<std::string, std::vector<std::shared_ptr<Account> > > database_;

    std::shared_ptr<Account> selected_account_;
};
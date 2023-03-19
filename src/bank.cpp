#include "../include/bank.hpp"

Bank::Bank() {
    selected_account_ = nullptr;
}
Bank::Bank(std::map<std::string, std::vector<std::shared_ptr<Account> > > database) {
    database_ = database;
    selected_account_ = nullptr;
}

Bank::ErrorCode Bank::ValidPinNum(std::string pin_number) {
    if (database_.find(pin_number) != database_.end()) {
        return ErrorCode::NO_ERROR;
    }
    return ErrorCode::PIN_IS_NOT_VALID;
}

const std::vector<std::shared_ptr<Account> > Bank::GetAccountList(std::string pin_number) {
    if (database_.find(pin_number) != database_.end()) {
        return database_[pin_number];
    }
}

Bank::ErrorCode Bank::SelectAccount(std::string pin_number, int idx) {
    if (idx >= database_[pin_number].size() || idx < 0) {
        return ErrorCode::ACCOUNT_NOT_FOUND;
    }
    else{
        selected_account_ = database_[pin_number][idx];
        return ErrorCode::NO_ERROR;
    }
}

void Bank::UnLinkAccount() {
    selected_account_ = nullptr;
}

Bank::ErrorCode Bank::Deposit(int amount) {
    if (selected_account_ == nullptr) {
        return ErrorCode::ACCOUNT_NOT_SELECTED;
    }
    else{
        if (amount < 0) {
            return ErrorCode::INSUFFICIENT_FUNDS;
        }
        else{
            selected_account_->SetBalance(selected_account_->GetBalance() + amount);
            return ErrorCode::NO_ERROR;
        }
    }
}

Bank::ErrorCode Bank::Withdraw(int amount) {
    if (selected_account_ == nullptr) {
        return ErrorCode::ACCOUNT_NOT_SELECTED;
    }
    else{
        if (selected_account_->GetBalance() >= amount) {
            selected_account_->SetBalance(selected_account_->GetBalance() - amount);
            return ErrorCode::NO_ERROR;
        }
        return ErrorCode::INSUFFICIENT_FUNDS;
    }
}

int Bank::GetBalance() {
    return selected_account_->GetBalance();
}

Bank::ErrorCode Bank::MakeAccount(std::string pin_number, int balance) {

    bool is_exist = true;
    std::shared_ptr<Account> new_account;
    while (is_exist)
    {
        is_exist = false;
        new_account = std::make_shared<Account>(pin_number, balance);
        for (int i = 0; i < database_[pin_number].size(); i++) {
            if (database_[pin_number][i]->GetAccountNumber() == new_account->GetAccountNumber()) {
                is_exist = true;
            }
        }
    }

    database_[pin_number].push_back(new_account);
    std::string new_account_number = database_[pin_number].back()->GetAccountNumber();

    return ErrorCode::NO_ERROR;
}
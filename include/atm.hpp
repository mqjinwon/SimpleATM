#pragma once
#include <iostream>
#include <istream>
#include <chrono>
#include <thread>

#include "../include/bank.hpp"

class ATM {
    enum MenuOption {
        INIT = 0,
        VALID_PIN,
        SELECT_ACCOUNT,
        SELECT_MENU,
        DEPOSIT,
        WITHDRAW,
        BALANCE,
        EXIT
    };

public:
    ATM();
    void ConnectBank(std::shared_ptr<Bank> bank);
    void run();

private:
    void ShowMenu(ATM::MenuOption option);
    void Init();
    void ValidPin();
    void SelectAccount();
    void SelectMenu();
    void Deposit();
    void Withdraw();
    void Balance();
    void Exit();
    void ClearScreen();
    void ClearData();

    int option_;
    std::string pin_number_;
    std::shared_ptr<Bank> bank_;
};
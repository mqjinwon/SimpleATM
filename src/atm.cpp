#include "../include/atm.hpp"

ATM::ATM() {
    option_ = (int)ATM::MenuOption::INIT;

    // FIXME: It is just for test
    bank_ = std::make_shared<Bank>();
    bank_->MakeAccount("1234", 1000);
    bank_->MakeAccount("1234", 3000);
    bank_->MakeAccount("1234", 4000);
}

void ATM::ConnectBank(std::shared_ptr<Bank> bank) {
    bank_ = bank;
}

void ATM::run() {
    option_ = (int)ATM::MenuOption::INIT;

    while(1){
        ClearScreen();
        ShowMenu((ATM::MenuOption)option_);
    }
}

void ATM::ShowMenu(ATM::MenuOption option) {
    switch (option){
        case ATM::MenuOption::INIT:
            Init();
            break;
        case ATM::MenuOption::VALID_PIN:
            ValidPin();
            break;
        case ATM::MenuOption::SELECT_ACCOUNT:
            SelectAccount();
            break;
        case ATM::MenuOption::SELECT_MENU:
            SelectMenu();
            break;
        case ATM::MenuOption::DEPOSIT:
            Deposit();
            break;
        case ATM::MenuOption::WITHDRAW:
            Withdraw();
            break;
        case ATM::MenuOption::BALANCE:
            Balance();
            break;
        case ATM::MenuOption::EXIT:
            Exit();
            break;
        default:
            break;
    }
}

void ATM::Init() {
    std::cout << "========================================" << std::endl;
    std::cout << "Welcome to our bear robotics bank" << std::endl;
    std::cout << "Please insert your card below the reader" << std::endl;
    std::cout << "If you insert your card, please press 1" << std::endl;
    std::cout << "If you want to exit, please press 0" << std::endl;
    std::cout << "========================================" << std::endl;

    while(true){
        std::cout << "Option: ";
        std::cin >> option_;
        if (option_ >= 2){
            std::cout << "Please insert a valid option" << std::endl;
        }
        else{
            break;
        }
    }
}

void ATM::ValidPin(){
    std::string pin_number;
    std::cout << "========================================" << std::endl;
    std::cout << "Please write card pin number" << std::endl;
    std::cout << "========================================" << std::endl;

    for (int i = 0; i < 3; i++){
        std::cout << "Pin number: ";
        std::cin >> pin_number;
        Bank::ErrorCode status = bank_->ValidPinNum(pin_number);

        if (status == Bank::ErrorCode::NO_ERROR){
            pin_number_ = pin_number;
            option_ = (int)ATM::MenuOption::SELECT_ACCOUNT;
            break;
        }
        else{
            std::cout << "Please insert a valid pin number" << std::endl;
            std::cout << "You have " << 2 - i << " attempts left" << std::endl;
        }
        option_ = (int)ATM::MenuOption::EXIT;
    }
}

void ATM::SelectAccount(){
    std::cout << "========================================" << std::endl;
    std::cout << "Please select an account" << std::endl;
    auto account_list = bank_->GetAccountList(pin_number_);
    for (int i = 0; i < account_list.size(); i++){
        std::string account_number = account_list[i]->GetAccountNumber();
        std::cout << i + 1 << ". " << account_number.substr(0,4) << "-" << account_number.substr(4,8) << std::endl;
    }
    std::cout << "========================================" << std::endl;

    int number;
    while (true)
    {
        std::cout << "number: ";
        std::cin >> number;
        Bank::ErrorCode status = bank_->SelectAccount(pin_number_, number-1);
        if (status == Bank::ErrorCode::ACCOUNT_NOT_FOUND)
        {
            std::cout << "Please write valid number" << std::endl;
        }
        else{
            break;
        }
    }
    option_ = (int)ATM::MenuOption::SELECT_MENU;
}

void ATM::SelectMenu(){
    std::cout << "========================================" << std::endl;
    std::cout << "Please select an option" << std::endl;
    std::cout << "1. Deposit" << std::endl;
    std::cout << "2. Withdraw" << std::endl;
    std::cout << "3. Balance" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "========================================" << std::endl;

    while(true){
        std::cout << "Option: ";
        std::cin >> option_;
        if (option_ >= 5){
            std::cout << "Please insert a valid option" << std::endl;
        }
        else{
            option_ += (int)ATM::SELECT_MENU;
            break;
        }
    }
}

void ATM::Deposit() {
    std::cout << "========================================" << std::endl;
    std::cout << "Please, insert the amount you want to deposit" << std::endl;
    std::cout << "Your balance: " << bank_->GetBalance() << "$" << std::endl;
    std::cout << "========================================" << std::endl;

    int money;
    while (true)
    {
        std::cout << "$: ";
        std::cin >> money;
        Bank::ErrorCode status = bank_->Deposit(money);

        if (status == Bank::ErrorCode::NO_ERROR){
            std::cout << "Deposit completed" << std::endl;
            std::cout << "Your balance: " << bank_->GetBalance() << "$" << std::endl;
            break;
        }
        else{
            if (status == Bank::ErrorCode::INSUFFICIENT_FUNDS)
            std::cout << "Please insert a valid amount" << std::endl;
        }
    }    
    
    //sleep time 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));

    option_ = ATM::MenuOption::SELECT_MENU;
}

void ATM::Withdraw() {
    std::cout << "========================================" << std::endl;
    std::cout << "Please, insert the amount you want to withdraw" << std::endl;
    std::cout << "Your balance: " << bank_->GetBalance() << "$" << std::endl;
    std::cout << "========================================" << std::endl;

    int money;
    while (true)
    {
        std::cout << "$: ";
        std::cin >> money;
        Bank::ErrorCode status = bank_->Withdraw(money);

        if (status == Bank::ErrorCode::NO_ERROR){
            std::cout << "Withdraw completed" << std::endl;
            std::cout << "Your balance: " << bank_->GetBalance() << "$" << std::endl;
            break;
        }
        else{
            if (status == Bank::ErrorCode::INSUFFICIENT_FUNDS)
            std::cout << "Please insert a valid amount" << std::endl;
        }
    }

    //sleep time 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));

    option_ = ATM::MenuOption::SELECT_MENU;
}

void ATM::Balance() {
    std::cout << "Your balance: " << bank_->GetBalance() << "$" << std::endl;
    option_ = ATM::MenuOption::SELECT_MENU;

    //sleep time 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void ATM::Exit() {
    std::cout << "Thank you for using our bear robotics bank" << std::endl;
    ClearData();
    // sleep time 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
    option_ = (int)ATM::MenuOption::INIT;

}

void ATM::ClearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void ATM::ClearData() {
    pin_number_ = "";
}
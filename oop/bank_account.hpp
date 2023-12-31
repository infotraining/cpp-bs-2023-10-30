#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace Banking
{
    enum class TransactionType : char { withdraw = 'W',
        deposit = 'D' };

    struct Transaction
    {
        uint32_t id;
        TransactionType type;
        double amount;

        bool operator==(const Transaction& other) const = default; // C++20
    };

    // inline bool operator==(const Transaction& t1, const Transaction& t2)
    // {
    //     return t1.id == t2.id && t1.type == t2.type && t1.amount == t2.amount;
    // }

    // inline bool operator!=(const Transaction& t1, const Transaction& t2)
    // {
    //     return !(t1 == t2);
    // }

    struct InsufficientFundsException : public std::runtime_error
    {
        uint32_t account_id;
        double amount;
        double current_balance;

        InsufficientFundsException(uint32_t id, double amount, double balance)
            : std::runtime_error("Insufficient funds for account: " + std::to_string(id))
            , account_id{id}
            , amount{amount}
            , current_balance{balance}
        { }
    };

    class BankAccount
    {
    private:
        const uint32_t id_;
        std::string owner_;
        double balance_;
        std::vector<Transaction> history_;

        inline static double interest_rate_ = 0.05;

    public:
        static void set_interest_rate(double interest_rate)
        {
            interest_rate_ = interest_rate;
        }

        BankAccount(uint32_t id, const std::string& owner, double balance = 0.0);

        uint32_t id() const
        {
            return id_;
        }

        std::string owner() const
        {
            return this->owner_;
        }

        void set_owner(const std::string& new_owner);

        double balance() const
        {
            return balance_;
        }

        void deposit(double amount)
        {
            assert(amount > 0);
            balance_ += amount;
            history_.push_back(Transaction{id_, TransactionType::deposit, amount});
        }

        void withdraw(double amount)
        {
            assert(amount > 0);

            if (amount > balance_)
                throw InsufficientFundsException{id_, amount, balance_};

            balance_ -= amount;
            history_.push_back(Transaction{id_, TransactionType::withdraw, amount});
        }

        void pay_interest(uint32_t days)
        {
            double interest = balance_ * interest_rate_ * (days / 365.0);
            balance_ += interest;
        }

        void print() const
        {
            std::cout << "ID: " << id_ << "; Owner: " << owner_ << "; Balance: " << balance_ << ";\n";
        }

        const std::vector<Transaction>& transactions() const
        {
            return history_;
        }

        friend std::ostream& operator<<(std::ostream& out, const BankAccount& account)
        {
            return out << "BankAccount{ID: " << account.id_
                       << "; Owner: " << account.owner_
                       << "; Balance: " << account.balance_ << "}";
        }
    };
} // namespace Banking

#endif // BANK_ACCOUNT_HPP
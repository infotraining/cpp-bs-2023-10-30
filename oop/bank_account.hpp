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

    class BankAccount
    {
    private:
        const uint32_t id_;
        std::string owner_;
        double balance_;
        std::vector<Transaction> history_;

    public:
        BankAccount(uint32_t id, const std::string& owner, double balance);

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
            balance_ -= amount;
            history_.push_back(Transaction{id_, TransactionType::withdraw, amount});
        }

        void print() const
        {
            std::cout << "ID: " << id_ << "; Owner: " << owner_ << "; Balance: " << balance_ << ";\n";
        }

        std::vector<Transaction> transactions() const
        {
            return history_;
        }
    };
} // namespace Banking

#endif // BANK_ACCOUNT_HPP
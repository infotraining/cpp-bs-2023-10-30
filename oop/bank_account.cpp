#include "bank_account.hpp"

namespace Banking
{
    BankAccount::BankAccount(uint32_t id, const std::string& owner, double balance)
        : id_{id}
        , owner_{owner}
        , balance_{balance}
    {
    }

    void BankAccount::set_owner(const std::string& new_owner)
    {
        owner_ = new_owner;
    }

} // namespace Banking

#include "bank_account.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

struct Date
{
    int day, month, year;

    std::string to_string() const
    {
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }
};

TEST_CASE("struct - aggregates")
{
    const Date today{31, 10, 2023}; // aggregate initialization {}
    std::cout << today.to_string() << "\n";

    Date just_day{31}; // {31, 0, 0}
    std::cout << just_day.to_string() << "\n";

    Date zero{};
    std::cout << zero.to_string() << "\n";

    Date year{.year = 2023}; // designated initializers - C++20
    std::cout << year.to_string() << "\n";
}

using namespace Banking;

TEST_CASE("BankAccount - construction")
{
    BankAccount account_1{1, "Jan Kowalski", 100.0};

    CHECK(account_1.id() == 1);
    CHECK(account_1.owner() == "Jan Kowalski");
    CHECK(account_1.balance() == 100.0);

    account_1.set_owner("Jan Nowak-Kowalski");
    CHECK(account_1.owner() == "Jan Nowak-Kowalski");
}

TEST_CASE("BankAccount - using account")
{
    BankAccount account{1, "JK", 1000.0};

    SECTION("deposit")
    {
        account.deposit(100.0);

        CHECK(account.balance() == 1100.0);
    }

    SECTION("withdraw")
    {
        account.withdraw(100.0);

        CHECK(account.balance() == 900.0);
    }

    account.print();
}

TEST_CASE("BankAccount - transactions")
{
    BankAccount account{1, "AN", 1000.0};

    account.deposit(100.0);
    account.deposit(200.0);
    account.withdraw(150.0);

    const auto& history = account.transactions();

    CHECK(history == std::vector{
    	Transaction{1, TransactionType::deposit, 100.0},
    	Transaction{1, TransactionType::deposit, 200.0},
    	Transaction{1, TransactionType::withdraw, 150.0}
    });

	std::cout << account << "\n";
}

TEST_CASE("BankAccount - interests")
{
	BankAccount::set_interest_rate(0.1);

	BankAccount account{1, "AN", 1000.0};

	account.pay_interest(365);

	CHECK(account.balance() == 1100.0);
}

TEST_CASE("BankAccount - exceptions")
{
    BankAccount account{1, "AN", 100.0};

    try
    {
        account.withdraw(1'000'000);
    }
    catch(const InsufficientFundsException& e)
    {
        std::cerr << e.what() << "\n";

        CHECK(e.account_id == 1);
        CHECK(e.amount == 1'000'000);
        CHECK(e.current_balance == 100.0);
    }
}

TEST_CASE("operator ==")
{
	Transaction t1{1, TransactionType::deposit, 100.0};
	Transaction t2{1, TransactionType::deposit, 100.0};

	CHECK(t1 == t2);
	CHECK(t1 != Transaction{2, TransactionType::deposit, 200.0});
}

struct Person
{
	std::string name;
	int age;

	Person() : name("unknown"), age(18) // default constructor 
	{}

	Person(const std::string& name) : name(name), age(18)
	{
	}
};

TEST_CASE("Person")
{
	Person p;

	CHECK(p.name == "unknown");
	CHECK(p.age == 18);
}
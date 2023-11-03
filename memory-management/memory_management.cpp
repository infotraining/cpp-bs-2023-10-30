#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std::literals;

namespace StackFriendly
{
    struct Gadget
    {
        std::string name;

        Gadget(const std::string& n = "not-set") // constructor
            : name(n)
        {
            std::cout << "Gadget(" << name << ": @" << this << ")\n";
        }

        // copy
        Gadget(const Gadget&) = default;
        Gadget& operator=(const Gadget&) = default;

        // move
        Gadget(Gadget&&) = default;
        Gadget& operator=(Gadget&&) = default;

        ~Gadget() // destructor
        {
            std::cout << "~Gadget(" << name << ": @" << this << ")\n";
        }

        void use()
        {
            std::cout << "Using " << name << ": @" << this << "\n";
        }
    };

    Gadget create_gadget()
    {
        static int id = 0;
        Gadget g("gadget-"s + std::to_string(++id));
        return g;
    }
} // namespace StackFriendly

TEST_CASE("stack")
{
    using namespace StackFriendly;

    Gadget g1_on_stack("ipad");
    g1_on_stack.use();

    Gadget g2 = create_gadget();
    g2.use();
}

namespace HeapOnly
{
    struct Gadget
    {
        std::string name;

        Gadget(const std::string& n = "not-set") // constructor
            : name(n)
        {
            std::cout << "Gadget(" << name << ": @" << this << ")\n";
        }

        // copy
        Gadget(const Gadget&) = delete;
        Gadget& operator=(const Gadget&) = delete;

        // move
        Gadget(Gadget&&) = delete;
        Gadget& operator=(Gadget&&) = delete;

        ~Gadget() // destructor
        {
            std::cout << "~Gadget(" << name << ": @" << this << ")\n";
        }

        void use()
        {
            std::cout << "Using " << name << ": @" << this << "\n";
        }
    };

    namespace Legacy
    {
        Gadget* create_gadget()
        {
            static int id = 0;
            Gadget* ptr_g = new Gadget("gadget-"s + std::to_string(++id));
            return ptr_g;
        }
    } // namespace Legacy

	std::unique_ptr<Gadget> create_gadget()
	{
		static int id = 0;
        auto ptr_g = std::make_unique<Gadget>("gadget-"s + std::to_string(++id));
        return ptr_g;
	}

	void use(Gadget* g) // Gadget* - non-owning pointer
	{
		if (g)
			g->use();
	}

	void use(std::unique_ptr<Gadget> g) // sink
	{
		if (g)
			g->use();
	}

} // namespace HeapOnly

TEST_CASE("heap")
{
    using namespace HeapOnly;

    SECTION("legacy - C++98")
    {
        Gadget* ptr_g1 = Legacy::create_gadget();
        ptr_g1->use();

        delete ptr_g1;
    }

	SECTION("modern - since C++11")
	{
		std::unique_ptr<Gadget> ptr_g1 = create_gadget();
		ptr_g1->use();

		std::unique_ptr<Gadget> ptr_g2 = std::move(ptr_g1);
		CHECK(ptr_g1 == nullptr);
		ptr_g2->use();

		use(ptr_g2.get());

		use(std::move(ptr_g2));
		CHECK(ptr_g2 == nullptr);
	}

	SECTION("vector unique_ptrs")
	{
		std::unique_ptr<Gadget> ptr_g3(Legacy::create_gadget());
		ptr_g3->use();

		std::vector<std::unique_ptr<Gadget>> gadgets;
		gadgets.push_back(std::move(ptr_g3));
		gadgets.push_back(create_gadget());
		gadgets.push_back(create_gadget());
		gadgets.push_back(create_gadget());
		gadgets.push_back(create_gadget());

		for(const auto& g : gadgets)
			g->use();
	}

	SECTION("shared_ptr")
	{
		std::shared_ptr<Gadget> ptr_g = std::make_shared<Gadget>("ipad-1"); // rc == 1

		{ 
			std::shared_ptr<Gadget> other_ptr_g = ptr_g; // rc == 2
			CHECK(ptr_g.use_count() == 2);
		} // rc == 1

	} // rc == 0 -> deallocation of object
}
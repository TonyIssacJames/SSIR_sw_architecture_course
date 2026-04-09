#include <iostream>
#include <memory>
#include <string>

// Component Interface
class Coffee {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Coffee() = default;
};

// Concrete Component
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override { return "Simple Coffee"; }
    double cost() const override { return 2.00; }
};

// Base Decorator
class CoffeeDecorator : public Coffee {
protected:
    std::unique_ptr<Coffee> wrappedCoffee;
public:
    CoffeeDecorator(std::unique_ptr<Coffee> c) : wrappedCoffee(std::move(c)) {}
    std::string getDescription() const override { return wrappedCoffee->getDescription(); }
    double cost() const override { return wrappedCoffee->cost(); }
};

// Concrete Decorators
class Milk : public CoffeeDecorator {
public:
    Milk(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    std::string getDescription() const override { return wrappedCoffee->getDescription() + ", Milk"; }
    double cost() const override { return wrappedCoffee->cost() + 0.50; }
};

class Mocha : public CoffeeDecorator {
public:
    Mocha(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    std::string getDescription() const override { return wrappedCoffee->getDescription() + ", Mocha"; }
    double cost() const override { return wrappedCoffee->cost() + 0.75; }
};


class ExtraSugar : public CoffeeDecorator {
public:
    ExtraSugar(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    std::string getDescription() const override { return wrappedCoffee->getDescription() + ", ExtraSugar"; }
    double cost() const override { return wrappedCoffee->cost() + 0.25; }
};

int main() {
    // Start with a base object
    std::unique_ptr<Coffee> myCoffee = std::make_unique<SimpleCoffee>();

    std::unique_ptr<Coffee> myCoffee1 = std::make_unique<SimpleCoffee>();

    myCoffee1 = std::make_unique<CoffeeDecorator>(std::move(myCoffee1));

    std::cout << "Order: " << myCoffee1->getDescription() << "\n"; // Simple Coffee, Milk, Mocha
    std::cout << "Total: $" << myCoffee1->cost() << "\n";          // $3.25
    
    // Wrap it in decorators dynamically
    myCoffee = std::make_unique<Milk>(std::move(myCoffee));
    myCoffee = std::make_unique<Mocha>(std::move(myCoffee));
    myCoffee = std::make_unique<ExtraSugar>(std::move(myCoffee));

    std::cout << "Order: " << myCoffee->getDescription() << "\n"; // Simple Coffee, Milk, Mocha
    std::cout << "Total: $" << myCoffee->cost() << "\n";          // $3.25
    return 0;
}
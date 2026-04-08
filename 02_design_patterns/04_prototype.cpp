#include <iostream>
#include <memory>
#include <string>

// Prototype Interface
class Monster {
public:
    virtual std::unique_ptr<Monster> clone() const = 0;
    virtual void printDetails() const = 0;
    virtual ~Monster() = default;
};

// Concrete Prototype
class Orc : public Monster {
private:
    int health;
    std::string weapon;

public:
    Orc(int h, std::string w) : health(h), weapon(std::move(w)) {}

    // The core of the Prototype pattern: cloning oneself
    std::unique_ptr<Monster> clone() const override {
        return std::make_unique<Orc>(*this); // Uses default copy constructor
    }

    void printDetails() const override {
        std::cout << "Orc with " << health << " health holding a " << weapon << "\n";
    }

    void setHealth(int newHealth) { health = newHealth; }
    void setWeapon(std::string newWeapon) { weapon = std::move(newWeapon); }
};

int main() {
    // Create an initial prototype (maybe an expensive operation)
    std::unique_ptr<Orc> baseOrc = std::make_unique<Orc>(100, "Rusty Axe");

    // Clone it cheaply to create a new instance
    std::unique_ptr<Monster> clonedOrc = baseOrc->clone();
    
    // Modify the clone slightly if needed
    auto specificOrc = static_cast<Orc*>(clonedOrc.get());
    specificOrc->setWeapon("Steel Sword");

    std::unique_ptr<Monster> tempClone = specificOrc->clone();
    auto specificOrc1 = static_cast<Orc*>(tempClone.get());
    specificOrc1->setHealth(200);
    specificOrc1->setWeapon("Shot Gun");



    baseOrc->printDetails();   // Orc with 100 health holding a Rusty Axe
    specificOrc->printDetails(); // Orc with 100 health holding a Steel Sword
    specificOrc1->printDetails();


    return 0;
}
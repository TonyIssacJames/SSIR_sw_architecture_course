#include <iostream>
#include <memory>

// Abstract Products
class Button { public: virtual void click() = 0; virtual ~Button() = default; };
class Checkbox { public: virtual void toggle() = 0; virtual ~Checkbox() = default; };

// Concrete Products (Windows Family)
class WinButton : public Button { public: void click() override { std::cout << "Windows Button Clicked\n"; } };
class WinCheckbox : public Checkbox { public: void toggle() override { std::cout << "Windows Checkbox Toggled\n"; } };

// Concrete Products (Mac Family)
class MacButton : public Button { public: void click() override { std::cout << "Mac Button Clicked\n"; } };
class MacCheckbox : public Checkbox { public: void toggle() override { std::cout << "Mac Checkbox Toggled\n"; } };

// Abstract Factory
class GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};

// Concrete Factories
class WinFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override { return std::make_unique<WinButton>(); }
    std::unique_ptr<Checkbox> createCheckbox() override { return std::make_unique<WinCheckbox>(); }
};

class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override { return std::make_unique<MacButton>(); }
    std::unique_ptr<Checkbox> createCheckbox() override { return std::make_unique<MacCheckbox>(); }
};

int main() {
    // Easily swap between WinFactory and MacFactory here
    std::unique_ptr<GUIFactory> factory = std::make_unique<MacFactory>(); 
    
    auto button = factory->createButton();
    auto checkbox = factory->createCheckbox();
    
    button->click();
    checkbox->toggle();
    return 0;
}
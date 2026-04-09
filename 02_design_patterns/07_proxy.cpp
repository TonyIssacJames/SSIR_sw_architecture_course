#include <iostream>
#include <memory>
#include <string>
#include <thread> // Required for sleep
#include <chrono> // Required for time units

// Subject Interface
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() = default;
};

// Real Subject (Expensive to create)
class HighResImage : public Image {
private:
    std::string filename;
    void loadFromDisk() {
        std::cout << "Loading massive image payload for " << filename << "... (Takes 10 seconds)\n";
        // The modern way to sleep
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
public:
    HighResImage(std::string fn) : filename(std::move(fn)) {
        loadFromDisk(); // Expensive operation happens immediately on construction
    }
    void display() override {
        std::cout << "Displaying HighResImage: " << filename << "\n";
    }
};

// Proxy
class ProxyImage : public Image {
private:
    std::string filename;
    std::unique_ptr<HighResImage> realImage; // The proxy holds a pointer to the real object
public:
    ProxyImage(std::string fn) : filename(std::move(fn)) {
        std::cout << "Proxy created for " << filename << ". No expensive loading yet.\n";
    }
    
    void display() override {
        // Lazy initialization: Only load the real image when explicitly asked to display
        if (!realImage) {
            realImage = std::make_unique<HighResImage>(filename);
        }
        realImage->display();
    }
};

int main() {
    std::cout << "--- Client asks for an image ---\n";
    std::unique_ptr<Image> image = std::make_unique<ProxyImage>("milky_way_4k.png");
    
    std::cout << "\n--- Client does some other work ---\n";
    
    std::cout << "\n--- Client finally needs to see the image ---\n";
    image->display(); // The actual loading happens here
    
    std::cout << "\n--- Client displays it again ---\n";
    image->display(); // It's already loaded, so it just displays instantly
    
    return 0;
}
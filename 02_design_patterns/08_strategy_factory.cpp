#include <iostream>
#include <memory>
#include <string>

// --- 1. THE STRATEGIES (The Drill Bits) ---
class CompressionStrategy {
public:
    virtual ~CompressionStrategy() = default;
    virtual void compress() = 0;
};

class JpegCompression : public CompressionStrategy {
public:
    void compress() override { std::cout << "Compressing using JPEG algorithm...\n"; }
};

class RawCompression : public CompressionStrategy {
public:
    void compress() override { std::cout << "Saving as RAW (no compression)...\n"; }
};

class PngCompression : public CompressionStrategy {
public:
    void compress() override { std::cout << "Saving as PNG (lossless)...\n"; }
};


// --- 2. THE FACTORY (The Hardware Store Employee) ---
class CompressionFactory {
public:
    // This is the ONLY place in the whole program where the if-else lives!
    static std::unique_ptr<CompressionStrategy> createStrategy(const std::string& format) {
        if (format == "JPEG") {
            return std::make_unique<JpegCompression>();
        } else if (format == "RAW") {
            return std::make_unique<RawCompression>();
        } else if (format == "PNG") {
            return std::make_unique<PngCompression>();
        } else {
            std::cout << "Format not supported!\n";
            return nullptr;
        }
    }
};


// --- 3. THE CONTEXT (The Power Drill) ---
class Camera {
private:
    std::unique_ptr<CompressionStrategy> strategy;

public:
    // The camera just talks to the Factory now.
    void setFormat(const std::string& format) {
        // The factory handles the creation, the camera just takes the result
        strategy = CompressionFactory::createStrategy(format);
    }

    void capture() {
        if (strategy) {
            strategy->compress();
        }
    }
};


// --- 4. THE REAL WORLD ---
int main() {
    Camera myPhone;

    // Look how clean this is! 
    // The main program doesn't even know that the class "JpegCompression" exists.
    // It just asks for "JPEG".
    
    std::cout << "User selects JPEG:\n";
    myPhone.setFormat("JPEG");
    myPhone.capture();

    std::cout << "\nUser selects PNG:\n";
    myPhone.setFormat("PNG");
    myPhone.capture();

    return 0;
}
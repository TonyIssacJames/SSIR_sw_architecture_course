#include <iostream>
#include <memory>

// The Strategy Interface
class CompressionStrategy {
public:
    virtual ~CompressionStrategy() = default;
    virtual void compress() = 0;
};

// Concrete Strategy A
class JpegCompression : public CompressionStrategy {
public:
    void compress() override { std::cout << "Compressing using JPEG algorithm...\n"; }
};

// Concrete Strategy B
class RawCompression : public CompressionStrategy {
public:
    void compress() override { std::cout << "Saving as RAW (no compression)...\n"; }
};


// Concrete Strategy C
class PngCompression : public CompressionStrategy {
public:
    void compress() override { std::cout << "Compressing using PNG algorithm...\n"; }
};

// The Context
class Camera {
private:
    std::unique_ptr<CompressionStrategy> strategy;
public:
    void setStrategy(std::unique_ptr<CompressionStrategy> s) { strategy = std::move(s); }
    void capture() {
        if (strategy) strategy->compress();
    }
};

int main() {
    Camera myPhone;
// 1. You snap a quick photo for social media
    std::cout << "--- Standard Mode ---\n";
    myPhone.setStrategy(std::make_unique<JpegCompression>());
    myPhone.capture(); 

    // 2. You switch to "Pro Mode" in your camera settings for a landscape shot
    std::cout << "\n--- Pro Mode ---\n";
    myPhone.setStrategy(std::make_unique<RawCompression>());
    myPhone.capture(); 

    // 3. You take a screenshot that needs a transparent background
    std::cout << "\n--- Screenshot Mode ---\n";
    myPhone.setStrategy(std::make_unique<PngCompression>()); 
    myPhone.capture();
}
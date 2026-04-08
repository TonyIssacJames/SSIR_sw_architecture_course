#include <iostream>
#include <memory>

// Product Interface
class Document {
public:
    virtual void open() = 0;
    virtual ~Document() = default;
};

// Concrete Products
class PdfDocument : public Document {
public:
    void open() override { std::cout << "Opening PDF Document...\n"; }
};

class WordDocument : public Document {
public:
    void open() override { std::cout << "Opening Word Document...\n"; }
};

// Creator Interface
class DocumentCreator {
public:
    virtual std::unique_ptr<Document> createDocument() = 0; // The Factory Method
    virtual ~DocumentCreator() = default;
};

// Concrete Creators
class PdfCreator : public DocumentCreator {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<PdfDocument>();
    }
};

class WordCreator : public DocumentCreator {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<WordDocument>();
    }
};

int main() {
    std::unique_ptr<DocumentCreator> creator = std::make_unique<PdfCreator>();
    std::unique_ptr<Document> doc = creator->createDocument();
    doc->open(); // Outputs: Opening PDF Document...
    return 0;
}
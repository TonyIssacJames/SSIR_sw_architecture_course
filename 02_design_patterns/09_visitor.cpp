#include <iostream>
#include <vector>

class TextElement;
class ImageElement;

// The Visitor Interface
class Visitor {
public:
    virtual void visit(TextElement* t) = 0;
    virtual void visit(ImageElement* i) = 0;
};

// Element Interface
class Element {
public:
    virtual void accept(Visitor* v) = 0;
};

class TextElement : public Element {
public:
    void accept(Visitor* v) override { v->visit(this); }
};

class ImageElement : public Element {
public:
    void accept(Visitor* v) override { v->visit(this); }
};

// Concrete Visitor logic
// --- 5. VISITOR 1: The HTML Worker ---
class Export2HTMLVisitor : public Visitor {
public:
    void visit(TextElement* t) override { std::cout << "Exporting Text to HTML...\n"; }
    void visit(ImageElement* i) override { std::cout << "Exporting Image to HTML...\n"; }
};

// --- 6. VISITOR 2: The PDF Worker (Brand New!) ---
class Export2PDFVisitor : public Visitor {
public:
    void visit(TextElement* t) override { std::cout << "Compressing and exporting Text to PDF...\n"; }
    void visit(ImageElement* i) override { std::cout << "Rendering and exporting Image to PDF...\n"; }
};

#if 0
int main() {
    TextElement docPart;
    Export2HTMLVisitor exporter;
    docPart.accept(&exporter);


    exporter.visit(&docPart); //single dispatch wiill work here
}

#else
// --- 7. The Main Program ---
int main() {
    // Create a list of generic elements representing our document
    std::vector<Element*> document;
    document.push_back(new TextElement());
    document.push_back(new ImageElement());

    // Instantiate our two different visitors
    Export2HTMLVisitor htmlExporter;
    Export2PDFVisitor pdfExporter;

    // --- First, we run the HTML Exporter on every item ---
    std::cout << "=== Running HTML Export ===\n";
    for (Element* item : document) {
        // Double dispatch figures out the identity and runs HTML logic
        item->accept(&htmlExporter); 
    }

    // --- Next, we run the PDF Exporter on every item ---
    std::cout << "\n=== Running PDF Export ===\n";
    for (Element* item : document) {
        // Double dispatch figures out the identity and runs PDF logic
        item->accept(&pdfExporter); 
    }

    // Memory cleanup (Standard C++ practice when using 'new')
    for (Element* item : document) {
        delete item;
    }

    return 0;
}
#endif
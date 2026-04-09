#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Component Interface
class FileSystemEntity {
public:
    virtual void display(int depth = 0) const = 0;
    virtual ~FileSystemEntity() = default;
};

// Leaf
class File : public FileSystemEntity {
private:
    std::string name;
public:
    File(std::string n) : name(std::move(n)) {}
    void display(int depth = 0) const override {
        std::cout << std::string(depth, '-') << " File: " << name << "\n";
    }
};

// Composite
class Directory : public FileSystemEntity {
private:
    std::string name;
    std::vector<std::unique_ptr<FileSystemEntity>> children;
public:
    Directory(std::string n) : name(std::move(n)) {}
    
    void add(std::unique_ptr<FileSystemEntity> entity) {
        children.push_back(std::move(entity));
    }

    void display(int depth = 0) const override {
        std::cout << std::string(depth, '-') << " Directory: " << name << "\n";
        // The composite delegates the work to its children
        for (const auto& child : children) {
            child->display(depth + 2);
        }
    }
};

int main() {
    auto root = std::make_unique<Directory>("Root");
    auto docs = std::make_unique<Directory>("Documents");
    
    // 1. Get a "view" (raw pointer) before moving
    Directory* docsPtr = docs.get();

    docs->add(std::make_unique<File>("resume.pdf"));
    docs->add(std::make_unique<File>("budget.xlsx"));
    docs->add(std::make_unique<File>("budget1.xlsx"));
    
    root->add(std::move(docs));

    // 3. You can still use the raw pointer!
    docsPtr->add(std::make_unique<File>("new_report.docx"));
    root->add(std::make_unique<File>("readme.txt"));


    
    // Client treats the entire tree uniformly
    root->display();
    return 0;
}
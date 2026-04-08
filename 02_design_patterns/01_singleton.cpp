#include <iostream>

class ConfigurationManager {
public:
    // Global point of access
    static ConfigurationManager& getInstance() {
        static ConfigurationManager instance; // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent duplicates
    ConfigurationManager(const ConfigurationManager&) = delete;
    void operator=(const ConfigurationManager&) = delete;

    void printConfig() {
        std::cout << "Reading configuration...\n";
    }

private:
    // Private constructor prevents direct instantiation
    ConfigurationManager() {
        std::cout << "ConfigurationManager initialized.\n";
    }
};

int main() {
    ConfigurationManager& config1 = ConfigurationManager::getInstance();
    ConfigurationManager& config2 = ConfigurationManager::getInstance();
    
    // config1 and config2 point to the exact same instance
    config1.printConfig();
    return 0;
}
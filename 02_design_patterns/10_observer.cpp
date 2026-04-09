#include <iostream>
#include <vector>
#include <algorithm>

// The Interface for any object that wants to listen
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(float temp) = 0;
};

// The Subject (the source of truth)
class WeatherStation {
private:
    std::vector<IObserver*> observers;
    float temperature;

public:
    void addObserver(IObserver* observer) {
        observers.push_back(observer);
    }

    void removeObserver(IObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setTemperature(float temp) {
        temperature = temp;
        notifyObservers();
    }

    void notifyObservers() {
        for (IObserver* observer : observers) {
            observer->update(temperature);
        }
    }
};

// Concrete Observer 1
class PhoneDisplay : public IObserver {
public:
    void update(float temp) override {
        std::cout << "Phone Display: Temperature is now " << temp << "°C\n";
    }
};

// Concrete Observer 2
class DesktopWidget : public IObserver {
public:
    void update(float temp) override {
        std::cout << "Desktop Widget: New temp received: " << temp << "°C\n";
    }
};


// Concrete Observer 2
class BeepAnnouncement : public IObserver {
public:
    void update(float temp) override {
        std::cout << "The temperature is  Beep: " << temp << "°C\n";
    }
};

int main() {
    WeatherStation station;
    
    PhoneDisplay phone;
    DesktopWidget desktop;
    BeepAnnouncement beeper;

    station.addObserver(&phone);
    station.addObserver(&desktop);
    station.addObserver(&beeper);

    // Both displays get updated automatically
    station.setTemperature(25.5f);
    
    return 0;
}
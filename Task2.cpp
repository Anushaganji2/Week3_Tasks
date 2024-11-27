#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>

class VehicleData {
public:
    VehicleData() : speed(0), fuelLevel(100), engineTemperature(70) {}
    // Update vehicle parameters with random values
    void update() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> speedDist(0, 150); // Speed: 0 to 150 km/h
        std::uniform_int_distribution<> fuelDist(0, 100); // Fuel: 0% to 100%
        std::uniform_int_distribution<> tempDist(60, 120); // Temperature: 60°C to 120°C

        speed = speedDist(gen);
        fuelLevel = fuelDist(gen);
        engineTemperature = tempDist(gen);
    }
    // Getters for the parameters
    int getSpeed() const { return speed; }
    int getFuelLevel() const { return fuelLevel; }
    int getEngineTemperature() const { return engineTemperature; }
private:
    int speed;                // Speed in km/h
    int fuelLevel;            // Fuel level in percentage
    int engineTemperature;     // Engine temperature in °C
};
class Display {
public:
    Display(const VehicleData& data) : vehicleData(data) {}
    void show() {
        while (true) {
            system("clear"); // Clear the console (use "cls" on Windows)
            std::cout << "Speed: " << vehicleData.getSpeed() << " km/h\n";
            std::cout << "Fuel Level: " << vehicleData.getFuelLevel() << "%\n";
            std::cout << "Engine Temperature: " << vehicleData.getEngineTemperature() << "°C\n";

            checkWarnings();

            std::this_thread::sleep_for(std::chrono::seconds(1)); // Update every second
        }
    }
private:
    const VehicleData& vehicleData;
    void checkWarnings() {
        if (vehicleData.getEngineTemperature() > 100) {
            std::cout << "Warning: Engine temperature is too high!\n";
        }
        if (vehicleData.getFuelLevel() < 10) {
            std::cout << "Warning: Fuel level is critically low!\n";
        }
    }
};
void updateVehicleData(VehicleData& data) {
    while (true) {
        data.update();
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Update every second
    }
}
int main() {
    VehicleData vehicleData;
    // Start a thread to update vehicle data
    std::thread updater(updateVehicleData, std::ref(vehicleData));
    // Create a display instance and show the data
    Display display(vehicleData);
    display.show();
    // Join the updater thread (not reachable in this case)
    updater.join();
    return 0;
}

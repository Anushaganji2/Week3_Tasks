#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>
using nmaespace std;
class VehicleData {
public:
    VehicleData() : speed(0), fuelLevel(100), engineTemperature(70) {}
    void update() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> speedDist(0, 150); 
        uniform_int_distribution<> fuelDist(0, 100); 
        uniform_int_distribution<> tempDist(60, 120); 

        speed = speedDist(gen);
        fuelLevel = fuelDist(gen);
        engineTemperature = tempDist(gen);
    }
    int getSpeed() const { return speed; }
    int getFuelLevel() const { return fuelLevel; }
    int getEngineTemperature() const { return engineTemperature; }
private:
    int speed;               
    int fuelLevel;            
    int engineTemperature;     
};
class Display {
public:
    Display(const VehicleData& data) : vehicleData(data) {}
    void show() {
        while (true) {
            system("clear"); // Clear the console (use "cls" on Windows)
            cout << "Speed: " << vehicleData.getSpeed() << " km/h\n";
            cout << "Fuel Level: " << vehicleData.getFuelLevel() << "%\n";
            cout << "Engine Temperature: " << vehicleData.getEngineTemperature() << "°C\n";

            checkWarnings();

            this_thread::sleep_for(chrono::seconds(1)); 
        }
    }
private:
    const VehicleData& vehicleData;
    void checkWarnings() {
        if (vehicleData.getEngineTemperature() > 100) {
            cout << "Warning: Engine temperature is too high!\n";
        }
        if (vehicleData.getFuelLevel() < 10) {
            cout << "Warning: Fuel level is critically low!\n";
        }
    }
};
void updateVehicleData(VehicleData& data) {
    while (true) {
        data.update();
        this_thread::sleep_for(chrono::seconds(1));
    }
}
int main() {
    VehicleData vehicleData;
    thread updater(updateVehicleData, ref(vehicleData));
    Display display(vehicleData);
    display.show();
    updater.join();
    return 0;
}
/*sample output
Speed: 85 km/h
Fuel Level: 45%
Engine Temperature: 90°C

Speed: 72 km/h
Fuel Level: 30%
Engine Temperature: 95°C

Speed: 120 km/h
Fuel Level: 5%
Engine Temperature: 110°C
Warning: Engine temperature is too high!
Warning: Fuel level is critically low!

...
*/

#include <iostream>

using namespace std;

class Vehicle 
{
    protected:
        int vehicleID;

    public:
        static int totalVehicles;

        Vehicle(int id) 
        {
            vehicleID = id;
            totalVehicles++;
        }

        virtual void display() 
        {
            cout << "Vehicle ID: " << vehicleID << endl;
        }

        int getID() 
        {
            return vehicleID;
        }

        virtual ~Vehicle() 
        {
            totalVehicles--;
        }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle 
{
    protected:
        int fuelType;   

    public:
        Car(int id, int fuel) : Vehicle(id) 
        {
            fuelType = fuel;
        }

        void display() 
        {
            cout << "Car ID: " << vehicleID << endl;
            cout << "Fuel Type: " << fuelType << endl;
        }
};


class ElectricCar : public Car 
{
    protected:
        int battery;

    public:
        ElectricCar(int id, int fuel, int bat)
            : Car(id, fuel) 
            {
            battery = bat;
            }

        void display() 
        {
            cout << "Electric Car ID: " << vehicleID << endl;
            cout << "Battery Capacity: " << battery << " kWh" << endl;
        }
};

class SportsCar : public ElectricCar 
{
    private:
        int topSpeed;

    public:
        SportsCar(int id, int fuel, int bat, int speed)
            : ElectricCar(id, fuel, bat) 
            {
                topSpeed = speed;
            }

        void display() 
        {
            cout << "Sports Car ID: " << vehicleID << endl;
            cout << "Top Speed: " << topSpeed << " km/h" << endl;
        }
};

class Sedan : public Car 
{
    public:
        Sedan(int id, int fuel) : Car(id, fuel) {}

        void display() 
        {
            cout << "Sedan ID: " << vehicleID << endl;
        }
};

class SUV : public Car 
{
    public:
        SUV(int id, int fuel) : Car(id, fuel) {}

        void display() 
        {
            cout << "SUV ID: " << vehicleID << endl;
        }
};

class Aircraft 
{
    protected:
        int flightRange;

    public:
        Aircraft(int range) 
        {
            flightRange = range;
        }
};

class FlyingCar : public Car, public Aircraft 
{
    public:
        FlyingCar(int id, int fuel, int range)
            : Car(id, fuel), Aircraft(range) {}

        void display() 
        {
            cout << "Flying Car ID: " << Car::vehicleID << endl;
            cout << "Flight Range: " << flightRange << " km" << endl;
        }
};


class VehicleRegistry 
{
    Vehicle* vehicles[20];
    int count;

public:
    VehicleRegistry() 
    {
        count = 0;
    }

    void addVehicle(Vehicle* v) 
    {
        vehicles[count] = v;
        count++;
    }

    void displayAll() 
    {
        if(count == 0) 
        {
            cout << "No Vehicles Available\n";
            return;
        }

        for(int i=0;i<count;i++) 
        {
            vehicles[i]->display();
            cout << "------------------\n";
        }
    }

    void searchVehicle(int id) 
    {
        for(int i=0;i<count;i++) 
        {
            if(vehicles[i]->getID() == id) 
            {
                vehicles[i]->display();
                return;
            }
        }
        cout << "Vehicle Not Found!\n";
    }
};


int main() 
{

    VehicleRegistry registry;
    int choice;

    do {
        cout << "\n===== VEHICLE REGISTRY MENU =====\n";
        cout << "1. Add Sports Car\n";
        cout << "2. Add Sedan\n";
        cout << "3. Add SUV\n";
        cout << "4. Add Flying Car\n";
        cout << "5. View All Vehicles\n";
        cout << "6. Search Vehicle by ID\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1) 
        {
            int id, fuel, battery, speed;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Fuel (1=Petrol,2=Diesel): ";
            cin >> fuel;
            cout << "Enter Battery Capacity: ";
            cin >> battery;
            cout << "Enter Top Speed: ";
            cin >> speed;

            registry.addVehicle(new SportsCar(id,fuel,battery,speed));
        }

        else if(choice == 2) 
        {
            int id, fuel;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Fuel (1=Petrol,2=Diesel): ";
            cin >> fuel;

            registry.addVehicle(new Sedan(id,fuel));
        }

        else if(choice == 3) 
        {
            int id, fuel;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Fuel (1=Petrol,2=Diesel): ";
            cin >> fuel;

            registry.addVehicle(new SUV(id,fuel));
        }

        else if(choice == 4) 
        {
            int id, fuel, range;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Fuel (1=Petrol,2=Diesel): ";
            cin >> fuel;
            cout << "Enter Flight Range: ";
            cin >> range;

            registry.addVehicle(new FlyingCar(id,fuel,range));
        }

        else if(choice == 5) 
        {
            registry.displayAll();
        }

        else if(choice == 6) 
        {
            int id;
            cout << "Enter Vehicle ID to search: ";
            cin >> id;
            registry.searchVehicle(id);
        }

    } while(choice != 7);

    cout << "\nTotal Vehicles Created: " << Vehicle::totalVehicles << endl;
    return 0;
}
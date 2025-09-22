#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Convert string to lowercase
string tolower(const string &str)
{
    string result = str;
    for (char &c : result)
    {
        c = tolower(c);
    }
    return result;
}

// Convert category to display format
string displayCategory(const string &cat)
{
    if (cat == "vip")
        return "VIP";
    else if (cat == "general")
        return "General";
    else if (cat == "handicapped")
        return "Handicapped";
    else
        return cat; // fallback
}

// Car class
class Car
{
private:
    string plate;
    string category;

public:
    Car(string p, string c) : plate(p), category(tolower(c)) {}

    string getPlate() const
    {
        return plate;
    }

    string getCategory() const
    {
        return category;
    }
};

// Parking Lot class
class ParkingLot
{
private:
    map<string, int> capacity;
    map<string, vector<Car>> parkedCars;
    map<string, float> rates;
    float revenue;

public:
    ParkingLot() : revenue(0.0)
    {
        capacity["vip"] = 10;
        capacity["general"] = 50;
        capacity["handicapped"] = 5;

        rates["vip"] = 50.0;
        rates["general"] = 20.0;
        rates["handicapped"] = 0.0;
    }

    void parkCar(Car &car)
    {
        string category = car.getCategory();
        if (capacity[category] > parkedCars[category].size())
        {
            parkedCars[category].push_back(car);
            cout << "Car with plate " << car.getPlate() << " parked in "
                 << displayCategory(category) << " section." << endl;
        }
        else
        {
            cout << "No space available in " << displayCategory(category) << " section!" << endl;
        }
    }

    bool removeCar(string plate)
    {
        for (auto &cat : parkedCars)
        {
            auto &cars = cat.second;
            for (auto it = cars.begin(); it != cars.end(); ++it)
            {
                if (it->getPlate() == plate)
                {
                    string category = it->getCategory();
                    cars.erase(it);
                    revenue += rates[category];
                    cout << "Car with plate " << plate << " removed from "
                         << displayCategory(category) << " section. Charged: $"
                         << rates[category] << endl;
                    return true;
                }
            }
        }
        return false;
    }

    void displayStatus()
    {
        cout << "=============================================" << endl;
        cout << "Parking Lot Status:" << endl;
        for (auto &cat : capacity)
        {
            string category = cat.first;
            int occupied = parkedCars[category].size();
            cout << "Category: " << displayCategory(category) << endl;
            cout << "Occupied: " << occupied << " / " << cat.second << endl;
        }
        cout << "Total Revenue: $" << revenue << endl;
        cout << "=============================================" << endl;
    }
};

int main()
{
    cout << "Welcome to the Parking Management System!" << endl;
    ParkingLot lot;

    while (true)
    {
        cout << "MENU:\nPress the preceding number to select an option:" << endl;
        cout << "1. Park Car" << endl;
        cout << "2. Remove Car" << endl;
        cout << "3. Display Parking Status" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 4)
        {
            cout << "Thank You for using the Parking Lot Management System!" << endl;
            break;
        }
        else if (choice == 1)
        {
            string plate, category;
            cout << "Enter Car Plate: ";
            getline(cin, plate);
            cout << "Enter Car Category (VIP/general/handicapped): ";
            getline(cin, category);

            category = tolower(category);

            if (category == "vip" || category == "general" || category == "handicapped")
            {
                Car car(plate, category);
                lot.parkCar(car);
            }
            else
            {
                cout << "Invalid category! Please enter VIP, general, or handicapped." << endl;
            }
        }
        else if (choice == 2)
        {
            string plate;
            cout << "Enter Car Plate to remove: ";
            getline(cin, plate);
            if (!lot.removeCar(plate))
            {
                cout << "Car with plate " << plate << " not found!" << endl;
            }
        }
        else if (choice == 3)
        {
            lot.displayStatus();
        }
        else
        {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}

#ifndef VEHICLE_H_
#define VEHICLE_H_

class Vehicle {
private:
    int vehicleId; // can be any integer
    int currentCityId; // initialised with 0 for Sydney
    int destinationId; // any city other than Sydney (1-11)
    int capacityRange; // battery life when fully charged in km
    int remainRange; // battery life remaining in km
    int recharges; // number of times a vehicle will need to recharge to get to the destination
    vector<int>chargingCities; // vector that stores which cities the vehicle has to charge at. Can only be 0, 1 or 2 cities
    
public:
    Vehicle(int=200, int=1, int=506, int=393); // some random values just in case the user doesn't input anything
    const void displayVehicleInfo(); // declared as const because its an accessor function
    
    // more accessor functions that only return the respective variables for use outside of the class
    const int getVehicleId();
    const int getCurrentCityId();
    const int getDestinationId();
    const int getCapacityRange();
    const int getRemainRange();

    void rechargeDestinations();
    int furthestCity(); // returns cityId of the city that can be reached with the current charge
    bool destinationReached(); // true or false depending on if the destinationId is reachable with the current charge

};

Vehicle::Vehicle(int vehicle, int dest, int capacity, int remain) {
    vehicleId = vehicle; //starts at 200 and increments by one each time
    currentCityId = 0; // corresponds to index 0 because thats Sydney in the nameMap array of Constant.h
    destinationId = dest;
    // arbitrary numbers chosen for the sake of testing taken from "GeneratedFileOOP.txt" from Practical6
    capacityRange = capacity;
    remainRange = remain;
    recharges = 0; // every car will start with 0 times that they recharged
}

const void Vehicle::displayVehicleInfo() {
    cout << "Vehicle ID: " << vehicleId << endl;
    cout << "Current City: " << nameMap[currentCityId] << endl;
    cout << "Destination City: " << nameMap[destinationId] << endl;
    cout << "Capacity: " << capacityRange << endl;
    cout << "Remaining: " << remainRange << endl;

}

const int Vehicle::getVehicleId() {
    return vehicleId;
}

const int Vehicle::getCurrentCityId() {
    return currentCityId;
}

const int Vehicle::getDestinationId() {
    return destinationId;
}

const int Vehicle::getCapacityRange() {
    return capacityRange;
}

const int Vehicle::getRemainRange() {
    return remainRange;
}

void Vehicle::rechargeDestinations() {

    cout << "Vehicle ID: " << vehicleId << endl;

    while (!destinationReached()) {
        int furthest = furthestCity(); // furthestCity() function only needs to be calculated once and then stored into furthest
        chargingCities.push_back(furthest); // puts the city or cities that the vehicle needs to charge at in the vector
        currentCityId = furthest;
        remainRange = capacityRange;
        
        recharges++;
    }
    
    // below print statements are just for testing purposes
    /*
    if (recharges <= 0) {
        cout << "No recharge is needed to reach " << nameMap[destinationId] << ".\n";
        cout << endl;
    }
    else {
        cout << "The car will need to recharge at cities:\n";   
        for (int v = 0; v < chargingCities.size(); v++) {
            cout << nameMap[chargingCities[v]] << endl;
        }

        cout << "Total times recharged: " << recharges << endl;
        cout << endl;
    }*/
}

int Vehicle::furthestCity() { 
    int tempRemainRange = remainRange; // temporary variable created so that remainRange isn't changed
    
    for (int i = currentCityId+1; i <= destinationId; i++) {
        if (tempRemainRange - distanceMap[i] < 0) {
            return i-1;   
        }
        else {
            tempRemainRange -= distanceMap[i];
        }    
    }
}

bool Vehicle::destinationReached() {
    return furthestCity() >= destinationId;
}


#endif /* VEHICLE_H_ */
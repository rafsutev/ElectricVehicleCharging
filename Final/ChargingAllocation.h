#ifndef CHARGINGALLOCATION_H_
#define CHARGINGALLOCATION_H_

class ChargingAllocation {
private:
    vector<Vehicle> vehicles; // used to store the vehicle objects into
    vector<ChargingStation> chargers; // used to store every charging station object into

public:
    ChargingAllocation();
    void setupChargers();
    int readDemands(); // reads demands and stores them into a vector
    void findChargingCities(); // checks where each car needs to be recharged
    void computeQueues(); // looks through the cities that each car needs to charge at and increments the queue size of that charging station
    void prepareAllocations(); // function that contains displayChargeStatus() and computeQueues() for organisation reasons 
    void outputAllocationInfo(); // function that displays all the information required from task 6
    
};

void ChargingAllocation::setupChargers(){
    for (int i = 0; i < NUM_CITIES; i++) {
        chargers.push_back(ChargingStation(i));
    }
}

ChargingAllocation::ChargingAllocation() {
    DemandGenerator generator; // the DemandGenerator constructor will automatically generate a new demands.txt file
    setupChargers(); // pushes the charging stations into the chargers vector by calling the ChargingStation constructor for each city ID
    readDemands(); // stores the demands in the demands.txt file into vehicle objects and stores those objects in the vehicles vector
    prepareAllocations(); // calculates the charging cities each vehicle stops at and computes the queue sizes for each charger
    outputAllocationInfo(); // print the above information taken

}

int ChargingAllocation::readDemands() {

    ifstream fin("demands.txt");

    // returns an error if the file didn't open
    if (!fin) {
        cout << "Could not open the file.\n";
        return 1;
    }

    string line; // where each line is stored

    while (getline(fin, line)) { // going through every line in the file
        char deliminator; // used to take the unused characters from the line (the square brackets and commas)
        stringstream ss(line); // turn each line into a string stream

        int vehicleId, destinationId, capacityRange, remainRange;

        // save each part of the line into variables to be input later into an object
        ss >> deliminator >> vehicleId >> deliminator >> destinationId >> deliminator >> capacityRange >> deliminator >> remainRange >> deliminator;

        Vehicle obj(vehicleId, destinationId, capacityRange, remainRange); // creates a temporary class object of type vehicle

        vehicles.push_back(obj); // stores the temporary class into the vector called vehicles
    }
}

void ChargingAllocation::findChargingCities() {
    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i].rechargeDestinations();
    }
}

/*
a bit more of a complex function, it does the following:
1. loops through every single vehicle in the vehicles vector, goes up to the size of the vehicles vector
2. loops through the size of the respective vehicle's chargingCities vector which stores the cities the vehicle stops at
3. call the incrementQueue function by returning the value of the city ID in the index
e.g. if the first vehicle has cities [3, 8] then j = 0 returns chargers[3] which increments the queue of Goulburn's charging stations
*/
void ChargingAllocation::computeQueues() {
    for (int i = 0; i < vehicles.size(); i++) {
        for (int j = 0; j < vehicles[i].getChargingCities().size(); j++) {
            chargers[vehicles[i].getChargingCities()[j]].incrementQueue();
        }
    }       
}

void ChargingAllocation::prepareAllocations() {
    findChargingCities();
    computeQueues();
}

void ChargingAllocation::outputAllocationInfo() {
    for (int i = 0; i < vehicles.size(); i++) {
        cout << "Vehicle ID: " << vehicles[i].getVehicleId() << endl;
        cout << "Destination City: " << nameMap[vehicles[i].getDestinationId()] << endl;
        cout << "Full capacity: " << vehicles[i].getCapacityRange() << endl;
        cout << "Remaining: " << vehicles[i].getRemainRange() << endl;
        cout << endl;

        if (vehicles[i].getChargingCities().size() <= 0) {
            cout << "No recharge required.\n";
            cout << endl;
        }
        else {
            for (int k = 0; k < vehicles[i].getChargingCities().size(); k++) {
                cout << "Recharge: " << k+1 << endl;
                cout << "City: " << nameMap[vehicles[i].getChargingCities()[k]] << endl;
                cout << "Queue: " << chargers[vehicles[i].getChargingCities()[k]].getQueue() << endl;
                cout << "Average waiting time: " << chargers[vehicles[i].getChargingCities()[k]].computeWaitTime() << " hours.\n";
                cout << endl;
            }
        }
    }
}


#endif /* CHARGINGALLOCATION_H_ */

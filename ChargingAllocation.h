#ifndef CHARGINGALLOCATION_H_
#define CHARGINGALLOCATION_H_

class ChargingAllocation {
private:
    vector<Vehicle> vehicles; // used to store the vehicle objects into

public:
    ChargingAllocation();
    int readDemands(); // reads demands and stores them into a vector
    void displayChargeStatus(); // checks where each car needs to be recharged
    
};

ChargingAllocation::ChargingAllocation() {
    DemandGenerator generator; // making an object of type ChargingAllocation will automatically make a demands generator
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

void ChargingAllocation::displayChargeStatus() {
    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i].rechargeDestinations();
    }
}





#endif /* CHARGINGALLOCATION_H_ */
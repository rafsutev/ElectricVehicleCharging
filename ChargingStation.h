#ifndef CHARINGSTATION_H_
#define CHARINGSTATION_H_

class ChargingStation {
private:
    int cityId;
    string cityName;
    int distanceToLastCity;
    int numberOfChargers;
    int queue; // tracks how many cars will need to charge at the charging station as per the demands (task 6)
    
public:
    ChargingStation();
    const void displayChargingStation();
    int distanceToSydney(int);
    const int getQueue();

};

ChargingStation::ChargingStation(){
    

    // prints the columns for each variable just like the table
    cout << "City ID" << setw(25) << "City/charging station" << setw(30) << "Distance to last city (km)" << setw(30) << "Number of chargers installed" << endl;

    for (int i = 0; i < NUM_CITIES; i++) {
        cityId = i;
        cityName = nameMap[i];
        distanceToLastCity = distanceMap[i];
        numberOfChargers = chargersMap[i];

        displayChargingStation(); 
    }
}

const void ChargingStation::displayChargingStation() {
    cout << setw(7) << cityId << setw(25) << cityName << setw(30) << distanceToLastCity << setw(30) << numberOfChargers << endl;
}

int ChargingStation::distanceToSydney(int cityNum) {
    int distance = 0; // local variable to compute the total distance to Sydney
    
    // adds each number in the distanceMap array up until the specified city ID
    for (int j = 0; j <= cityNum; j++) {
        distance += distanceMap[j]; 
    }

    return distance;
}

const int ChargingStation::getQueue() {
    return queue;
}


#endif /* CHARINGSTATION_H_ */
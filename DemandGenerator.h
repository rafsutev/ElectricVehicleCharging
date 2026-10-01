#ifndef DEMANDGENERATOR_H_
#define DEMANDGENERATOR_H_

class DemandGenerator {
private:
    int noOfDemands, destinationId, capacityRange, remainRange;
    int vehicleId = 200; // number identifying the cars starts at 200
    
public:
    DemandGenerator();
    void randomlyGenerate();
    void writeToFile();

};

DemandGenerator::DemandGenerator() {
    srand(time(nullptr));

    writeToFile();
}

void DemandGenerator::randomlyGenerate() {
    destinationId = 1 + (rand() % ((NUM_CITIES-1) - 1 + 1));
    capacityRange = MIN_CAPACITY + (rand() % (MAX_CAPACITY - MIN_CAPACITY + 1));
    remainRange = MIN_REMAIN_RANGE + (rand() % (capacityRange - MIN_REMAIN_RANGE + 1));
}

void DemandGenerator::writeToFile() {
    ofstream fout("demands.txt"); // will automatically open and close the file as needed
    noOfDemands = MIN_DEMANDS + (rand() % (MAX_DEMANDS - MIN_DEMANDS + 1));

    for (int i = 0; i < noOfDemands; i++) {
        randomlyGenerate();
        fout << "[" << vehicleId << "," << destinationId << "," << capacityRange << "," << remainRange << "]\n";
        vehicleId++;

    }
    
    
}

#endif /* DEMANDGENERATOR_H_ */
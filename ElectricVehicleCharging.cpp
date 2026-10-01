#include<iostream>
#include<ctime>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iomanip>
#include<array>

using namespace std;

#include "Constant.h"
#include "Vehicle.h"
#include "ChargingStation.h"
#include "DemandGenerator.h"
#include "ChargingAllocation.h"

int main() {
    ChargingAllocation allocator;
    allocator.readDemands();
    allocator.displayChargeStatus();

}
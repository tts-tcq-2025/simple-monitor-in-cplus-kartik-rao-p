#include <assert.h>
#include <iostream>
using namespace std;

bool checkTemperature(float temperature) {
  if(temperature < 0 || temperature > 45) {
    cout << "Temperature out of range!\n";
    return false;
  }
  return true;
}

bool checkStateOfCharge(float soc) {
  if(soc < 20 || soc > 80) {
    cout << "State of Charge out of range!\n";
    return false;
  }
  return true;
}

bool checkChargeRate(float chargeRate) {
  if (chargeRate>0.8) {
    cout << "Charge Rate out of range!\n";
    return false;
  }
  return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool resultTemperature=checkTemperature(temperature);
  bool resultSoc=checkStateOfCharge(soc);
  bool resultChargeRate=checkChargeRate(chargeRate);
  bool result;
  result = resultTemperature && resultSoc && resultChargeRate;
  return result;
  // if(temperature < 0 || temperature > 45) {
  //   cout << "Temperature out of range!\n";
  //   return false;
  // } else if(soc < 20 || soc > 80) {
  //   cout << "State of Charge out of range!\n";
  //   return false;
  // } else if(chargeRate > 0.8) {
  //   cout << "Charge Rate out of range!\n";
  //   return false;
  // }
  // return true;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}

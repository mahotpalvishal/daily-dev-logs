/**
  Design a TemperatureSensor class that records whole-number temperature readings while protecting its internal history. 
  The sensor accepts only values within its supported range and provides simple statistics over the readings it has accepted.

  Implement the TemperatureSensor class:
  
  - TemperatureSensor() creates a sensor with no readings.
  - boolean addReading(int value) records value and returns true when it is between -50 and 150, inclusive. 
  An out-of-range value is rejected: the method returns false and leaves the stored readings unchanged.
  - int getReadingCount() returns the number of accepted readings.
  - double getAverage() returns the arithmetic mean of the accepted readings. If the sensor is empty, it returns 0.
  - int[] getReadings() returns the accepted readings in insertion order. It must return a new collection or array, 
  so changing the result cannot modify the sensor's internal data.
  - Keep the readings encapsulated. Callers must be able to add values only through addReading, ensuring that the sensor 
  can never store an out-of-range temperature.
*/
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

class TemperatureSensor{
  private:
    vector<int> readings;

  public:
    TemperatureSensor(){
      this->readings = {};
    }

    bool addReading(int value){
      bool result_ = false;
      if(value>=-50 && value<=150){
        readings.push_back(value);
        result_ = true;
      }else{
        cout << "TemperatureSensor::addReading Value in Invalid range!" << value << endl;
      }
      return result_;
    }

    double getAverage(){
      if(readings.size() == 0){
        return 0;
      }
      double sum = accumulate(readings.begin(), readings.end(), 0);
      return sum/readings.size();
    }

    vector<int> getReadings(){
      return this->readings;
    }

    ~TemperatureSensor(){

    }
};

int main(){
  TemperatureSensor ts;
  bool temp = ts.addReading(-51);
  temp = ts.addReading(151);
  temp = ts.addReading(-5);
  temp = ts.addReading(1);
  temp = ts.addReading(-21);
  temp = ts.addReading(92);
  temp = ts.addReading(8);
  temp = ts.addReading(65);
  cout << "Sensor Hostory: " << endl;
  for(auto& x: ts.getReadings()){
    cout << x << " ";
  }
  cout << endl;
  cout << "Average Reading: " << ts.getAverage() << endl;
  return 0;
}
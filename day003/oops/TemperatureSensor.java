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

import java.util.ArrayList;
import java.util.stream.Collectors;

class TemperatureSensor{
    private ArrayList<Integer> readings;

    public TemperatureSensor(){
        this.readings = new ArrayList<Integer>();
    }

    boolean addReading(int value){
        boolean result_ = false;
        if(value>=-50 && value<=150){
            this.readings.add(value);
            result_ = true;
        }else{
            System.out.println("TemperatureSensor::addReading Value in Invalid range: " + value);
        }
        return result_;
    }

    double getAverage(){
        return this.readings.stream().mapToInt(Integer::intValue).average().orElse(0.0);
    }

    ArrayList<Integer> getReadings(){
        return this.readings;
    }

    public static void main(String[] args){
        TemperatureSensor ts = new TemperatureSensor();
        boolean temp = ts.addReading(-51);
        temp = ts.addReading(151);
        temp = ts.addReading(-5);
        temp = ts.addReading(1);
        temp = ts.addReading(-21);
        temp = ts.addReading(92);
        temp = ts.addReading(8);
        temp = ts.addReading(65);
        System.out.println("Sensor Hostory: ");
        for(int x: ts.getReadings()){
            System.out.print(x + " ");
        }
        System.out.println();
        System.out.println("Average Reading: " + ts.getAverage());
        return;
    }
};
class CAR{
    public static void main(String[] args){
        Car_ car = new Car_("Hondo", "Civic XT");
        int curr = car.accelerate(94);
        curr = car.brake(15);
        System.out.println("Current Speed: " + car.getSpeed());
        curr = car.accelerate(1);
        curr = car.accelerate(-12);
        System.out.println(car.describe());

        return;
    }
}

class Car_{
    private String model;
    private String brand;
    private int speed;

    public Car_(String model_, String brand_){
        this.model = model_;
        this.brand = brand_;
    }

    public int accelerate(int amount){
        if(amount > 0){
            this.speed += amount;
        }
        return this.speed;
    }

    public int brake(int amount){
        if(amount > 0){
            this.speed -= amount;
        }
        return this.speed;
    }

    public int getSpeed(){
        return this.speed;
    }

    public String describe(){
        return ("------------------\nBrand: " + this.brand + "\nModel: " + this.model + "\nSpeed: " + this.speed + "\n---------------------");
    }

}
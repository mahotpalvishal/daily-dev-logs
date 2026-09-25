/**
 * 
 *  Design the Color model used by a TrafficLight controller. The controller displays one colour at a time and moves through the same repeating cycle: red, green, yellow, then back to red.

 The TrafficLight class is provided. Complete the missing Color enum—or the closest enum-like type in your language—so the controller has everything it needs to behave as follows:
 
 TrafficLight(String startColor) starts on RED, GREEN, or YELLOW, matching the input without regard to case. An unrecognized value defaults to RED.
 String getColor() returns the current colour's name.
 int getDuration() returns the current colour's duration: RED lasts 30 seconds, GREEN lasts 25, and YELLOW lasts 5.
 String next() advances once through the cycle and returns the new colour's name.
 String describe() returns the current colour and duration in the exact format "<COLOR> (<duration>s)", such as "RED (30s)".
 Each colour should know both how long it lasts and which colour follows it:
 
 RED (30s) -> GREEN (25s) -> YELLOW (5s) -> RED (30s)
 
 Read the supplied controller carefully to see the exact fields, methods, or lookup tables expected from Color in your language. Do not duplicate the cycle rules inside the controller.


 */

class TrafficLight{
    private color currColor;

    public TrafficLight(String startColor){
        if(startColor == null){
            this.currColor = color.RED;
            return;
        }
        try{
            this.currColor = color.valueOf(startColor.toUpperCase());
        }catch(IllegalArgumentException e){
            this.currColor = color.RED;
        }
    }

    public String getColor(){
        return this.currColor.name();
    }

    public Integer getDuration(){
        return this.currColor.getDuration();
    }

    public String next() {
        this.currColor = this.currColor.next();
        return getColor();
    }

    public String describe() {
        return String.format("%s (%ds)", getColor(), getDuration());
    }

    public static void main(String[] args) {
        System.out.println("=== 1. Testing Initialization & Defaults ===");
        
        // Test normal initialization (case-insensitive)
        TrafficLight light1 = new TrafficLight("green");
        System.out.println("Initialized with 'green': " + light1.describe()); 

        // Test invalid value falling back to RED default
        TrafficLight light2 = new TrafficLight("PURPLE");
        System.out.println("Initialized with 'PURPLE' (Invalid): " + light2.describe()); 

        // Test null value falling back to RED default
        TrafficLight light3 = new TrafficLight(null);
        System.out.println("Initialized with null: " + light3.describe()); 


        System.out.println("\n=== 2. Simulating a Full Traffic Light Cycle ===");
        
        // Start a controller on RED
        TrafficLight controller = new TrafficLight("RED");
        System.out.println("Initial State: " + controller.describe());

        // Cycle through the states: RED -> GREEN -> YELLOW -> RED
        for (int i = 1; i <= 4; i++) {
            String nextColorName = controller.next();
            System.out.println("Advance " + i + " -> New color: " + nextColorName + " | Current state: " + controller.describe());
        }
    }
}

enum color{
    RED(30){
        @Override
        public color next(){
            return GREEN;
        }
    },
    GREEN(25){
        @Override
        public color next(){
            return YELLOW;
        }
    },
    YELLOW(5){
        @Override
        public color next(){
            return RED;
        }
    };

    private final int duration;

    color(int duration){
        this.duration = duration;
    }

    public int getDuration(){
        return this.duration;
    }

    public abstract color next();
}


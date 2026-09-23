
public class Shape{
    private String shape;

    protected String getShape(){
        return this.shape;
    }

    protected float getArea(){
        return 0;
    }

    protected float getPerimeter(){
        return 0;
    }

    public Shape(String shape_){
        this.shape = shape_;
    }

    public void describe(){
        System.out.println("Shape: " + this.getShape()
        + " Area: " + this.getArea()
        + " Perimeter: " + this.getPerimeter());
    }

    public static void main(String[] args){
        Shape sp = new Shape("Random Shape");
        sp.describe();
        sp = new Circle("Circle", 3);
        sp.describe();
        sp = new Rectangle("Rectangle", 2, 4);
        sp.describe();
    }
}

class Rectangle extends Shape{
    private float length;
    private float breadth;

    public Rectangle(String name, float len, float bre){
        super(name);
        this.length = len;
        this.breadth = bre;
    }

    protected float getArea(){
        return this.length*this.breadth;
    }

    protected float getPerimeter(){
        return 2*(this.length+this.breadth);
    }

    public void describe(){
        System.out.println("Shape: " + this.getShape()
        + " Area: " + this.getArea()
        + " Perimeter: " + this.getPerimeter());
    }
}

class Circle extends Shape{
    private float radius;

    public Circle(String name, float rad_){
        super(name);
        this.radius = rad_;
    }

    protected float getArea(){
        return 3.14F*this.radius*this.radius;
    }

    protected float getPerimeter(){
        return 2F*3.14F*this.radius;
    }

    public void describe(){
        System.out.println("Shape: " + this.getShape()
        + " Area: " + this.getArea()
        + " Perimeter: " + this.getPerimeter());
    }
}
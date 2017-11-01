import java.util.*;

class Shape {
  String name;
  Shape(String _name) { name=_name; }
  void draw() { System.out.println("drawing: " + name); }
}

class Circle extends Shape {
  double radius;
  Circle(String _name, int _radius) { super(_name); radius=_radius; }
  void draw() { System.out.println("drawing circle: " + name + " r=" + radius); }  
}

class Square extends Shape {
  double side;
  Square(String _name, int _side) { super(_name); side=_side; }
  void draw() { System.out.println("drawing circle: " + name + " s=" + side); }  
}

class Shapes extends Shape {
  Shapes() { super("shapes"); }
  Random random = new Random();
  int rand(int n) { return random.nextInt(n); }

  ArrayList < Shape > parts = new ArrayList<Shape>();
  void make(int n) {
    for (int i=0; i<n; ++i) {
        name = "" + rand(10000)  + "(" + i + ")";
        if ((i%10) <= 5) {
          parts.add(new Circle("circle # " + name,rand(100)));
        } else {
          parts.add(new Square("shape # " +name,rand(100)));
        }
    }
  }

  void sort() {
    parts.sort((a,b)->a.name.compareTo(b.name));
  }

  void draw() {
    for (Shape shape : parts) {
      shape.draw();
    }
  }
  
  public static void main(String[] args) {
    new Shapes().run();
  }

  void run() {
    int n = 100; // 1000000;
    Shapes shapes = new Shapes();
    long t0,t1;

    t0=System.currentTimeMillis();
    shapes.make(n);
    t1=System.currentTimeMillis();
    System.out.println("construct: " + (t1-t0)/1000.0 + "s");
    t0=System.currentTimeMillis();
    shapes.sort();
    t1=System.currentTimeMillis();
    System.out.println("sort: " + (t1-t0)/1000.0 + "s");
  }
}

import java.util.*;
import java.io.*;
import java.nio.charset.Charset;
import java.nio.file.*;
import javax.script.*;

class Config {
    public static final File thisDir;
    static {
	File _thisDir = null;
	try {
	    _thisDir = new File(Config.class.getProtectionDomain().getCodeSource().getLocation().getPath());
	} catch (Exception ex) {
	    ex.printStackTrace();
	}
	thisDir = _thisDir;
    }

    public final Map<String, Object> map;

    public Config(String filename) {
	Map<String,Object> _map = null;
	try {
	    String configFilename = thisDir + "/" + filename;
	    byte[] configBytes = Files.readAllBytes(Paths.get(configFilename));
	    String configString = new String(configBytes,
					     Charset.forName("UTF-8")).replaceAll("\\r?\\n"," ");
	    ScriptEngine engine = new ScriptEngineManager().getEngineByName("nashorn");
	    Object object = engine.eval(String.format("JSON.parse('%s')", configString));
	    _map = Collections.unmodifiableMap((Map<String, Object>) object);
	} catch (Exception ex) {
	    throw new RuntimeException(ex);
	}
	map=_map;
    }

    public static final Config CONFIG = new Config("config.json");

    public int getN() {
	return (Integer) map.get("n");
    }
}

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
        int n = Config.CONFIG.getN();
	System.out.println("n=" + n);
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

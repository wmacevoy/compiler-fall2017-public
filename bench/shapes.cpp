#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>

int rand(int n) { return rand() % n; }

class Shape {
public: std::string name;
public: Shape(const std::string &_name) : name(_name) { }
public: virtual void draw() { std::cout << "drawing: " << name << std::endl; }
};

class Circle: public Shape {
public: double radius;
public: Circle(const std::string &_name, int _radius)
  : Shape(_name), radius(_radius) {}

public: virtual void draw() {
  std::cout << "drawing circle: " << name << " r=" << radius << std::endl;
}
};

class Square: public Shape {
public: double side;
public: Square(const std::string &_name, int _side)
  : Shape(_name), side(_side) {}
public: void draw() {
  std::cout << "drawing square: " << name << " s=" << side << std::endl;  
}
};

class Shapes: public Shape {
public: Shapes() : Shape("shapes") {}
public: std::vector < std::shared_ptr < Shape > > parts;
public: void make(int n) {
  char cbuf[1024];
  parts.resize(n, std::shared_ptr < Shape > (0));
  for (int i=0; i<n; ++i) {
    if ((i%10) <= 5) {
      snprintf(cbuf,sizeof(cbuf),"circle # %d (%d)",rand(10000),i);
      parts[i]=(std::shared_ptr<Shape>(new Circle(cbuf,rand(100))));
    } else {
      snprintf(cbuf,sizeof(cbuf),"square # %d (%d)",rand(10000),i);      
      parts[i]=(std::shared_ptr<Shape>(new Square("shape # " +name,rand(100))));
    }
  }
}

public: void sort() {
  std::sort(parts.begin(), parts.end(),
            [](const std::shared_ptr <Shape> & a, const std::shared_ptr <Shape> & b)
            { return a->name > b->name; });
}

public: void draw() {
  for (auto shape : parts) {
    shape->draw();
  }
}
  
public: void run() {
  int n = 100; // 1000000;
  Shapes shapes;
  long t0,t1;

  t0=clock();
  shapes.make(n);
  t1=clock();
  std::cout << "construct: " << double(t1-t0)/CLOCKS_PER_SEC << "s" << std::endl;
  t0=clock();
  shapes.sort();
  t1=clock();
  std::cout << "sort: " << double(t1-t0)/CLOCKS_PER_SEC << "s" << std::endl;    
}


};

int main() {
  Shapes shapes;
  shapes.run();
  return 0;
}

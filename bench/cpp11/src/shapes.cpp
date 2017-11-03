#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

// https://github.com/nlohmann/json/releases
#include "json.hpp"

int rand(int n) { return rand() % n; }

class Shape {
public: typedef std::shared_ptr < Shape > Ptr;
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
public: std::vector < Ptr > parts;
public: void make(int n) {
  char cbuf[1024];
  parts.resize(n, Ptr(0));
  for (int i=0; i<n; ++i) {
    if ((i%10) <= 5) {
      snprintf(cbuf,sizeof(cbuf),"circle # %d (%d)",rand(10000),i);
      parts[i]=Ptr(new Circle(cbuf,rand(100)));
    } else {
      snprintf(cbuf,sizeof(cbuf),"square # %d (%d)",rand(10000),i);      
      parts[i]=Ptr(new Square("shape # " +name,rand(100)));
    }
  }
}

public: void sort() {
  std::sort(parts.begin(), parts.end(),
            [](const Ptr & a, const Ptr & b)
            { return a->name > b->name; });
}

public: void draw() {
  for (auto shape : parts) {
    shape->draw();
  }
}
  
public: void run(int n) {
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
  nlohmann::json config;
  std::ifstream("../config.json") >> config;
  int n = config["n"];
  Shapes shapes;
  shapes.run(n);
  return 0;
}

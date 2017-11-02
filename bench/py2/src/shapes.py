import json
import sys
import os
import random
import time

thisdir=os.path.abspath(os.path.dirname(sys.argv[0]))
cfg=json.load(open(thisdir + '/config.json', 'r'))
n=cfg["n"]

class Shape:
    def __init__(self,name):
        self.name=name
    def draw(self):
        print "drawing: " + self.name

class Circle(Shape):
    def __init__(self,name,radius):
        Shape.__init__(self,name)
        self.radius = radius
    def draw(self):
        print "drawing circle: " + self.name + " r=" + str(self.radius) 

class Square(Shape):
    def __init__(self,name,side):
        Shape.__init__(self,name)
        self.side = side
    def draw(self):
        print "drawing square: " + self.name + " s=" + str(self.side) 

def rand(n):
    return random.randint(0,n-1)

def mkShapes(n):
    shapes = list([])
    for i in xrange(n):
        name = str(rand(10000)) + "(" + str(i) + ")";
        if (i%10) <= 5:
            shapes.append(Circle("circle # " + name,rand(100)))
        else:
            shapes.append(Square("shape # " +name,rand(100)))
    return shapes

def drawShapes(shapes):
    for shape in shapes:
        shape.draw()

start = time.clock()
shapes=mkShapes(n)
end = time.clock()
print "construct: " + str(end - start) + "s"

start = time.clock()
sortedShapes = sorted(shapes,key = lambda shape: shape.name)
end = time.clock()
print "sort: " + str(end - start) + "s"

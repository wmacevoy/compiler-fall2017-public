import sys
import os
import time
import json

thisdir=os.path.abspath(os.path.dirname(sys.argv[0]))

cfg=json.load(open(thisdir + '/../../config.json', 'r'))
n=cfg["n"]

libdir=os.path.abspath(thisdir + "/../lib")
for root, dirs, files in os.walk(libdir):
    for dir in dirs:
        if dir.startswith("lib."):
            for subroot,subdirs,subfiles in os.walk(libdir + "/" + dir):
                for subfile in subfiles:
                    if (subfile.endswith(".so")):
                        libsodir=libdir + "/" + dir
                        sys.path.append(libsodir)

import rand

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

def mkShapes(n):
    shapes = list([])
    for i in xrange(n):
        name = str(rand.rand(10000))  + "(" + str(i) + ")";
        if (i%10) <= 5:
            shapes.append(Circle("circle # " + name,rand.rand(100)))
        else:
            shapes.append(Square("shape # " +name,rand.rand(100)))

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

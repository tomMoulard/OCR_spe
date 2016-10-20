import network
import numpy as np

sizes = [2, 3, 2, 3, 2]

def printArray(a):
    for x in a:
        print x, "\n"

print "sizes"
printArray(sizes)
print"biases"
b = [np.random.randn(y, 1) for y in sizes[1:]]
printArray(b)
print "weights"
a = [np.random.randn(y, x) for x, y in zip(sizes[:-1], sizes[1:])]
printArray(a)
print a
sizes.append(5) 
a = [np.random.randn(y, x) for x, y in zip(sizes[:-1], sizes[1:])]
printArray(a)
print a
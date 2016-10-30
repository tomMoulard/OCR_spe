import network
import numpy as np

sizes = [2, 3, 1]

def printArray(a):
    for x in a:
        print x, "\n"

print "sizes\n"
print sizes
print"\nbiases"
b = [np.random.randn(y, 1) for y in sizes[1:]]
printArray(b)
print "end biasesn\n"
print "weights"
a = [np.random.randn(y, x) for x, y in zip(sizes[:-1], sizes[1:])]
printArray(a)
print "end weights\n"
#print a

nabla_b = [np.zeros(bia.shape) for bia in b]
printArray(nabla_b)
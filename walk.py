import random

#x = 0 #float(input("enter x,y"))
#y = 0 #float(input("enter x,y"))
R = float(input('enter radius'))
A = []

dx = 2.0/R
#dy = 2.0/R
B = []
t = 0
import random
import os

def Fand(a, b, seed_bytes=128):
    random.seed = os.urandom(seed_bytes)
    return random.randint(a,b)
for i in range(20):
    T = Fand(1,2)
    x=0
    t=0
    while abs(x)%(3.1415) <(3.1415 - (1.0/R)): 
        if T == 1:
            x = x + dx
        elif T == 2:
            x = x - dx
        t = t + 1
        T = Fand(1,2)
        A.append(T)
    B.append(t*0.000114155*2)
print(sum(B)/20)
f = open("rand.txt", "a+")
for j in range(len(A)):
    f.write(str(A[j]))

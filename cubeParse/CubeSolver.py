#!/usr/bin/python2
#Filename:CubeSolver.py

import kociemba

def solver(s):
   print ("calculating...")
   answer = kociemba.solve(s)
   print("calculate successfully!")
   #print(answer)
   return answer

def hellos(s):
    print ("Hello World")
    print(s)

print ("work")

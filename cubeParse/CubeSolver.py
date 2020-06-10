#!/usr/bin/python2
#Filename:CubeSolver.py

import kociemba

def solver(s):
   print ("calculating...")
   try:
        answer = kociemba.solve(s)
        print("calculate successfully!")
        #print(answer)
   except:
        print('calculate fail')
        answer = 'Fail'
   return answer

def hellos(s):
    print ("Hello World")
    print(s)

print ("work")

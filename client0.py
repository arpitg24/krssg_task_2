import socket 
import pickle
import sys

s2 = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s2.connect((socket.gethostname(),1235))

m = int(input("enter no. of minions:"))  #no. of minions
n = int(input("enter no. of elements in array:")) 

lst = [] #the array
    
lst.append(m)
lst.append(n)

for i in range (0,n):
    ele = int(input())

    lst.append(ele)

while True:

    add = 0
    
    arr = pickle.dumps(lst)
    s2.send(arr)

    for j in range (0,m):
        add_recv = s2.recv(1024)
        add_j = pickle.loads(add_recv)
        add = add + add_j

    print(add)
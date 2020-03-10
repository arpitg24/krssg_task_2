import socket 
import pickle
import sys
import time

s1 = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s1.connect((socket.gethostname(),1235))

while True:

    

    sub_arr_recv = s1.recv(1024)
    sub_arr = pickle.loads(sub_arr_recv)

    size = len(sub_arr)

    print(sub_arr)

    sum = 0
    for i in range (0,size):
        sum = sum + sub_arr[i]

    sum_send = pickle.dumps(sum)
    s1.send(sum_send)
    time.sleep(10)

    
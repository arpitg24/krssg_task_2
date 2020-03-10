import socket
import pickle
import threading 

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

s.bind((socket.gethostname(),1235))
s.listen(5)

while True:

    clientsocket, address = s.accept()

    arr = clientsocket.recv(1024)
    lst = pickle.loads(arr)

    n = lst[1]
    m = lst[0]

    a = int(n/m)
    r = n%m

    def proc(i):

        minionsocket_i, address_i = s.accept()
        sub_lst_i = []
        for j in range (0,a):
            sub_lst_i.append(lst[i+j+2])
        
        minionsocket_i_send = pickle.dumps(sub_lst_i)
        minionsocket_i.send(minionsocket_i_send)

        sum_recv_i = minionsocket_i.recv(1024)
        clientsocket.send(sum_recv_i)

    def last():

        minionsocket_last , address_last = s.accept()
        sub_lst_last = []
        for i in range (m*(a-1),n):
            sub_lst_last.append(lst[i+2])
        
        minionsocket_last_send = pickle.dumps(sub_lst_last)
        minionsocket_last.send(minionsocket_last_send)

        sum_recv_last = minionsocket_last.recv(1024)
        clientsocket.send(sum_recv_last)


    for k in range (0,m-1):

        t_k = threading.Thread(target=proc, args=(k*a,))
        t_k.start()
        t_k.join()
    t = threading.Thread(target=last, args=())
    t.start()
    t.join()

            
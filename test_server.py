# recv log msg
from socket import *

addr = ("127.0.0.1", 9090)

ser = socket(AF_INET, SOCK_STREAM, 0)

ser.bind(addr)
ser.listen(5)
cnn, addr = ser.accept()

print("from addr:", addr)

while True:
    msg = cnn.recv(1024)
    if not msg:
        break
    print(msg.decode('utf-8'))

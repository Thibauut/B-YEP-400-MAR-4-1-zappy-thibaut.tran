#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-thibaut.tran
## File description:
## ai
##

import select
import socket
import sys


class MyClient():
    def __init__(self, argv):
        self.port = int(argv[2])
        self.ip = 'localhost'
        if (len(argv) == 5):
            self.ip = str(argv[4])

    def connect_to_server(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_address = (self.ip, self.port)
        self.sock.connect(server_address)

    def send_command_to_server(self):
        self.cmd = sys.stdin.readline()
        self.sock.sendall(self.cmd.encode())

    def receive_data_from_server(self):
        self.data = self.sock.recv(1024)
        print(self.data.decode(), end="")

    def handle_data(self):
        self.fdmax = self.sock.fileno()
        if sys.stdin.fileno() > self.fdmax:
            self.fdmax = sys.stdin.fileno()
        while True:
            readfds = []
            readfds.append(self.sock)
            readfds.append(sys.stdin)

            r, w, x = select.select(readfds, [], [])

            for descriptor in r:
                if descriptor == sys.stdin:
                    self.send_command_to_server()
                else:
                    self.receive_data_from_server()
            if self.data.decode() == "WELCOME\n":
               getWelcome()

def getWelcome():
    print("Is Welcomed")

def main():
    if (len(sys.argv) == 3) or (len(sys.argv) == 5):
        try:
            client = MyClient(sys.argv)
        except:
            exit(84)
        client.connect_to_server()
        client.handle_data()
        client.sock.close()
        return (0)
    else:
        exit (84)

if __name__ == "__main__":
    main()

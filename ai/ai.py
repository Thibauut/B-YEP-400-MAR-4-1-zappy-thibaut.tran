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

def connect_to_server(argv):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    if(len(argv) == 3):
        server_address = ('localhost', int(argv[2]))
    else:
        server_address = (str(argv[4]), int(argv[2]))
    sock.connect(server_address)
    return sock

def send_command_to_server(sock):
    cmd = input()
    sock.sendall(cmd.encode())

def receive_data_from_server(sock):
    data = sock.recv(1024)
    print(data.decode(), end="")
    return data.decode()

def getWelcome():
    print("Is Welcomed")

def handle_data(sock):
    fdmax = sock.fileno()
    if sys.stdin.fileno() > fdmax:
        fdmax = sys.stdin.fileno()
    while True:
        readfds = []
        readfds.append(sock)
        readfds.append(sys.stdin)

        r, w, x = select.select(readfds, [], [])

        for descriptor in r:
            if descriptor == sys.stdin:
                send_command_to_server(sock)
            else:
                data = receive_data_from_server(sock)
        if data == "WELCOME\n":
            getWelcome()

def main():
    if (len(sys.argv) == 3) or (len(sys.argv) == 5):
        try:
            sock = connect_to_server(sys.argv)
        except:
            exit(84)
        handle_data(sock)
        sock.close()
        return (0)
    else:
        exit (84)

if __name__ == "__main__":
    main()
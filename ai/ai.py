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

def connect_to_server(port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('127.0.0.1', int(port))
    sock.connect(server_address)
    return sock

def send_command_to_server(sock):
    cmd = input()
    sock.sendall(cmd.encode())

def receive_data_from_server(sock):
    data = sock.recv(1024)
    print(data.decode(), end="")

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
                receive_data_from_server(sock)

def main():
    sock = connect_to_server(sys.argv[1])
    handle_data(sock)
    sock.close()
    return (0)

if __name__ == "__main__":
    main()
#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-thibaut.tran
## File description:
## ai
##

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
    data = sock.recv(1024)
    print('Received:', data.decode())

def main():
    sock = connect_to_server(sys.argv[1])
    send_command_to_server(sock)
    sock.close()
    return (0)

if __name__ == "__main__":
    main()
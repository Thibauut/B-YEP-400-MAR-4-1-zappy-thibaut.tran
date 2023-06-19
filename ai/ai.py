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
<<<<<<< HEAD
                    self.receive_data_from_server()
            if self.data.decode() == "WELCOME\n":
               getWelcome()
=======
                    client.send_command_to_server(f"Take {item_to_take}\n")
                    client.receive_data_from_server()
            elif item_to_take == 'food':
                if item_to_take in self.look[2] or self.rotation >= 3:
                    client.send_command_to_server("Forward\n")
                    self.rotation = 0
                else:
                    client.send_command_to_server("Right\n")
                    self.rotation += 1
                client.receive_data_from_server()
        else:
            client.send_command_to_server("Forward\n")
            client.receive_data_from_server()

    def incantation(self, client):
        self.linemate = self.get_item("linemate")
        self.deraumere = self.get_item("deraumere")
        self.sibur = self.get_item("sibur")
        self.mendiane = self.get_item("mendiane")
        self.phiras = self.get_item("phiras")
        self.thystame = self.get_item("thystame")
        self.level2(client)
        self.level3(client)
        self.level4(client)
        self.level5(client)

    def level2(self, client):
        if self.level == 1 and self.linemate >= 1:
            client.send_command_to_server("Set linemate\n")
            client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                if (client.data.decode() != "ko\n"):
                    self.level += 1

    def level3(self, client):
        if (
            self.level == 2 and
            self.look[0].count('player') >= 2 and
            self.linemate >= 1 and
            self.deraumere >= 1 and
            self.sibur >= 1
        ):
            client.send_command_to_server("Set linemate\n")
            client.receive_data_from_server()
            client.send_command_to_server("Set deraumere\n")
            client.receive_data_from_server()
            client.send_command_to_server("Set sibur\n")
            client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                if (client.data.decode() != "ko\n"):
                    self.level += 1
                    client.receive_data_from_server()

    def level4(self, client):
        if (
            self.level == 3 and
            self.look[0].count('player') >= 2 and
            self.linemate >= 2 and
            self.phiras >= 2 and
            self.sibur >= 1
        ):
            client.send_command_to_server("Set linemate\n")     # PK y'a deux Set linemate ic
            client.receive_data_from_server()
            client.send_command_to_server("Set linemate\n")     # et ici
            client.receive_data_from_server()
            client.send_command_to_server("Set phiras\n")
            client.receive_data_from_server()
            client.send_command_to_server("Set phiras\n")
            client.receive_data_from_server()
            client.send_command_to_server("Set sibur\n")
            client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                if (client.data.decode() != "ko\n"):
                    self.level += 1
                    client.receive_data_from_server()

    def level5(self, client):
        if (
            self.level == 4 and
            self.look[0].count('player') >= 4 and
            self.linemate >= 1 and
            self.deraumere >= 1 and
            self.phiras >= 1 and
            self.sibur >= 2
        ):
            client.send_command_to_server("Set linemate\n")
            client.receive_data_from_server()
            client.send_command_to_server("Set linemate\n")
            client.receive_data_from_server()
            client.send_command_to_server("Set phiras\n")
            client.receive_data_from_server()
            client.send_command_to_server("Set phiras\n")
            client.receive_data_from_server()
            client.send_command_to_server("Set sibur\n")
            client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                if (client.data.decode() != "ko\n"):
                    self.level += 1
                    client.receive_data_from_server()
>>>>>>> 7f5cd87 (IA 0.7 test level 5)

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
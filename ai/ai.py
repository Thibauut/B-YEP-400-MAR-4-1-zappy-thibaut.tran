#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-thibaut.tran
## File description:
## ai
##

import socket
import sys


class MyClient():
    def __init__(self, argv):
        self.cmd = ""
        self.port = int(argv[2])
        self.ip = 'localhost'
        self.team = argv[4] + '\n'
        self.connected = False
        if len(argv) == 7:
            self.ip = str(argv[6])

    def connect_to_server(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_address = (self.ip, self.port)
        self.sock.connect(server_address)

    def send_team(self):
        self.receive_data_from_server()
        self.sock.sendall(self.team.encode())
        self.receive_data_from_server()
        self.ai = MyAI(self.data.decode())

    def send_command_to_server(self, cmd):
        self.cmd = cmd
        try:
            self.sock.sendall(cmd.encode())
        except:
            print("Died at level", self.ai.level)
            self.sock.close()
            exit(0)

    def receive_data_from_server(self):
        self.data = self.sock.recv(1024)
        print(self.data.decode(), end="")

    def handle_data(self):
        self.send_team()
        while self.data.decode() != "dead\n":
            self.ai.run(self)
        print("Died at level", self.ai.level)


class MyAI():
    def __init__(self, data):
        self.ClientNB = 0
        self.MapX = 0
        self.MapY = 0
        self.level = 1
        self.rotation = 0
        self.parser(data)

    def run(self, client):
        self.handle_inventory(client)
        self.food = self.get_item("food")
        self.recon(client)
        self.gather_items(client)
        if (self.food > 4):
            self.incantation(client)
        # if (self.level > 1):
        #     client.send_command_to_server("Fork\n")
        #     client.receive_data_from_server()

    def handle_inventory(self, client):
        client.send_command_to_server("Inventory\n")
        client.receive_data_from_server()
        if client.cmd == "Inventory\n":
            client.ai.get_inventory(client.data.decode())

    def recon(self, client):
        client.send_command_to_server("Look\n")
        client.receive_data_from_server()
        if client.cmd == "Look\n":
            client.ai.get_look(client.data.decode())

    def gather_items(self, client):
        items_to_gather = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']
        for item in items_to_gather:
            self.take_item(client, item)

    def parser(self, data):
        data_parts = data.split()
        if len(data_parts) >= 3:
            self.ClientNB = int(data_parts[0])
            self.MapX = int(data_parts[1])
            self.MapY = int(data_parts[2])

    def get_inventory(self, data):
        self.inventory = []
        data = data[1:-1]
        item_quantities = data.split(',')
        for item_quantity in item_quantities:
            item_info = item_quantity.split()
            if len(item_info) >= 2:
                item = item_info[0].strip()
                try:
                    quantity = int(item_info[1].strip())
                except ValueError:
                    quantity = 0
                item_dict = {'item': item, 'quantity': quantity}
                self.inventory.append(item_dict)

    def get_look(self, data):
        self.look = []
        data = data[1:-1]
        tiles = data.split(',')
        for tile in tiles:
            items = [item.strip() for item in tile.split()]
            self.look.append(items)

    def get_item(self, item_to_get):
        for item in self.inventory:
            if item['item'] == item_to_get:
                return item['quantity']
        return 0

    def take_item(self, client, item_to_take):
        if len(self.look) > 2:
            if item_to_take in self.look[0]:
                if self.level == 1 and item_to_take == 'linemate':
                    client.send_command_to_server("Incantation\n")
                    self.level += 1
                    client.receive_data_from_server()
                    client.receive_data_from_server()
                else:
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

    def level2(self, client):
        if self.level == 1 and self.linemate >= 1:
            client.send_command_to_server("Set linemate\n")
            client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            self.level += 1
            client.receive_data_from_server()
            client.receive_data_from_server()

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
            self.level += 1
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                client.receive_data_from_server()

    def level4(self, client):
        if (
            self.level == 3 and
            self.look[0].count('player') >= 2 and
            self.linemate >= 2 and
            self.phiras >= 2 and
            self.sibur >= 1
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
            self.level += 1
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                client.receive_data_from_server()


def main():
    if len(sys.argv) == 5 or len(sys.argv) == 7:
        try:
            client = MyClient(sys.argv)
        except Exception as e:
            print(e)
            exit(84)
        client.connect_to_server()
        client.handle_data()
        client.sock.close()
        return 0
    else:
        exit(84)


if __name__ == "__main__":
    main()

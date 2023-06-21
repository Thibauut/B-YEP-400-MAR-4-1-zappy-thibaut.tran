#!/usr/bin/env python3

##
## EPITECH PROJECT, 2023
## B-YEP-400-MAR-4-1-zappy-thibaut.tran
## File description:
## ai
##

import socket
import sys
import time
import threading
import subprocess
import random


class MyClient():
    def __init__(self, argv):
        self.cmd = ""
        self.port = int(argv[2])
        self.ip = 'localhost'
        self.team = argv[4]
        self.connected = False
        if len(argv) == 7:
            self.ip = str(argv[6])

    def connect_to_server(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_address = (self.ip, self.port)
        self.sock.connect(server_address)

    def send_team(self):
        self.receive_data_from_server()
        self.sock.sendall((self.team + '\n').encode())
        self.receive_data_from_server()
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

    def wait_for_data(self):
        my_thread = threading.Thread(target=self.receive_data_from_server)
        my_thread.start()
        my_thread.join()


    def receive_data_from_server(self):
        self.data = self.sock.recv(1024)
        print(self.data.decode(), end="")

    def handle_data(self):
        self.send_team()
        while self.data.decode() != "dead\n":
            self.ai.run(self)
        print(" Died at level", self.ai.level)


class MyAI():
    def __init__(self, data):
        self.ClientNB = 0
        self.MapX = 0
        self.MapY = 0
        self.level = 1
        self.rotation = 0
        self.nb = 0
        self.parser(data)
        self.items_to_gather = [{'item': 'food', 'quantity': 12}, {'item': 'linemate', 'quantity':1}] , [{'item': 'food', 'quantity': 12}, {'item': 'linemate', 'quantity':1}, {'item': 'deraumere', 'quantity':1}, {'item': 'sibur', 'quantity':1},] , [{'item': 'food', 'quantity': 12}, {'item': 'linemate', 'quantity':2}, {'item': 'sibur', 'quantity':1}, {'item': 'phiras', 'quantity':1}]

    def run(self, client):
        self.handle_inventory(client)
        time.sleep(0.5)
        self.food = self.get_item("food")
        time.sleep(0.5)
        self.recon(client)
        time.sleep(0.5)
        if self.food < 7:
            self.go_to_item(client, 'food')
        else:
            if self.check_item('food', 0) > 0 and self.food < 12 :
                self.take_item(client, 'food')
            time.sleep(0.5)
            self.gather_to_lvl_up(client)
            time.sleep(0.5)
            self.incantation(client)
            time.sleep(0.5)
            self.fork(client)

    def handle_inventory(self, client):
        client.send_command_to_server("Inventory\n")
        client.wait_for_data()
        if client.cmd == "Inventory\n":
            client.ai.get_inventory(client.data.decode())

    def recon(self, client):
        client.send_command_to_server("Look\n")
        client.wait_for_data()
        if client.cmd == "Look\n":
            client.ai.get_look(client.data.decode())

    def check_item(self, item, pos):
        if item in self.look[pos]:
            return self.look[pos].count(item)
        return 0


    def parser(self, data):
        data_parts = data.split()
        if len(data_parts) >= 3:
            self.ClientNB = int(data_parts[0])
            self.MapX = int(data_parts[1])
            self.MapY = int(data_parts[2])
        self.nb = (1 - self.ClientNB) * (-1)

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

    def get_level(self, client):
        level = client.data.decode().replace("Current level: ", "").replace("\n", "")
        try:
            self.level = int(level)
        except:
            self.level += 1

    def go_to_item(self, client, item):
        try:
            if self.check_item(item, 0):
                self.take_item(client, item)
            elif self.check_item(item, 2) > 0:
                self.move(client, "Forward")
                self.take_item(client, item)
            elif self.level > 1 and self.check_item(item, 6):
                self.move(client, "Forward")
                self.move(client, "Forward")
                self.take_item(client, item)
            elif self.level > 2 and self.check_item(item, 12):
                self.move(client, "Forward")
                self.move(client, "Forward")
                self.move(client, "Forward")
                self.take_item(client, item)
            elif self.check_item(item, 1):
                self.move(client, "Forward")
                self.move(client, "Left")
                self.move(client, "Forward")
                self.take_item(client, item)
            elif self.check_item(item, 3):
                self.move(client, "Forward")
                self.move(client, "Right")
                self.move(client, "Forward")
                self.take_item(client, item)
            else:
                self.move(client, "Right")
        except:
            return

    def gather_to_lvl_up(self, client):
        for n in self.items_to_gather[self.level - 1]:
            if (n["quantity"] > self.get_item(n['item'])):
                self.go_to_item(client, n['item'])

    def move(self, client, direction):
        client.send_command_to_server(direction + "\n")
        client.wait_for_data()

    def take_item(self, client, item_to_take):
        client.send_command_to_server(f"Take {item_to_take}\n")
        client.wait_for_data()

    def connect_nbr(self, client):
        client.send_command_to_server("Connect_nbr\n")
        client.wait_for_data()
        nb = client.data.decode().split("\n")[0]
        self.ClientNB = int(nb)

    def fork(self, client):
        try:
            self.connect_nbr(client)
            time.sleep(0.1)
        except:
            return
        if self.ClientNB != 0:
            # print("Fork")
            # client.send_command_to_server("Fork\n")
            # client.wait_for_data()
        # else:
            subprocess.Popen(["./zappy_ai", "-p", str(client.port), "-n", client.team, "-h", client.ip])


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
            client.wait_for_data()
            client.send_command_to_server("Incantation\n")
            client.wait_for_data()
            if (client.data.decode() != "ko\n"):
                client.wait_for_data()
                self.get_level(client)

    def level3(self, client):
        if (
            self.level == 2 and
            self.look[0].count('player') >= 2 and
            self.linemate >= 1 and
            self.deraumere >= 1 and
            self.sibur >= 1
        ):
            client.send_command_to_server("Set linemate\n")
            client.wait_for_data()
            client.send_command_to_server("Set deraumere\n")
            client.wait_for_data()
            client.send_command_to_server("Set sibur\n")
            client.wait_for_data()
            client.send_command_to_server("Incantation\n")
            client.wait_for_data()
            if (client.data.decode() != "ko\n"):
                client.wait_for_data()
                client.wait_for_data()
                self.get_level(client)
                client.wait_for_data()

    def level4(self, client):
        if (
            self.level == 3 and
            self.look[0].count('player') >= 2 and
            self.linemate >= 2 and
            self.phiras >= 2 and
            self.sibur >= 1
        ):
            client.send_command_to_server("Set linemate\n")
            client.wait_for_data()
            client.send_command_to_server("Set linemate\n")
            client.wait_for_data()
            client.send_command_to_server("Set phiras\n")
            client.wait_for_data()
            client.send_command_to_server("Set phiras\n")
            client.wait_for_data()
            client.send_command_to_server("Set sibur\n")
            client.wait_for_data()
            client.send_command_to_server("Incantation\n")
            client.wait_for_data()
            if (client.data.decode() != "ko\n"):
                client.wait_for_data()
                if (client.data.decode() != "ko\n"):
                    self.get_level(client)
                    client.wait_for_data()
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")

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
            client.wait_for_data()
            client.send_command_to_server("Set linemate\n")
            client.wait_for_data()
            client.send_command_to_server("Set phiras\n")
            client.wait_for_data()
            client.send_command_to_server("Set phiras\n")
            client.wait_for_data()
            client.send_command_to_server("Set sibur\n")
            client.wait_for_data()
            client.send_command_to_server("Incantation\n")
            client.wait_for_data()
            if (client.data.decode() != "ko\n"):
                client.wait_for_data()
                if (client.data.decode() != "ko\n"):
                    self.get_level(client)
                    client.wait_for_data()


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

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
    def __init__(self):
        self.cmd = ""
        self.port = int(sys.argv[2])
        self.ip = 'localhost'
        self.team = sys.argv[4]
        self.connected = False
        if len(sys.argv) == 7:
            self.ip = str(sys.argv[6])
        self.launch()

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

    def receive_data_from_server(self):
        try:
            self.data = self.sock.recv(1024)
        except:
                print("Died at level", self.ai.level)
                self.sock.close()
                exit(0)
        print(self.data.decode(), end="")

    def handle_data(self):
        self.send_team()
        while True:
            self.ai.run(self)

    def launch(self):
        self.connect_to_server()
        self.handle_data()


class MyAI():
    def __init__(self, data):
        self.ClientNB = 0
        self.MapX = 0
        self.MapY = 0
        self.level = 1
        self.rotation = 0
        self.nb = 0
        self.nbFork = 0
        self.parser(data)
        self.items_to_gather = [{'item': 'food', 'quantity': 12}, {'item': 'phiras', 'quantity': 3}, {'item': 'linemate', 'quantity':1}], [{'item': 'food', 'quantity': 12}, {'item': 'phiras', 'quantity': 3}, {'item': 'linemate', 'quantity':1}, {'item': 'deraumere', 'quantity':1}, {'item': 'sibur', 'quantity':1},], [{'item': 'food', 'quantity': 12}, {'item': 'phiras', 'quantity': 3}, {'item': 'linemate', 'quantity':2}, {'item': 'sibur', 'quantity':1}], [{'item': 'food', 'quantity': 12}, {'item': 'phiras', 'quantity': 3}, {'item': 'linemate', 'quantity':1}, {'item': 'deraumere', 'quantity':1},{'item': 'sibur', 'quantity':2}]
        self.items_to_lvl = [{'item': 'linemate', 'quantity':1}], [{'item': 'linemate', 'quantity':1}, {'item': 'deraumere', 'quantity':1}, {'item': 'sibur', 'quantity':1},], [{'item': 'linemate', 'quantity':2}, {'item': 'sibur', 'quantity':1}, {'item': 'phiras', 'quantity':2}], [{'item': 'linemate', 'quantity':1}, {'item': 'deraumere', 'quantity':1},{'item': 'sibur', 'quantity':2}, {'item': 'phiras', 'quantity':1}]


    def run(self, client):
        client.ai.handle_inventory(client)
        client.ai.recon(client)
        if client.ai.get_item('food') < 10:
            if self.look[0].count('player') < 2:
                for item in client.ai.items_to_gather[self.level - 1]:
                    if client.ai.check_item(item['item'], 0) > 0:
                        client.ai.take_item(client, item['item'])
            client.ai.go_to_item(client, 'food')
        else:
            for _ in range(client.ai.check_item('food', 0)):
                client.ai.take_item(client, 'food')
            client.ai.incantation(client)
            client.ai.check_item_floor(client)
            if self.look[0].count('player') < 2:
                client.ai.gather_to_lvl_up(client)
            client.ai.fork(client)
            # print('Level', ' '*self.level, client.ai.level)
            # if (self.level == 3):
            #     print("*********************************************")
            #     missing_objs = []

            #     # AFFICHAGE
            #     print("Level 3 : missing :")
                    
            #     # CE QUE J'AI
            #     print("Objects in my possession :")
            #     for obj in self.inventory:
            #         print(obj['item'])

            #     # CE QU'IL ME FAUT
            #     print("Required objects :")
            #     for obj_require in self.items_to_gather[self.level - 1]:
            #         print(obj_require['item'])
            #         missing_objs.append(obj_require['item'] + ":" + str(obj_require['quantity'] - self.get_item(obj_require['item'])))

            #     for obj in self.inventory:
            #         for obj_require in self.items_to_gather[self.level - 1]:
            #             if (obj['item'] == obj_require['item'] and obj_require['quantity'] - obj['quantity'] <= 0) or obj['item'] == 'food':
            #                 try:
            #                     missing_objs.remove(obj['item'])
            #                 except:
            #                     continue
                
            #     print("Missing objects :", missing_objs)
            #     print("*********************************************")


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

    def check_item(self, item, pos):
        if item in self.look[pos]:
            return self.look[pos].count(item)
        return 0

    def check_item_floor(self, client):
        items_needed = 0
        valid_items = 0
        for _ in self.items_to_lvl[self.level - 1]:
            items_needed += 1
        for item in self.items_to_lvl[self.level - 1]:
            quantityhave = self.check_item(item['item'], 0)
            quantityreq = item['quantity']
            if quantityhave >= quantityreq:
                valid_items += 1
        if (valid_items == items_needed):
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            client.receive_data_from_server()
            self.get_level(client)
            # if self.level > 2:
            #     client.receive_data_from_server()


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
                direction = random.randint(0, 2)
                if direction == 0:
                    self.move(client, "Left")
                elif direction == 1:
                    self.move(client, "Forward")
                else:
                    self.move(client, "Right")
        except:
            return

    def gather_to_lvl_up(self, client):
        for item in self.items_to_gather[self.level - 1]:
            if (item['quantity'] > self.get_item(item['item'])):
                self.go_to_item(client, item['item'])
                self.recon(client)

    def move(self, client, direction):
        client.send_command_to_server(direction + "\n")
        client.receive_data_from_server()

    def take_item(self, client, item_to_take):
        client.send_command_to_server(f"Take {item_to_take}\n")
        client.receive_data_from_server()

    def connect_nbr(self, client):
        client.send_command_to_server("Connect_nbr\n")
        client.receive_data_from_server()
        nb = client.data.decode().split("\n")[0]
        self.ClientNB = int(nb)

    def fork(self, client):
        try:
            self.connect_nbr(client)
        except:
            return
        if self.ClientNB != 0:
        #     client.send_command_to_server("Fork\n")
        #     client.receive_data_from_server()
        # else:
            thread = threading.Thread(target=MyClient)
            thread.start()
        # subprocess.Popen(["./zappy_ai", "-p", str(client.port), "-n", client.team, "-h", client.ip])


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
        if self.level == 1 and (self.linemate >= 1 or self.check_item('linemate', 0) >= 1):
            if self.check_item('linemate', 0) < 1:
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                self.get_level(client)

    def level3(self, client):
        if (
            self.level == 2 and
            self.look[0].count('player') >= 2 and
            (self.linemate >= 1 or self.check_item('linemate', 0) >= 1) and
            (self.deraumere >= 1 or self.check_item('deraumere', 0) >= 1) and
            (self.sibur >= 1 or self.check_item('sibur', 0) >= 1)
        ):
            if self.check_item('linemate', 0) < 1 :
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
            if self.check_item('deraumere', 0) < 1:
                client.send_command_to_server("Set deraumere\n")
                client.receive_data_from_server()
            if self.check_item('sibur', 0) < 1:
                client.send_command_to_server("Set sibur\n")
                client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                self.get_level(client)
                client.receive_data_from_server()

    def level4(self, client):
        if (
            self.level == 3 and
            self.look[0].count('player') >= 2 and
            (self.linemate >= 2 or self.check_item('linemate', 0) >= 2) and
            (self.phiras >= 2 or self.check_item('phiras', 0) >= 2) and
            (self.sibur >= 1 or self.check_item('sibur', 0) >= 1)
        ):
            print("|||||||LEVEL4 INCOMING|||||||||||")
            print("|||||||LEVEL4 INCOMING|||||||||||")
            print("|||||||LEVEL4 INCOMING|||||||||||")
            print("|||||||LEVEL4 INCOMING|||||||||||")
            print("|||||||LEVEL4 INCOMING|||||||||||")
            print("|||||||LEVEL4 INCOMING|||||||||||")
            print("|||||||LEVEL4 INCOMING|||||||||||")
            print("|||||||LEVEL4 INCOMING|||||||||||")
            if self.check_item('linemate', 0) < 2:
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
            if self.check_item('phiras', 0) < 2:
                client.send_command_to_server("Set phiras\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set phiras\n")
                client.receive_data_from_server()
            if self.check_item('sibur', 0) < 1:
                client.send_command_to_server("Set sibur\n")
                client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")
            print("||||||||||||||||||||||||||||||||||||||||LEVEL4|||||||||||||||||||||||||||||")

            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                self.get_level(client)
                print("*********************************************JE SUIS NIVEAU 4**********************************************")
                print("*********************************************JE SUIS NIVEAU 4**********************************************")
                print("*********************************************JE SUIS NIVEAU 4**********************************************")
                print("*********************************************JE SUIS NIVEAU 4**********************************************")
                print("*********************************************JE SUIS NIVEAU 4**********************************************")
                print("*********************************************JE SUIS NIVEAU 4**********************************************")
                print("*********************************************JE SUIS NIVEAU 4**********************************************")

                if (client.data.decode() != "ko\n"):
                    client.receive_data_from_server()

    def level5(self, client):
        if (
            self.level == 4 and
            self.look[0].count('player') >= 4 and
            (self.linemate >= 1 or self.check_item('linemate', 0) >= 1) and
            (self.deraumere >= 1 or self.check_item('deraumere', 0) >= 1) and
            (self.phiras >= 1 or self.check_item('phiras', 0) >= 1) and
            (self.sibur >= 2 or self.check_item('sibur', 0) >= 2)
        ):
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            if self.check_item('linemate', 0) < 2:
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
            if self.check_item('deraumere', 0) < 1:
                client.send_command_to_server("Set deraumere\n")
                client.receive_data_from_server()
            if self.check_item('phiras', 0) < 2:
                client.send_command_to_server("Set phiras\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set phiras\n")
                client.receive_data_from_server()
            if self.check_item('sibur', 0) < 1:
                client.send_command_to_server("Set sibur\n")
                client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            print("|||||||LEVEL5 INCOMING|||||||||||")
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                self.get_level(client)
                print("*********************************************JE SUIS NIVEAU 5**********************************************")
                print("*********************************************JE SUIS NIVEAU 5**********************************************")
                print("*********************************************JE SUIS NIVEAU 5**********************************************")
                print("*********************************************JE SUIS NIVEAU 5**********************************************")
                print("*********************************************JE SUIS NIVEAU 5**********************************************")
                print("*********************************************JE SUIS NIVEAU 5**********************************************")
                print("*********************************************JE SUIS NIVEAU 5**********************************************")


    def level6(self, client):
        if (
            self.level == 5 and
            self.look[0].count('player') >= 4 and
            self.linemate >= 1 and
            self.deraumere >= 2 and
            self.sibur >= 1 and
            self.mendiane >= 3
        ):
            if self.check_item('linemate', 0) < 1:
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
            if self.check_item('deraumere', 0) < 2:
                client.send_command_to_server("Set deraumere\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set deraumere\n")
                client.receive_data_from_server()
            if self.check_item('sibur', 0) < 1:
                client.send_command_to_server("Set sibur\n")
                client.receive_data_from_server()
            if self.check_item('mendiane', 0) < 3:
                client.send_command_to_server("Set mendiane\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set mendiane\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set mendiane\n")
                client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                self.get_level(client)
                if (client.data.decode() != "ko\n"):
                    client.receive_data_from_server()

    def level7(self, client):
        if (
            self.level == 6 and
            self.look[0].count('player') >= 6 and
            self.linemate >= 1 and
            self.deraumere >= 2 and
            self.sibur >= 3 and
            self.phiras >= 1
        ):
            if self.check_item('linemate', 0) < 1:
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
            if self.check_item('deraumere', 0) < 2:
                client.send_command_to_server("Set deraumere\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set deraumere\n")
                client.receive_data_from_server()
            if self.check_item('sibur', 0) < 3:
                client.send_command_to_server("Set sibur\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set sibur\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set sibur\n")
                client.receive_data_from_server()
            if self.check_item('phiras', 0) < 1:
                client.send_command_to_server("Set phiras\n")
                client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                self.get_level(client)
                if (client.data.decode() != "ko\n"):
                    client.receive_data_from_server()

    def level8(self, client):
        if (
            self.level == 7 and
            self.look[0].count('player') >= 6 and
            self.linemate >= 2 and
            self.deraumere >= 2 and
            self.sibur >= 2 and
            self.mendiane >= 2 and
            self.phiras >= 2 and
            self.thystame >= 1
        ):
            if self.check_item('linemate', 0) < 2:
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set linemate\n")
                client.receive_data_from_server()
            if self.check_item('deraumere', 0) < 2:
                client.send_command_to_server("Set deraumere\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set deraumere\n")
                client.receive_data_from_server()
            if self.check_item('sibur', 0) < 2:
                client.send_command_to_server("Set sibur\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set sibur\n")
                client.receive_data_from_server()
            if self.check_item('mendiane', 0) < 2:
                client.send_command_to_server("Set mendiane\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set mendiane\n")
                client.receive_data_from_server()
            if self.check_item('phiras', 0) < 2:
                client.send_command_to_server("Set phiras\n")
                client.receive_data_from_server()
                client.send_command_to_server("Set phiras\n")
                client.receive_data_from_server()
            if self.check_item('thystame', 0 < 1):
                client.send_command_to_server("Set thystame\n")
                client.receive_data_from_server()
            client.send_command_to_server("Incantation\n")
            client.receive_data_from_server()
            if (client.data.decode() != "ko\n"):
                client.receive_data_from_server()
                self.get_level(client)
                if (client.data.decode() != "ko\n"):
                    client.receive_data_from_server()



def main():
    if len(sys.argv) == 5 or len(sys.argv) == 7:
        # try:
        thread = threading.Thread(target=MyClient)
        # except Exception as e:
        #     print(e)
        #     exit(84)
        thread.start()
        thread.join()
        return 0
    else:
        exit(84)


if __name__ == "__main__":
    main()

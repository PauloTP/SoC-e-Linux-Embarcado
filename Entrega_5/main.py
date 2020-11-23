#!/usr/bin/python

import socket
from flask import Flask,render_template,request
import threading
import struct

app = Flask(__name__)

host = "/tmp/9Lq7BNBnBycd6nxy.socket"

sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
sock.connect((host))
n = "0"

def thread_get():
        global n
        while True:
                n = str(sock.recv(1024))
                print(n)

@app.route('/', methods=['GET','POST'])
def hello():

        if request.method == "POST":
                global n
                print("sending: ",n)
                sock.sendall(bytes(str(n), "utf-8"))

        if request.method == "GET":
                get = threading.Thread(target=thread_get)
                get.start()

        return render_template('main.html')
        
        """
        while True:

                if not get.is_alive():
                        get = threading.Thread(target=thread_get)
                        get.start()

                if not post.is_alive():
                        post = threading.Thread(target=thread_get)
                        post.start()
        """
                


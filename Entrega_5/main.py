#!/usr/bin/python

import socket
from flask import Flask,render_template,request
import threading

app = Flask(__name__)

host = "/tmp/9Lq7BNBnBycd6nxy.socket"

sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
sock.connect((host))

def thread_get():
        while True:
                received = str(sock.recv(1024), "utf-8")
                print(received)

def thread_post():
        sock.sendall(bytes('ola!' + "\n", "utf-8"))

@app.route('/', methods=['POST'])
def hello():

        if request.method == "POST":
                post = threading.Thread(target=thread_post)
                post.start()

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
                


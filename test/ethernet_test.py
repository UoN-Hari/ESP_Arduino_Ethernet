import socket
from time import sleep

if __name__ == '__main__':
    # 创建udpsocket
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # 设置socket的选项，允许发送广播消息
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, True)
    # 发送广播消息
    while(True):
        udp_socket.sendto("PC is sending UDP message".encode("utf-8"), ("1.145.14.19", 8888))
        sleep(1)
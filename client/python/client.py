import socket
import struct


def send_data(client, data):
    #cmd对应配置文件workflow.xml里面的 <work name="2" switch="on"> 的name值
    cmd = 2
    data_len = len(data)
    data = struct.pack(f'8sII{data_len}s', b'work', cmd, data_len, data.encode('utf-8'))
    client.send(data)  # 发送TCP数据
    info = client.recv(1024).decode()
    print(info)


if __name__ == '__main__':

    host = '127.0.0.1'
    port = 8080

    client = socket.socket()  # 创建TCP/IP套接字
    client.connect((host, port))  # 主动初始化TCP服务器连接
    send_data(client, 'hello')
    client.close()

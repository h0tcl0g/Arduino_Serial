from socket import *
import serial
import time

### Swift->Python シリアル通信 設定 ###
# 受信側アドレス設定
# 受信側IP
SrcIP = "192.168.36.31"
# 受信側ポート番号
SrcPort = 12345
# 受信側アドレスをtuppleに格納
SrcAddr = (SrcIP, SrcPort)
# バッファサイズ指定
BUFSIZE = 1024

# ソケット作成
udpServSock = socket(AF_INET, SOCK_DGRAM)
# 受信側アドレスでソケットを設定
udpServSock.bind(SrcAddr)

########################

### Python->Arduino シリアル通信　設定 ###

# シリアルポートの設定
ser = serial.Serial('/dev/cu.usbmodem11401', 9600)

time.sleep(2)   # 接続待機

#######################

# Swift->Python 受信待ち
while True:
    # データ受信時の処理
    # 受信データを変数に設定
    data, addr = udpServSock.recvfrom(BUFSIZE)
    # 受信データと送信アドレスを出力
    print(data.decode(), addr)
    if data.decode() == "reset":
        ser.write(b'reset')

    if data.decode() == "quit":
        break

    if data.decode() == "1":
        ser.write(b'1')
    elif data.decode() == "2":
        ser.write(b'2')
    elif data.decode() == "3":
        ser.write(b'3')
    elif data.decode() == "4":
        ser.write(b'4')
    elif data.decode() == "5":
        ser.write(b'5')
    elif data.decode() == "6":
        ser.write(b'6')
    elif data.decode() == "7":
        ser.write(b'7')
    elif data.decode() == "8":
        ser.write(b'8')
    elif data.decode() == "9":
        ser.write(b'9')
    elif data.decode() == "10":
        ser.write(b'10')

# シリアルポートを閉じる
ser.close()
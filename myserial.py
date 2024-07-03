from socket import *
import serial
import time

### Swift->Python シリアル通信 設定 ###
# 受信側アドレス設定
# 受信側IP
SrcIP = "192.168.121.3"
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
def toggle_led():
    ser.write(b'1') # LEDを点灯
    time.sleep(5) # 5秒点灯状態で待機
    ser.write(b'0')    # LEDを消灯

# シリアルポートの設定
ser = serial.Serial('/dev/cu.usbmodem111401', 9600)

time.sleep(2)   # 接続待機

#######################

# Swift->Python 受信待ち
while True:
    # データ受信時の処理
    # 受信データを変数に設定
    data, addr = udpServSock.recvfrom(BUFSIZE)
    # 受信データと送信アドレスを出力
    print(data.decode(), addr)
    if data.decode() == "exe":
        toggle_led()

    if data.decode() == "quit":
        break


# シリアルポートを閉じる
ser.close()
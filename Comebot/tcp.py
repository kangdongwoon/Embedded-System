import socket
from threading import Thread
import threading
import time

# 서버의 주소입니다. hostname 또는 ip address를 사용할 수 있습니다.
HOST = '192.168.0.33'  
# 서버에서 지정해 놓은 포트 번호입니다. 
PORT = 8585       

condition_recv = threading.Condition()
condition_send = threading.Condition()

stt_list = {"코미봇" : 1, "고마워" : 2, "안녕" : 3}
stt_data = ""
stt_mode = 0
def STT_Google(cv_recv):
	global stt_data
	while True:
		#음성인식시도후 String 반환
		stt_data=input()
		cv_recv.acquire()
		cv_recv.notifyAll()
		cv_recv.release()

def sendMsg(sock,cv_send):
    global stt_mode
    sock.send("stt".encode())
    while True:
        with cv_send:
            cv_send.acquire()
            cv_send.wait()
            cv_send.release()
            sock.send(str(stt_mode).encode())
            
def STTThread(cv_send,cv_recv):
	global stt_data
	global stt_mode
	while True:
		cv_recv.acquire()
		cv_recv.wait()
		cv_recv.release()
        # String Dict안에서 비교 후 번호반환
		for stt,stt_num in stt_list.items():
			if stt == stt_data:
				print(stt,":",stt_num)
				stt_mode = stt_num
				cv_send.acquire()
				cv_send.notifyAll()
				cv_send.release()

def TcpThread():
	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
		sock.connect((HOST, PORT))
        
		thread_STT_Google = Thread(target=STT_Google, args=(condition_recv,))
		thread_send = Thread(target=sendMsg, args=(sock,condition_send,))
		thread_stt = Thread(target=STTThread, args=(condition_send, condition_recv))
        
		thread_STT_Google.daemon = True
		thread_send.daemon = True
		thread_stt.daemon = True
        
		thread_STT_Google.start()
		thread_send.start()
		thread_stt.start()
        
		while(1):
			pass
            
TcpThread()

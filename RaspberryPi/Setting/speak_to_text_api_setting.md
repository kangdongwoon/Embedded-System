** Cloud SDK 설치**
-
> sudo apt-get install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev  
> sudo apt-get install python-dev  
> sudo pip install pyaudio  
> https://cloud.google.com/sdk/docs/downloads-versioned-archives?hl=ko  
> SDK 패키지 다운로드(Linux 32bit) 후 압축해제  
> ./google-cloud-sdk/install.sh  
> ./google-cloud-sdk/bin/gcloud init  
> pip install -r requirements.txt
> reboot  
> pip install --upgrade google-cloud-speech  
> pip install google-cloud-storage  
> export GOOGLE_APPLICATION_CREDENTIALS=/home/pi/[FILE_NAME].json  
> **진심진심 경로에 "" 이나 '' 따위 붙이지 말 것(20.03.17 오류 해결)**  
> 혹은 vim /etc/bash.bashrc에서 맨 밑에 추가해준다.(영구적)  
> Python 클라이언트 라이브러리 버전을 바꿔줘야한다!  
> requirements.txt 파일 변경  
> google-cloud-speech==~1.3.1~  
> google-cloud-speech==0.26  
>
>-
>**단축키설정**  
> vim ~/.bashrc  
> alias 변수=''
> source ~/.bashrc  

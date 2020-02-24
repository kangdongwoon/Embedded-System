**라즈베리 환경설정 내용**
-
1. vim editor 설치  
2. fcitx 한글 설치  
3. python3 설치



>sudo apt-get install -y vim  
>sudo apt install -y fcitx fcitx-hangul  
>sudo apt install -y libffi-dev libbz2-dev liblzma-dev \
>libsqlite3-dev libncurses5-dev libgdbm-dev zlib1g-dev \
>libreadline-dev libssl-dev tk-dev build-essential \
>libncursesw5-dev libc6-dev openssl git
>cd /home/pi
>mkdir python_src
>cd python_src
>wget https://www.python.org/ftp/python/3.7.0/Python-3.7.0.tgz
>tar xvf Python-3.7.0.tgz
>cd Python-3.7.0
>./configure
>make -j 4
>sudo make install
>cd /home/pi/python_src
>wget https://bootstrap.pypa.io/get-pip.py
>sudo python3.7 ./get-pip.py 


**환경설정 파일수정**
-
sudo vim /etc/vim/vimrc  

>set number  
>set ai  
>set si  
>set cindent  
>set shiftwidth=4  
>set tabstop=4  
>set ignorecase  
>set hlsearch  
>set expandtab  
>set background=dark  
>set nocompatible  
>set fileencodings=utf-8,euc-kr  
>set bs=indent,eol,start  
>set history=1000  
>set ruler  
>set nobackup  
>set title  
>set showmatch  
>set nowrap  
>set wmnu  
>syntax on  

/etc/default/im-config

>~IM_CONFIG_DEFAULT_MODE=auto~  
>IM_CONFIG_DEFAULT_MODE=fcitx  
>
>기본설정 - 입력기 - default로 설정 후 저장하고 Reboot  




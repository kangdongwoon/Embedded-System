sudo apt-get install -y vim




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




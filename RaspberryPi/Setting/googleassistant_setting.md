**마이크/스피커 설정**
> arecord -l  
> aplay -l  
> 마이크와 스피커 card/device 번호를 기억한다.
>
> vim .asoundrc
> 
>pcm.!default {  
>  	type asym  
>  	capture.pcm "mic"  
>  	playback.pcm "speaker"  
>}  
>pcm.mic {  
>	type plug  
>	slave {  
>   	pcm "hw:~card number~,~device number~"  
>	}  
>}  
>pcm.speaker {  
>	type plug  
>	slave {  
>		pcm "hw:~card number~,~device number~"  
>  	}  
>}  
>**테스트 환경**  
> speaker-test -t wav  
> arecord --format=S16_LE --duration=5 --rate=16000 --file-type=raw out.raw  
> aplay --format=S16_LE --rate=16000 out.raw  
> alsamixer  

**Project 생성**
> sudo apt-get update  
> sudo apt-get install python3-dev python3-venv  
> python3 -m venv env  
> env/bin/python -m pip install --upgrade pip setuptools wheel  
> 
> 
> 
> 
> **Python 가상환경 접속**  
> source env/bin/activate  
> sudo apt-get install -y portaudio19-dev libffi-dev libssl-dev libmpg123-dev  
> python -m pip install --upgrade google-assistant-library==1.0.1  
> python -m pip install --upgrade google-assistant-sdk[samples]==0.5.1  
> python -m pip install --upgrade google-auth-oauthlib[tool]  
> google-oauthlib-tool --scope https://www.googleapis.com/auth/assistant-sdk-prototype \  
> --scope https://www.googleapis.com/auth/gcm \  
> --save --headless --client-secrets /home/pi/client_secret_~client-id~.json  
> 
> url 접속 후 비밀번호 입력/접속  
>
>
> **테스트 환경**  
> hotword : Ok google로 호출
> googlesamples-assistant-hotword --device_model_id ~my-model~  
> 엔터를 입력할 때마다 반응
> googlesamples-assistant-pushtotalk --project_id ~my-dev-project~ --device_model_id ~my-model~  

**음성인식 Source**
-
> sudo apt-get update  
> sudo apt-get install -y libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev  
> sudo apt-get install python-dev  
> sudo pip install pyaudio  
> 서비스 계정 키 생성하기  
> export GOOGLE_APPLICATION_CREDENTIALS="/home/pi/~testspeech-e88f1e852859.json~"  
> git clone https://github.com/GoogleCloudPlatform/python-docs-samples.git  
> source env/bin/activate  
> cd python-docs-samples/speech/cloud-client/  
> pip install -r requirements.txt  
>  
> **예제코드**  
> cd python-docs-samples/speech/cloud-client/  
> python transcribe_streaming_mic.py  
> - 영어문장을 인식하는 예제코드  
> - 한글문장을 인식하려면 코드수정하기  
> ~language_code = 'en-US'~  
> language_code = 'ko-KR'  





**참고자료**
-
> https://developers.google.com/assistant/sdk/guides/library/python/embed/config-dev-project-and-account  
> https://diy-project.tistory.com/89  
> https://console.actions.google.com/
>
> https://myaccount.google.com/activitycontrols  
> - Web & App Activity, Device Information, Voice & Audio Activity 활성화  
>
> https://diy-project.tistory.com/91?category=742713

**주의사항**
-
> Google API Console에서 신용카드 등록이 필요하다. 1년 무료  
> 음성인식 프로그램 작동되는 시간 대략 65초정도이며 자동으로 정지된다.

**오류해결**
-
>Expression 'alsa_snd_pcm_hw_params_set_period_size_near( pcm, hwParams, &alsaPeriodFrames, &dir )' failed in   >'src/hostapi/alsa/pa_linux_alsa.c', line: 924  
>  
>.asoundrc를 사용하여 alsa 샘플속도 변환
``` 
pcm.convert{  
    type plug;
    slave{
        pcm default;
        rate 16000;
    }
}
```

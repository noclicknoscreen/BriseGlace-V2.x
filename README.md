# BriseGlace-V2.x

## Server
- SSH commands to start and stop (basically reboot raspberrries)
https://askubuntu.com/questions/762541/ubuntu-16-04-ssh-sign-and-send-pubkey-signing-failed-agent-refused-operation

- How to auto-sign and having ssh server
http://www.linuxproblem.org/art_9.html

## Raspberry Client
- the raspberry automatically starts, and opens a chromium page and connect to https://192.168.1.104:8443/recognition
- the automatic opening is set with set this session file

sudo nano /home/pi/.config/lxsession/LXDE-pi/autostart 

and adding this line

@chromium-browser  https://192.168.1.104:8443/recognition


# BriseGlace-V2.x
## Typology
- STT Server : node.js server for webPages and informations supply
- Scripts : startUp scripts
- Unity : folder containing Unity3D projects

#### OpenFramework Projects
- Formulaire : OF project to input enigmas
- motus : OF First

## How to Setup
### Raspberry Client
- Basic setup local settings to FR (Localization, TimeZone, Keyboard, WiFi) in the raspberry settings / Localisation tab
- Active SSH / VNC in settings/Interface
- Install realVnc server and setup 
https://www.realvnc.com/fr/connect/docs/raspberry-pi.html#vnc-connect-and-raspberry-pi
- the automatic opening is set with set this session file :

'sudo nano /home/pi/.config/lxsession/LXDE-pi/autostart'
and adding this line

'@chromium-browser  https://192.168.1.104:8443/recognition'

### Server
- SSH commands to start and stop (basically reboot raspberrries)
https://askubuntu.com/questions/762541/ubuntu-16-04-ssh-sign-and-send-pubkey-signing-failed-agent-refused-operation

- How to auto-sign and having ssh server
http://www.linuxproblem.org/art_9.html

- Good article in case of not connecting on rasp pi (For example : this message can happen **WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!**)
http://www.tux-planet.fr/warning-remote-host-identification-has-changed/

## Expected behavior
### Raspberry Client
- the raspberry automatically starts, and opens a chromium page and connect to https://192.168.1.104:8443/recognition



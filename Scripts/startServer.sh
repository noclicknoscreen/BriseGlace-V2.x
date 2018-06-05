# Run chromium start
#cd "../STTServer"

# nohup node GoogleSpeech_FileServer.js &
sleep 1
node /Users/medenagan-id-001/BriseGlace/OF_0.9.8/apps/BriseGlace-V2.x/STTServer/SttServer.js

# Restart raspberries
#sleep 1
#ssh pi@192.168.1.103 'echo | sudo shutdown -r now'

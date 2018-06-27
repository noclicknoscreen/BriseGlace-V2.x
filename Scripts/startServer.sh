# Run chromium start
#cd "../STTServer"

# nohup node GoogleSpeech_FileServer.js &
sleep 1
/usr/local/bin/node /Users/medenagan-id-001/BriseGlace/OF_0.9.8/apps/BriseGlace-V2.x/STTServer/SttServer.js >>/Users/medenagan-id-001/BriseGlace/OF_0.9.8/apps/BriseGlace-V2.x/Scripts/logsServerNode.txt 2>&1  &

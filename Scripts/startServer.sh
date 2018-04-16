# Run chromium start
cd "../STTServer"

# nohup node GoogleSpeech_FileServer.js &
sleep 1
gnome-terminal --window-with-profile="Term" -e "node SttServer.js"

# Restart raspberries
sleep 1
ssh pi@192.168.1.103 'echo | sudo shutdown -r now'

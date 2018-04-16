# Run chromium start
cd "../STTServer"
# nohup node GoogleSpeech_FileServer.js &
sleep 1
gnome-terminal -e "node STTServer.js"

# Restart raspberries
ssh pi@192.168.1.103 'echo | sudo shutdown -r now'

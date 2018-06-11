# Wait for it
sleep 10

# Restart raspberries
echo 'Restart rasp1'
ssh pi@192.168.2.21 'echo | sudo shutdown -r now'

echo 'Restart rasp2'
ssh pi@192.168.2.22 'echo | sudo shutdown -r now'

echo 'Restart rasp3'
ssh pi@192.168.2.23 'echo | sudo shutdown -r now'

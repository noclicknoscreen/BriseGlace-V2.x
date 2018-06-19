# Wait for it
sleep 1

# Restart raspberries
echo 'Restart ' $1
ssh pi@$1 'echo | sudo shutdown -r now'

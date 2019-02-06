# Wait for it
sleep 1

# Restart raspberries
echo 'Restart ' $1
ssh -o ConnectTimeout=5 pi@$1 'sudo shutdown -r now &'

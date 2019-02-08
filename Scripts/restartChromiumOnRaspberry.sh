# Wait for it
sleep 1

# Restart the page on Raspberry
echo 'Restart chromium page' $1

# Kill the page
echo 'kill chromium'
ssh -o ConnectTimeout=1 pi@$1 'pkill chromium'

# Restart chromium page
echo 'start page'
ssh -o ConnectTimeout=1 pi@$1 'DISPLAY=:0 chromium-browser https://brise.glace:8443/recognition --ignore-certificate-errors >/dev/null &'

# Restart chromium page
echo 'exit from ssh'
ssh -o ConnectTimeout=1 pi@$1 'exit'

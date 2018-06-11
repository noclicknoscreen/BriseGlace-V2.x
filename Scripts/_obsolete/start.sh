#!/bin/bash

cd "$(echo $0 | rev | cut -d "/" -f 2- | rev)"

#!/bin/sh
# Run chromium start
cd "../Scripts"
sleep 1
./startChromium.sh &

# Run window manager
#exec openbox

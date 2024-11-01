#! /bin/bash
touch semseter
echo '#!/bin/bash' > semester
echo 'curl --head --silent https://missing.csail.mit.edu' >> semester
chmod 777 semester
./semester
stat -c %y semester > ./last-modified.txt
cat /sys/class/thermal/thermal_zone0/temp

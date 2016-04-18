#!/bin/sh

sudo iptables -I INPUT 1 -m conntrack --ctstate NEW -j NFQUEUE --queue-num 0
#or
sudo iptables -I INPUT -i eth0 -m conntrack --ctstate NEW -j NFQUEUE --queue-num 0
curl --head localhost
ping localhost
sudo iptables -D INPUT -m conntrack --ctstate NEW -j NFQUEUE --queue-num 0

sudo iptables -I INPUT 1 -p icmp -j NFQUEUE --queue-num 0

CC=arm-fw867-linux-uclibcgnueabi-gcc GOOS=linux GOARCH=arm GOARM=5 CGO_ENABLED=1 CGO_CFLAGS="-march=armv5" go build --ldflags '-s  -extldflags "-static"'

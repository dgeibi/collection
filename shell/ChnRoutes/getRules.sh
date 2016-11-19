#!/bin/bash

ROUTINGTEMP="$(mktemp)"
RULESOUT="chnroutes.rules"
PORT=1080
BYPASSPORTS=()
BYPASSIPS=()
FORCE_GET=false
IPV6=false
CHNROUTES="CHNROUTES.txt"
CHAIN="SHADOWSOCKS"

if [ "$FORCE_GET" = true ] || [ ! -f ${CHNROUTES} ]; then
    echo "Get CHNROUTES.txt"
    curl http://ftp.apnic.net/apnic/stats/apnic/delegated-apnic-latest > $ROUTINGTEMP
    cat $ROUTINGTEMP | awk -F\| '/CN\|ipv4/ { printf("%s/%d\n", $4, 32-log($5)/log(2)) }' > "${CHNROUTES}"
    if [ "$IPV6" = true ]; then
        cat $ROUTINGTEMP | awk -F\| '/CN\|ipv6/ { printf("%s/%d\n", $4, $5) }' >> "${CHNROUTES}"
    fi
fi

echo "Generating iptables rules..."
{
    echo "# Generated on $(date)"
    cat <<EOF
*nat
:$CHAIN - [0:0]
-A PREROUTING -p tcp -j $CHAIN
-A OUTPUT -p tcp -j $CHAIN
-A $CHAIN -d 0.0.0.0/8 -j RETURN
-A $CHAIN -d 10.0.0.0/8 -j RETURN
-A $CHAIN -d 127.0.0.0/8 -j RETURN
-A $CHAIN -d 169.254.0.0/16 -j RETURN
-A $CHAIN -d 172.16.0.0/12 -j RETURN
-A $CHAIN -d 192.168.0.0/16 -j RETURN
-A $CHAIN -d 224.0.0.0/4 -j RETURN
-A $CHAIN -d 240.0.0.0/4 -j RETURN
EOF

    echo "# Customized rules"
    for _port in "${BYPASSPORTS[@]}"; do
        echo "-A $CHAIN -p tcp -m tcp --dport $_port -j RETURN"
    done

    for _ip in "${BYPASSIPS[@]}"; do
        echo "-A $CHAIN -d $_ip -j RETURN"
    done

    echo "# CHNROUTES"
    sed "s/.*/-A $CHAIN -d & -j RETURN/" $CHNROUTES

    echo "# REDIRECT to Shadowsocks"
    echo "-A $CHAIN -p tcp -j REDIRECT --to-ports $PORT"
    echo "COMMIT"
} > $RULESOUT

rm -rf $ROUTINGTEMP

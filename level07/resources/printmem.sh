#!/bin/bash

elf="/home/users/level07/level07"

for i in {0..200}; do
    payload=$(echo -e "read\n$i\nquit")
    content=$("$elf" <<< "${payload}")
    printf "%3d: %x\n" "${i}" $(echo -n "${content}" | grep -oP '(?<=] is ).*')
done

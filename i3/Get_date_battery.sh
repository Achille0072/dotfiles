#! /bin/sh

BAT_charge=`cat /sys/class/power_supply/BAT1/capacity`
BAT_status=`cat /sys/class/power_supply/BAT1/status`

notify-send "$(date +"%d %b, %T")" "$BAT_charge% [$BAT_status]"

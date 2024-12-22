#!/bin/bash
set -ex
xinput set-prop "$(xinput | grep -i touchpad | awk '{ print $3, $4, $5 }')" "libinput Tapping Enabled" 1
xinput set-prop "$(xinput | grep -i touchpad | awk '{ print $3, $4, $5 }')" "libinput Disable While Typing Enabled" 0


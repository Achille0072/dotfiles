#! /bin/sh

Title=`playerctl metadata | grep -oP '(?<=title).*' | sed 's/  //g'`
Artist=`playerctl metadata | grep -oP '(?<=artist).*' | sed 's/  //g'`
Album=`playerctl metadata | grep -oP '(?<=album).*' | sed 's/  //g'`

notify-send "$Title" "$Artist \nAlbum: $Album"

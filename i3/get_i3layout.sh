#!/bin/bash

i3-msg -t get_tree | jq -r 'recurse(.nodes[];.nodes!=null)|select(.nodes[].focused).layout' > ~/.config/i3/current_layout

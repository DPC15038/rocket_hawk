#!/bin/bash

DATE=$(date +"%Y-%m-%d_%H%M")

raspivid -t 10000 -w 1920 -h 1080 -fps 30 -b 1200000 -p 0,0,1920,1080 -o pivideo.h264 

MP4Box -add pivideo.h264 pivideo.mp4

rm pivideo.h264

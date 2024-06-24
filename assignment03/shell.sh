#!/bin/sh


sudo umount vtbd2

dd if=/dev/vtbd2 of=partition2.img bs=1M

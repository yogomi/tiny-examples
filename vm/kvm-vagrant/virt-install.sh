#!/bin/bash

PWD=`pwd`

sudo apt-get -y install virt-manager

wget http://cdimage.debian.or.jp/8.4.0/amd64/iso-cd/debian-8.4.0-amd64-netinst.iso

qemu-img create -f qcow2 ${PWD}/meteo.img 10G

sudo brctl addbr virbr0
sudo brctl addif virbr0 eth0

sudo virt-install \
  --name=meteo \
  --connect=qemu:///system \
  --ram 1024 \
  --vcpus=2 \
  --os-type=linux \
  --hvm \
  --virt-type=kvm \
  --disk path=${PWD}/meteo.img \
  --cdrom=${PWD}/debian-8.4.0-amd64-netinst.iso \
  --vnc --vncport=5900 --vnclisten=0.0.0.0 \
  --network=bridge:virbr0 \
  --keymap=us

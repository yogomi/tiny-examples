#!/bin/bash

PWD=`pwd`

wget https://packages.chef.io/stable/debian/8/chefdk_0.13.21-1_amd64.deb
sudo dpkg -i chefdk_0.13.21-1_amd64.deb

wget https://releases.hashicorp.com/vagrant/1.8.1/vagrant_1.8.1_x86_64.deb
sudo dpkg -i vagrant_1.8.1_x86_64.deb

sudo apt-get -y install build-essential libvirt-dev

vagrant plugin install vagrant-berkshelf vagrant-libvirt vagrant-mutate vagrant-omnibus vagrant-share

vagrant box add debian-8.4.0-amd64 https://s3.eu-central-1.amazonaws.com/ffuenf-vagrantboxes/debian/debian-8.4.0-amd64_virtualbox.box
vagrant mutate debian-8.4.0-amd64 --input-provider virtualbox libvirt

sudo usermod --group libvirt vagrant

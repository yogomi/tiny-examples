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

vagrant box add debian-7.3.0-amd64 https://dl.dropboxusercontent.com/u/29173892/vagrant-boxes/debian7.3.0-vbox4.3.6-puppet3.4.1.box
vagrant mutate debian-7.3.0-amd64 --input-provider virtualbox libvirt

vagrant box add centos-7.1-amd64 https://github.com/CommanderK5/packer-centos-template/releases/download/0.7.1/vagrant-centos-7.1.box
vagrant mutate centos-7.1-amd64 --input-provider virtualbox libvirt

sudo usermod --group libvirt vagrant

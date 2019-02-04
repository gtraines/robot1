#! /usr/bin/env bash
sudo allow ufw allow proto tcp from 192.168.1.0/24 to any port 22
sudo ufw enable
sudo systemctl enable ssh && sudo systemctl start ssh

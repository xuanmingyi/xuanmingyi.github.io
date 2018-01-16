---
layout:     post
title:      "Zabbix Server 安装"
subtitle:   ""
date:       2018-01-13 07:56:00
author:     sin
catalog:    true
header-img: img/bg.jpg
permalink:  /zabbix-server-install/
tags:
    - zabbix
    - 运维
---

准备
========

首先确认使用LTS版本，server数据库采用MySQL

* zabbix-server + MySQL centos7.4
* zabbix-proxy  centos7.4
* zabbix-agent  centos7.4

# 安装repo

    sudo rpm -ivh http://repo.zabbix.com/zabbix/3.0/rhel/7/x86_64/zabbix-release-3.0-1.el7.noarch.rpm

或者，使用我放在国内的repo，当前版本3.0.14

    sudo curl -o /etc/yum.repos.d/zabbix.repo http://p23blp446.bkt.clouddn.com/zabbix.repo


# 关闭selinux

关闭selinux并且disable相关服务

    sudo setenforce 0
    sudo sed -i 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/selinux/config

# 安装软件

安装依赖、数据库，以及Zabbix-Server

    sudo yum install -y MySQL-python mariadb
    sudo yum install -y epel-release mariadb-server
    sudo systemctl start  mariadb
    sudo systemctl enable mariadb
    sudo yum install -y epel-release zabbix-get zabbix-server-mysql

# 数据库

创建数据库,收据库授权

    mysql -e "CREATE DATABASE zabbix DEFAULT CHARSET UTF8;"
    mysql -e "CREATE USER 'zabbix'@'localhost' IDENTIFIED BY '123456';"
    mysql -e "GRANT ALL ON zabbix.* to 'zabbix'@'localhost';"

# 导入数据库

    gunzip <`ls /usr/share/doc/zabbix-server-mysql-*/create.sql.gz`|mysql -uroot zabbix

# 修改zabbix-server.conf

修改数据库连接

    sed -i "s/# DBPassword=/DBPassword=123456/g" /etc/zabbix/zabbix_server.conf
    sed -i "s/# DBHost=localhost/DBHost=localhost/g" /etc/zabbix/zabbix_server.conf

# 重启zabbix-server

    systemctl restart zabbix-server
    systemctl enable zabbix-server


下一步[安装Zabbix Web](/zabbix-web-install/)
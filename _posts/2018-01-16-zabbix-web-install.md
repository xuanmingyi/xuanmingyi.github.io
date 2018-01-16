---
layout:     post
title:      Zabbix Web 安装
subtitle:   ""
date:       2018-01-16 15:05:00
author:     sin
catalog:    true
header-img: img/bg.jpg
permalink:  /zabbix-web-install/
tags:
    - zabbix
    - 运维
---


#　安装
    yum install httpd php php-mysql php-mbstring php-gd php-bcmath php-ldap php-xml
    yum install zabbix-web

# 修改时区

    sed -i 's/# php_value date.timezone Europe\/Riga/php_value date.timezone Asia\/Shanghai/g' /etc/httpd/conf.d/zabbix.conf

# 重启apache

    systemctl restart httpd
    systemctl enable httpd
    systemctl stop firewalld

# 访问
    http://192.168.199.137/zabbix

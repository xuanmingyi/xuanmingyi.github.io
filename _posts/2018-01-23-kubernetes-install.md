---
layout:     post
title:      使用kubeadm安装２节点kubernetes
subtitle:   ""
date:       2018-01-23 07:56:00
author:     sin
catalog:    true
header-img: img/bg.jpg
permalink:  /kubernetes-install/
tags:
    - Linux
---

# 介绍

kubeadm是官方推荐的安装方式，但是国内由于GFW问题，无法直接安装，所以写了这篇文档,安装版本为 v.1.9.2。

# 系统准备

下面有相关镜像，我已经把需要用到的相关镜像上传到百度云了。

    https://pan.baidu.com/s/1nwO6c6t

解压缩这个包

    tar zvxf kubernetes-v1.9.2.tar.gz -C /opt/

使用centos7.4, 设置hostname,关闭firewalld, selinux, 以及 swap
   
    hostnamectl set-hostname k8s-master

    systemctl stop firewalld
    systemctl disable firewalld

    sed -i "s/SELINUX=enforcing/SELINUX=disabled/g" /etc/sysconfig/selinux
    setenforce 0

    swapoff -a
    sed -i "/swap/d" /etc/fstab

# 部署准备

安装docker

    yum install -y docker
    systemctl enable docker && sudo systemctl start docker

添加内核参数

    cat <<EOF >  /etc/sysctl.d/k8s.conf
    net.bridge.bridge-nf-call-ip6tables = 1
    net.bridge.bridge-nf-call-iptables = 1
    EOF
    sysctl --system

增加本地源

    cat <<EOF > /etc/yum.repos.d/kubernetes.repo
    [kubernetes]
    name=Kubernetes
    baseurl=file:///opt/repo
    enabled=1
    gpgcheck=0
    EOF

安装kubelet、kubeadm、kubectl

    yum install -y kubelet kubeadm kubectl
    systemctl enable kubelet && sudo systemctl start kubelet


导入镜像

    for i in `ls /opt/images`; do
        docker load </opt/images/$i
    done

# Master上初始化集群

使用kubeadm初始化集群

    kubeadm init --kubernetes-version=v1.9.2 --pod-network-cidr=10.244.0.0/16 2>&1 1>k8s_install.txt

这里可以
    tail -f k8s_install.txt查看安装进度

安装完之后，可以根据提示添加配置文件

    mkdir -p $HOME/.kube
    cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
    chown $(id -u):$(id -g) $HOME/.kube/config


应用flannel的网络方案

    kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/v0.9.1/Documentation/kube-flannel.yml


# 增加Slave节点

在完成系统准备和部署准备后，增加Slave节点的步骤比较简单,查看k8s_install.txt中内容。

    You should now deploy a pod network to the cluster.
    Run "kubectl apply -f [podnetwork].yaml" with one of the options listed at:
        https://kubernetes.io/docs/concepts/cluster-administration/addons/

    You can now join any number of machines by running the following on each node
    as root:

    kubeadm join --token b97547.de4aff10941e8d73 172.16.138.154:6443 --discovery-token-ca-cert-hash sha256:05a07331d827a9e48436863a666e8a6f9e42168a5d031c92e47253a3b26c258c


如上所述:

    kubeadm join --token b97547.de4aff10941e8d73 172.16.138.154:6443 --discovery-token-ca-cert-hash sha256:05a07331d827a9e48436863a666e8a6f9e42168a5d031c92e47253a3b26c258c

# 检查

在k8s-master节点上

    [root@k8s-master ~]# kubectl get nodes
    NAME         STATUS    ROLES     AGE       VERSION
    k8s-master   Ready     master    24m       v1.9.2
    k8s-slave1   Ready     <none>    6m        v1.9.2
    [root@k8s-master ~]#
    [root@k8s-master ~]# kubectl get pods --all-namespaces
    NAMESPACE     NAME                                 READY     STATUS    RESTARTS   AGE
    kube-system   etcd-k8s-master                      1/1       Running   8          23m
    kube-system   kube-apiserver-k8s-master            1/1       Running   7          23m
    kube-system   kube-controller-manager-k8s-master   1/1       Running   0          23m
    kube-system   kube-dns-6f4fd4bdf-gm4pp             3/3       Running   0          24m
    kube-system   kube-flannel-ds-l6fms                1/1       Running   0          21m
    kube-system   kube-flannel-ds-mxtl6                1/1       Running   0          7m
    kube-system   kube-proxy-m6b2g                     1/1       Running   0          24m
    kube-system   kube-proxy-wjnf2                     1/1       Running   0          7m
    kube-system   kube-scheduler-k8s-master            1/1       Running   0          24m

# FAQ

#### Q: 系统重启之后如何启动k8s?

只需要确保kubelet启动就可以了， systemctl enable kubelet 会确保开机启动

#### Q: 如何简单排错？

kubeadmin部署的k8s运行在重启中，可以从一下地方找到相关信息

  * docker logs 对应容器
  * tail -f /var/log/messages

#### Q: 碰到etcd启动不了，使用docker logs查看发现　“open /var/lib/etcd/.touch: permission denied” 怎么办？

关闭selinux，零时和永久关闭方法在上文
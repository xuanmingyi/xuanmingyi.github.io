Title: 网络命令
Date: 2020-05-02 02:30
Category: Linux
Tags: linux, network, command line
Slug: network-command
Authors: Xuan Mingyi

### ip命令
* ip route 查看路由
* ip rotue add default via [192.168.65.2] dev [ens33] 添加默认路由
* ip route add [192.168.65.0/24] via  [192.168.65.2]
* ip addr  查看网络接口
* ip addr show [ens33] 显示特定网卡
* ip addr add [192.168.1.100/24] dev [eth0] 设置ip地址
* ip addr del [192.168.1.100/24] dev [eth0] 删除ip地址
* ip link set [eth0] [up] 启动网卡eth0
* ip link set [eth0] [down] 关闭网卡eth0


### brctl命令(linux bridge)
* brctl show 显示所有网桥
* brctl addbr [br0] 添加一个网桥
* brctl addif [br0] [ens33] 添加接口


### ovs-vsctl 命令(Open vSwitch)
* ovs-vsctl show 查看所有ovs网桥
* ovs-vsctl add-br [br0] 添加一个ovs网桥
* ovs-vsctl del-br [br0] 删除一个ovs网桥


### Tap/Tun设备命令
* ip tuntap add tap0 mode tap 创建一个tap0设备
* ip tuntap del tap0 mode tap 删除一个tap0设备


### 网络命名空间
* ip netns 列出所有命名空间
* ip netns exec [ns1] [ip addr]   在网络命名空间ns1中执行命令
* ip netns add [ns1] 新建一个namespace
* ip netns del [ns1] 删除一个namespace
* ip link set [eth0] netns [ns1] 把网卡从主空间移动到ns1
* ip netns exec [ns1] ip link set [eth0] netns [1]  把网卡eth0从ns1中移动到root里
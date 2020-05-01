Title: gRPC通信实验(1)
Date: 2020-05-02 01:09
Category: gRPC
Tags: python, gRPC
Slug: gRPC-1
Authors: Xuan Mingyi

### 准备
安装grpc的工具
```shell
pip3 install grpcio  grpcio-tools
```
### 协议编写

编写服务文件`hello.proto`
```protobuf
service Greeter {
    rpc SayHello (HelloRequest) returns (HelloReply) {}
}

message HelloRequest {
    string name = 1;
}

message HelloReply {
    string message = 1;
}
```

编译
```shell
python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=.  hello.proto
```
编译的结果

* `--python_out=`选项指定的目录，输出`hello_pb2.py`
* `--grpc_python_out=`选项指定的目录，输出`hello_pb2_rpc.py`

不要编辑这两个文件

### 编写服务器
根据`proto`文件,定义一个python类对应。

```python
class Greeter(helloworld_pb2_grpc.GreeterServicer):

    def SayHello(self, request, context):
        return helloworld_pb2.HelloReply(message='Hello, %s!' % request.name)
```

下面是例行性的代码
```python
server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
server.add_insecure_port('[::]:50051')
server.start()
server.wait_for_termination()
```

### 编写客户端

```python
with grpc.insecure_channel('localhost:50051') as channel:
    stub = helloworld_pb2_grpc.GreeterStub(channel)
    response = stub.SayHello(helloworld_pb2.HelloRequest(name='you'))
```

直接获取通道，调用方法


### 例子

[helloworld](https://github.com/grpc/grpc/tree/master/examples/python/helloworld) 这个例子

<script id="asciicast-9BqO3p52jeh3oi6rc4MyLocc9" src="https://asciinema.org/a/9BqO3p52jeh3oi6rc4MyLocc9.js" async></script>
/*
muduo网络库给用户提供了两个主要的类
TcpServer : 用于编写服务器程序的
TcpClient : 用于编写客户端程序的

epoll + 线程池
好处：能够把网络I/O的代码和业务代码区区分开
                        | 用户的连接和断开 用户的可读写事件
*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional> // 绑定器
#include <string>
using namespace std;
using namespace muduo::net;
using namespace muduo;
using namespace placeholders; //参数占位符

/*
基于muduo网络库开发的服务器程序
1.组合TcpServer对象
2.创建EventLoop事件循环对象的指针
3.明确TcpServer构造函数需要什么函数，输出ChatServer的构造函数
4.当前服务器类的构造函数当中,注册处理连接的回调函数和注册用户处理读写的回调函数
5.设置合适的服务端线程数量, muduo库会自己划分i/O线程线程和worker线程
*/
class ChatServer
{
public:
    //通过构造函数传入各个对象
    ChatServer(EventLoop *loop,               // 事件循环
               const InetAddress &listenAddr, // IP+Port ip地址加端口号
               const string &nameArg)         // 服务器名字
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        //给服务器注册用户用户连接的创建和断开回调
        //（不知道该件事情发生以及发生后怎么做，时间不统一，注册回调，在发生时候，调用回调函数）
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1)); //绑定器bind
        //                                 绑定ChatServer的onConnection方法  参数占位符 onConnection方法有一个参数

        //给服务器注册用户读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置服务器端的线程数量 一个I/O线程  三个工作worker线程
        _server.setThreadNum(4); // 把一个用户做I/O事件,当作新用户的连接事件
    }

    //开启事件循环
    void start()
    {
        _server.start();
    }

private:
    //处理用户的连接创建和断开 处理epoll 监听事件listenfd 进行接受处理 accept
    void onConnection(const TcpConnectionPtr &conn)
    {
        //参数包含隐藏的 *this
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "stata:online" << endl;
        }
        // peerAddress 对应地址 localAddress 本地地址  toIp 只返回Ip地址  toIpPort 同时返回iP地址和端口号
        else
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state:offline" << endl;
            conn->shutdown(); // close(fd)
            // _loop->quit();
        }
    }
    //处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn, // 连接数据,进行操作
                   Buffer *buffer,               // 缓冲区 提高数据收发性能
                   Timestamp time)               //  接受到数据的时间信息
    {
        string buf = buffer->retrieveAllAsString(); //将接收到的数据全部放到字符串当中
        cout << "recv data:" << buf << "time" << time.toString() << endl;
        conn->send(buf);
    }

    TcpServer _server; // #1
    EventLoop *_loop;  // #2 组合EventLoop对象 epoll  事件循环 解决单线程运行时不会阻塞的一种机制
};

int main()
{
    EventLoop loop; // epoll
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    server.start(); // 启动服务  listenfd 通过epool_ctl 添加到epoll
    loop.loop();    // epoll_wait 以阻塞方式等待新用户连接,已连接用户的读写事件

    return 0;
}
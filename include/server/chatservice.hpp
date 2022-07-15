#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>

#include "redis.hpp"
#include "json.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "usermodel.hpp"
#include "groupmodel.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;
using namespace placeholders;

// 表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

// 聊天服务器业务类  运用单例模式
class ChatService
{
public:
    //获取单例对象的接口函数
    static ChatService *instance();
    //处理登陆业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 群组
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    // 服务器异常，业务重置方法
    void reset();
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    // 从redis消息队列中获取订阅的信息
    void handleRedisSubscribeMessage(int userid, string msg);

private:
    //单例模式 构造函数私有化
    ChatService();
    //存储消息id和其对应的业务处理方法（消息处理器的表  写消息id处理的操作）
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储在线用户的通信连接
    // 此连接会随着用户的上线和下线做出相应的改变  所有要注意线程安全问题
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 定义互斥锁，保证 _userConnMap 的线程安全
    mutex _connMutex;

    // 数据操作类对象  //////
    UserModel _usermodel;

    // 数据表 outlinemessage 操作对象
    offlineMsgModel _offlineMsgModel;

    // 数据表friend表操作对象
    FriendModel _friendModel;

    // 群组相关对象
    GroupModel _groupModel;

    // redis 操作对象
    Redis _redis;
};

#endif
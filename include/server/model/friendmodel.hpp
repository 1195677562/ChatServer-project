#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include"user.hpp"
#include<vector>
using namespace std;

// 维护好友信息的操作接口方法
class FriendModel
{
    public:
    // 添加好友关系
    void insert(int userid, int friendid);

    // 返回用户好友列表 通过用户id找到用户列表 将friend表和user表进行联合查询，一次操作，避免先查friend表在查user表两次操作
    vector<User> query(int userid);
    private:
};

#endif

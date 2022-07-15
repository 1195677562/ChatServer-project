#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"

// 客户端通过命令查看成员时，不能只显示user的信息
// 群组用户，多了一个role角色信息，从User类直接继承，复用User的其他信息
class GroupUser : public User
{
public:
    void setRole(string role) { this->_role = role; }
    string getRole() { return this->_role; }

private:
    string _role; // role角色信息  在群组中，用户的角色信息
};

#endif
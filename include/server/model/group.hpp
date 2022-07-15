#ifndef GROUP_H
#define GROUP_H

#include "groupuser.hpp"
#include <string>
#include <vector>
using namespace std;

// User表的ORM类
class Group
{
public:
    Group(int id = -1, string name = "", string desc = "")
    {
        this->_id = id;
        this->_name = name;
        this->_desc = desc;
    }

    void setId(int id) { this->_id = id; }
    void setName(string name) { this->_name = name; }
    void setDesc(string desc) { this->_desc = desc; }

    int getId() { return this->_id; }
    string getName() { return this->_name; }
    string getDesc() { return this->_desc; }
    vector<GroupUser> &getUsers() { return this->_users; }

private:
    int _id;   // 组的id
    string _name;   // 组的名字
    string _desc;  // 组的描述
    vector<GroupUser> _users; //一个组中有多少成员，从数据库中将成员放在vector中，从而业务进行使用
};

#endif
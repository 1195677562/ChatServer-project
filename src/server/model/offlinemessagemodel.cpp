#include "db.hpp"
#include "offlinemessagemodel.hpp"

// 存储用户的离线消息
void offlineMsgModel::insert(int userid, string msg)
{
    // 1. 组装sql
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemessage values ( %d, '%s')", userid, msg.c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

// 删除用户的离线消息
void offlineMsgModel::remove(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "delete from offlinemessage where userid = %d", userid);
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

// 查询用户的离线消息
vector<string> offlineMsgModel::query(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "select message from offlinemessage where userid = %d", userid);

    vector<string> vec;
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            // MYSQL_ROW 表示有一条数据保存在数据集中 ROW[1] 就是保存的内容
            // 把所有userid用户的所有离线消息放入vec中返回‘
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr) // 该userid下的消息，只需要查询一次
            {
                vec.push_back(row[0]);
            }
            mysql_free_result(res); // 将查询到的res数据释放掉
            return vec;
        }
    }
    return vec;
}

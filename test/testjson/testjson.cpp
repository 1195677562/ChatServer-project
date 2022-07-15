#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// json序列化示例
void func1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "张三";
    js["to"] = "李四";
    js["msg"] = "你在干什么";

    string sendBuf = js.dump();
    cout << sendBuf.c_str() << endl; //转成字符串，通过网络发送

    // cout<<js<<endl; // 提供输出重载运算符
    //相当于map中的key值
}

//序列化示例2
void func2()
{
    json js;
    js["id"] = {1, 2, 3, 4, 5};
    js["name"] = "玛卡巴卡";
    js["msg"]["叮叮车"] = "hello audi";
    //等同于下面这句添加
    js["msg"] = {"叮叮车", "hello audi"};

    cout << js << endl;
}

// json示例3
void func3()
{
    json js;

    //序列化容器vector
    vector<int> vt;
    for (int i = 0; i < 5; ++i)
    {
        vt.push_back(i);
    }

    js["list"] = vt;

    //序列化容器map
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "张家界"});
    js["path"] = m;

    string sendBuf = js.dump();
    cout << sendBuf.c_str() << endl; // json 数据对象转化成 序列化 json 字符串

    // cout<< js << endl;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// json 反序列化示例
string func4()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "张三";
    js["to"] = "李四";
    js["msg"] = "你在干什么";

    string sendBuf = js.dump();
    return sendBuf;

    // cout<<js<<endl; // 提供输出重载运算符
    //相当于map中的key值
}

string func5()
{
    json js;

    //序列化容器vector
    vector<int> vt;
    for (int i = 0; i < 5; ++i)
    {
        vt.push_back(i);
    }

    js["list"] = vt;

    //序列化容器map
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "张家界"});
    js["path"] = m;

    string sendBuf = js.dump();
    return sendBuf;
}

int main()
{
    //数据的反序列化接受
    string recvBuf = func5();
    
    // json 字符串 转化为 反序列化 数据对象(看作容器，方便访问)
    json jsbuf = json::parse(recvBuf); // 返回一个json对象
    // cout<< jsbuf["msg_type"] << endl;
    // cout<< jsbuf["from"] << endl;
    // cout<< jsbuf["to"] << endl;
    // cout<< jsbuf["msg"] << endl;

    vector<int> vt = jsbuf["list"]; // js对象里面的数据类型，直接放入vector容器中
    for (auto &v : vt)
    {
        cout << v << " ";
    }
    cout << endl;

    map<int, string> m = jsbuf["path"];
    for (auto &p : m)
    {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;

    //序列化发送
    // func4();
    return 0;
}

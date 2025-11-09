/*
    string容器 常用操作
        1. 拼接
        2. 查找
        3. 替换
        4. 比较
        5. 截取子串
        6. 解析字符串，将 www baidu com cn 截取后存储到 vector容器中
        7. 插入和删除
        8. std::string 转为 const char*
        9. 将字符串中的所有字母 转大写/转小写
*/
#include <iostream>
#include <vector>


// 构造、赋值
void  test00()
{
    std::cout << __func__ << std::endl;

    // 1. 调用默认构造函数，创建一个字符串长度为 0的stirng对象
    std::string s1();

    // 2. 转换构造，创建一个string对象，并使用C风格字符串初始化 s2
    std::string s2("abcdef");

    // 3. 截取 str部分 来初始化 s3
    const char *str = "helloworld";
    std::string s3(str, 4);  // hell

    // 4. 创建一个以指定数量的字符来初始化string对象
    std::string s4(50, '*');  // **************************************************
    
    
    std::cout << s4 << std::endl;
}


// 字符串拼接
void test01()
{
    std::cout << __func__ << std::endl;
    std::string a1 = "Tom";
    a1 += ", Hello";
    std::cout << a1 << std::endl;

    a1.append(" World");
    std::cout << a1 << std::endl;
/*
Tom, Hello
Tom, Hello World
*/
}

// 查找
void test02()
{
    std::cout << __func__ << std::endl;
    std::string str = "abcdefg";
    int pos = str.find("de");
    if(pos == -1)
    {
        std::cout << "未找到" << std::endl;
    }
    else
    {
        std::cout << "找到子串, " << "pos: " << pos << std::endl;
    }

    std::string str2 = "abcdefghide";
    int pos1 = str2.find("de");   // 从左往右找
    int pos2 = str2.rfind("de");  // 从右往左找
    std::cout << "pos1: " << pos1 << std::endl;
    std::cout << "pos2: " << pos2 << std::endl;
}

// 替换
void test03()
{
    std::cout << __func__ << std::endl;
    std::string str1 = "abcdefgh";
    std::string str2 = "abcdefgh";
    str1.replace(1, 3, "123456");  // 参数2是对 str1起作用的，不要误解成 只能参数3的前3个字符
    std::cout << "str1: " << str1 << std::endl;

    str2.replace(1, 5, "123456");  // 参数2是对 str1起作用的，不要误解成 只能参数3的前5个字符
    std::cout << "str2: " << str2 << std::endl;
/*
str1: a123456efgh
str2: a123456gh
*/
}

// 比较
void test04()
{
    std::cout << __func__ << std::endl;
    std::string str1 = "abcdef2";
    std::string str2 = "abcdef1";

    if (str1.compare(str2) == 0)
        std::cout << "str1 == str2" << std::endl;
    else if(str1.compare(str2) > 0)
        std::cout << "str1 > str2" << std::endl;
    else if(str1.compare(str2) < 0)
        std::cout << "str1 < str2" << std::endl;
        
}

// 截取子串
void test05()
{
    std::cout << __func__ << std::endl;
    std::string email = "helloworld@gmail.com";
    // 截取用户名
    int pos = email.find("@");
    std::string username = email.substr(0, pos);  // 从0开始截取，截取pos个字符
    std::cout << "username: " << username << std::endl;
}

// 解析字符串，将 www baidu com cn 截取后存储到 vector容器中
void test06()
{
    std::cout << __func__ << std::endl;
    std::vector<std::string> v;
    std::string url = "www.baidu.com.cn";
    int prev_pos = 0;
    int next_pos = 0;

    while(true)
    {
        next_pos = url.find(".", next_pos);
        if(next_pos == -1)
        {
            // 处理最后一个 "cn"
            std::string text = url.substr(prev_pos, url.size() - prev_pos);
            v.push_back(text);
            break;
        }
        std::string text = url.substr(prev_pos, next_pos - prev_pos);  // 第2个参数表示要截取多少个字符
        v.push_back(text);
        prev_pos = ++next_pos;
    }

    // 遍历vector
    std::vector<std::string>::iterator itBegin = v.begin();
    while(itBegin != v.end())
    {
        std::cout << *itBegin << std::endl;
        itBegin++;
    }
}

// 7. 插入和删除
void test07()
{
    std::cout << __func__ << std::endl;
    std::string str1 = "hello";
    str1.insert(1, "123");  // 在 索引1的位置插入字符串 "123"
    std::cout << str1 << std::endl;

    str1.erase(1, 3);  // 从 1开始删除，删除 3个字符
    std::cout << str1 << std::endl;
}

// 8. std::string 转为 const char*
void test08()
{
    std::cout << __func__ << std::endl;
    std::string str = "world";
    const char* cstr = str.c_str();
}

// 9. 将字符串中的所有字母 转大写/转小写
void test09()
{
    std::cout << __func__ << std::endl;
    std::string str = "abasdaASDSasd";
    for(int i = 0; i < str.size(); i++)
    {
        str.at(i) = toupper(str.at(i));  // 转大写
        str.at(i) = tolower(str.at(i));  // 转小写
    }
    std::cout << str << std::endl;
}

int main(void)
{
    // 0. 构造，赋值
    test00();
    std::cout << std::endl;
    // 1. 拼接
    test01();
    std::cout << std::endl;
    // 2. 查找
    test02();
    std::cout << std::endl;
    // 3. 替换
    test03();
    std::cout << std::endl;
    // 4. 比较
    test04();
    std::cout << std::endl;
    // 5. 截取子串
    test05();
    std::cout << std::endl;
    // 6. 解析字符串，将 www baidu com cn 截取后存储到 vector容器中
    test06();
    std::cout << std::endl;
    // 7. 插入和删除
    test07();
    std::cout << std::endl;
    // 8. std::string 转为 const char*
    test08();
    std::cout << std::endl;
    // 9. 将字符串中的所有字母 转大写/转小写
    test09();
    std::cout << std::endl;
    return 0;
}

/*
test00
**************************************************

test01
Tom, Hello
Tom, Hello World

test02
找到子串, pos: 3
pos1: 3
pos2: 9

test03
str1: a123456efgh
str2: a123456gh

test04
str1 > str2

test05
username: helloworld

test06
www
baidu
com
cn

test07
h123ello
hello

test08

test09
abasdaasdsasd
*/
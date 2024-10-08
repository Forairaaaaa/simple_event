/**
 * @file start_and_stop.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <mooncake_event.h>
#include <iostream>

using namespace mooncake;

// 事件回调
void onTeaTime1(EventArgs_t* args)
{
    std::cout << "111\n";
}
void onTeaTime2(EventArgs_t* args)
{
    std::cout << "222\n";
}
void onTeaTime3(EventArgs_t* args)
{
    std::cout << "333\n";
}

int main()
{
    // 监听事件
    auto listener_id_1 = GetEventBroker().startListen("三点几啦", onTeaTime1);
    auto listener_id_2 = GetEventBroker().startListen("三点几啦", onTeaTime2);
    auto listener_id_3 = GetEventBroker().startListen("三点几啦", onTeaTime3);

    // 发布事件
    std::cout << ">> firing..\n";
    GetEventBroker().fire("三点几啦");
    // 输出:
    // 111
    // 222
    // 333

    // 有三个个监听者
    std::cout << ">> firing with " << GetEventBroker().getListenerNum("三点几啦") << " listeners..\n";
    for (int i = 0; i < 3; i++)
        GetEventBroker().fireAsync("三点几啦");

    std::cout << ">> handling..\n";
    GetEventBroker().handleAsyncEvents();
    // 输出:
    // 111
    // 222
    // 333
    // x3

    // 删掉一个监听者
    GetEventBroker().stopListen("三点几啦", listener_id_2);
    std::cout << ">> firing with " << GetEventBroker().getListenerNum("三点几啦") << " listeners..\n";
    for (int i = 0; i < 3; i++)
        GetEventBroker().fireAsync("三点几啦");

    std::cout << ">> handling..\n";
    GetEventBroker().handleAsyncEvents();
    // 输出:
    // 111
    // 333
    // x3

    // 删掉全部监听者
    GetEventBroker().stopListen("三点几啦", listener_id_1);
    GetEventBroker().stopListen("三点几啦", listener_id_3);
    std::cout << ">> firing with " << GetEventBroker().getListenerNum("三点几啦") << " listeners..\n";
    for (int i = 0; i < 3; i++)
        GetEventBroker().fireAsync("三点几啦");

    std::cout << ">> handling..\n";
    GetEventBroker().handleAsyncEvents();
    // 无输出

    return 0;
}

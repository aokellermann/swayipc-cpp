#pragma once

#include <swayipc-cpp/safequeue.hpp>
#include <swayipc-cpp/json.hpp>
#include <swayipc-cpp/message.hpp>

namespace swayipc {

template <class T>
class event_stream {
public:
    event_stream(safe_queue<message_s>*);
    T get_event();
    bool empty();
private:
    safe_queue<message_s>* m_queue;
};

template <class T>
event_stream<T>::event_stream(safe_queue<message_s>* queue)
    : m_queue(queue) {}

template <class T>
T event_stream<T>::get_event() {
    auto message = m_queue->pop();
    return ::nlohmann::json::parse(message.payload).get<T>();
}

template <class T>
bool event_stream<T>::empty() {
    return m_queue->empty();
}

}

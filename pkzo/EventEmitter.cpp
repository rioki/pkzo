// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#include "EventEmitter.h"

#include <stdexcept>

namespace pkzo
{
    EventEmitter::EventEmitter() = default;

    EventEmitter::~EventEmitter() = default;

    unsigned int EventEmitter::add_listener(unsigned int event_id, std::function<void ()> cb)
    {
        if (!cb)
        {
            throw std::invalid_argument("EventEmitter::add_listener: No callbak provided.");
        }
    
        std::lock_guard<std::mutex> lock(mutex);

        unsigned int listener_id = ++last_listener;
        listeners.insert(std::make_pair(event_id, std::make_shared<Listener<>>(listener_id, cb)));

        return listener_id;       
    }

    unsigned int EventEmitter::on(unsigned int event_id, std::function<void ()> cb)
    {
        return add_listener(event_id, cb);
    }

    void EventEmitter::remove_listener(unsigned int listener_id)
    {
        std::lock_guard<std::mutex> lock(mutex);

        auto i = std::find_if(listeners.begin(), listeners.end(), [&] (std::pair<const unsigned int, std::shared_ptr<ListenerBase>> p) {
            return p.second->id == listener_id;
        });
        if (i != listeners.end())
        {
            listeners.erase(i);
        }
        else
        {
            throw std::invalid_argument("EventEmitter::remove_listener: Invalid listener id.");
        }
    }
}

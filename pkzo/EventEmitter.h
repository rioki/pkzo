// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_EVENT_EMITTER_H_
#define _PKZO_EVENT_EMITTER_H_

#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <list>
#include <algorithm>

#include "defines.h"

namespace pkzo
{
    /*!
     * Object that emits events.
     */
    class PKZO_EXPORT EventEmitter
    {
    public:
    
        EventEmitter();
        EventEmitter(const EventEmitter&) = delete; 
        ~EventEmitter();
        EventEmitter& operator = (const EventEmitter&) = delete; 

        /*!
         * Add a listener.
         *
         * @param event_id the id of the event.
         * @param cb the callback to be emitted
         * @retunr a handle that can be used to remove the listner again
         * @{
         */
        template <typename... Args>
        unsigned int add_listener(unsigned int event_id, std::function<void (Args...)> cb);
        unsigned int add_listener(unsigned int event_id, std::function<void ()> cb);
        template<typename LambdaType>
        unsigned int add_listener(unsigned int event_id, LambdaType lambda) {
            return add_listener(event_id, make_function(lambda));
        }
        
        template <typename... Args>
        unsigned int on(unsigned int event_id, std::function<void (Args...)> cb);
        unsigned int on(unsigned int event_id, std::function<void ()> cb);
        template<typename LambdaType>
        unsigned int on(unsigned int event_id, LambdaType lambda) {
            return on(event_id, make_function(lambda));
        }
        /*! @} */

        /*!
         * Remove the listener.
         *
         * @param listener_id the listner
         */
        void remove_listener(unsigned int listener_id);

        /*!
         * Emit an event.
         *
         * @param event_id the id of the event
         * @param args the arguments to the event
         */
        template <typename... Args>
        void emit(unsigned int event_id, Args... args);

    private:
        struct ListenerBase
        {
            ListenerBase() {}

            ListenerBase(unsigned int i)
            : id(i) {}

            virtual ~ListenerBase() {}

            unsigned int id;
        };

        template <typename... Args>
        struct Listener : public ListenerBase
        {
            Listener() {}

            Listener(unsigned int i, std::function<void (Args...)> c)
            : ListenerBase(i), cb(c) {}

            std::function<void (Args...)> cb;
        };

        std::mutex mutex;
        unsigned int last_listener;
        std::multimap<unsigned int, std::shared_ptr<ListenerBase>> listeners;

        // http://stackoverflow.com/a/21000981
        template <typename T>
        struct function_traits
           : public function_traits<decltype(&T::operator())>
        {};

        template <typename ClassType, typename ReturnType, typename... Args>
        struct function_traits<ReturnType(ClassType::*)(Args...) const> {
           typedef std::function<ReturnType (Args...)> f_type;
        };

        template <typename L> 
        typename function_traits<L>::f_type make_function(L l){
          return (typename function_traits<L>::f_type)(l);
        }
    };

    template <typename... Args>
    unsigned int EventEmitter::add_listener(unsigned int event_id, std::function<void (Args...)> cb)
    {
        if (!cb)
        {
            throw std::invalid_argument("EventEmitter::add_listener: No callbak provided.");
        }

        std::lock_guard<std::mutex> lock(mutex);

        unsigned int listener_id = ++last_listener;
        listeners.insert(std::make_pair(event_id, std::make_shared<Listener<Args...>>(listener_id, cb)));

        return listener_id;        
    }

    template <typename... Args>
    unsigned int EventEmitter::on(unsigned int event_id, std::function<void (Args...)> cb)
    {
        return add_listener(event_id, cb);
    }

    template <typename... Args>
    void EventEmitter::emit(unsigned int event_id, Args... args)
    {
        std::list<std::shared_ptr<Listener<Args...>>> handlers;
    
        {
            std::lock_guard<std::mutex> lock(mutex);

            auto range = listeners.equal_range(event_id);
            handlers.resize(std::distance(range.first, range.second));
            std::transform(range.first, range.second, handlers.begin(), [] (std::pair<const unsigned int, std::shared_ptr<ListenerBase>> p) {
                auto l = std::dynamic_pointer_cast<Listener<Args...>>(p.second);
                if (l)
                {
                    return l;
                }
                else
                {
                    throw std::logic_error("EventEmitter::emit: Invalid event signature.");
                }
            });
        }

        for (auto& h : handlers)
        {
            h->cb(args...);
        }        
    }
}

#endif
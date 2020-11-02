#ifndef SIGNAL_H
#define SIGNAL_H

#include <list>
#include <algorithm>


namespace rg
{
    template<typename... Types>
    class Signal 
    {
        std::list<void (*)(Types ...)> m_function_ptrs;

    public:

        void connect(void (*func)(Types ...))
        {
            m_function_ptrs.push_back(func);
        }


        bool disconnect(void (*func)(Types ...))
        {
            auto it = std::find(m_function_ptrs.begin(), m_function_ptrs.end(), func);
            if (it != m_function_ptrs.end())
            {
                m_function_ptrs.erase(it);
                return true;
            }

            return false;
        }

        void emit(const Types &...args)
        {
            for (auto &x : m_function_ptrs)
            {
                x(args...);
            }
        }

    };
}

#endif

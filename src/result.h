#pragma once

#include "internal.h"

namespace Roc
{
    template <typename O, typename E>
    class Result : Value
    {
        union Payload
        {
            O ok;
            E err;
        } m_payload;
        bool m_is_ok;

    public:
        static Result make_ok(O val)
        {
            Result r;
            r.m_payload.ok = val;
            r.m_is_ok = true;
            return r;
        }

        static Result make_err(E val)
        {
            Result r;
            r.m_payload.err = val;
            r.m_is_ok = false;
            return r;
        }

        bool is_ok() const
        {
            return m_is_ok;
        }

        O* ok() const
        {
            return m_is_ok ? &m_payload->ok : NULL;
        }

        E* err() const
        {
            return m_is_ok ? NULL : &m_payload->err;
        }

        ~Result()
        {
            rc_decrement();
        }

        bool rc_unique() const
        {
            return true;
        };

        void rc_increment()
        {
            if (m_is_ok)
                m_payload.ok.rc_increment();
            else
                m_payload.err.rc_increment();
        };

        void rc_decrement()
        {
            if (m_is_ok)
                m_payload.ok.rc_decrement();
            else
                m_payload.err.rc_decrement();
        };
    };
};

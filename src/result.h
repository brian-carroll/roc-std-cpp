#pragma once

#include "internal.h"

namespace Roc
{

    template <typename O, typename E>
    class Result : Value
    {
        union ResultPayload
        {
            O ok;
            E err;

            ResultPayload(bool is_ok)
            {
                if (is_ok)
                    ok = O();
                else
                    err = E();
            }

            ResultPayload(const O &other)
            {
                ok = other;
            }

            // This is a problem if O and E are the same type            
            ResultPayload(const E &other)
            {
                err = other;
            }

            ~ResultPayload()
            {
            }
        } m_payload;
        bool m_is_ok;

    public:
        Result(bool is_ok)
            : m_payload(is_ok), m_is_ok(is_ok)
        {
        }

        Result(const Result &other)
        {
            m_is_ok = other.m_is_ok;
            m_payload = other.m_payload;
            rc_increment();
        }

        static Result make_ok(O val)
        {
            Result r(true);
            r.m_payload.ok = val;
            return r;
        }

        static Result make_err(E val)
        {
            Result r(false);
            r.m_payload.err = val;
            return r;
        }

        bool is_ok() const
        {
            return m_is_ok;
        }

        O *ok() const
        {
            return m_is_ok ? &m_payload.ok : NULL;
        }

        E *err() const
        {
            return m_is_ok ? NULL : &m_payload.err;
        }

        ~Result()
        {
            if (m_is_ok)
            {
                m_payload.ok.~O();
            }
            else
            {
                m_payload.err.~E();
            }
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

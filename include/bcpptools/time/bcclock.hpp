/**
*
* The Black Codex Library: Chapter: C++ Tools
*
* https://github.com/tbc-beren/BCppTools
*
* Mozilla Public License Version 2.0
* https://github.com/tbc-beren/BCppTools/blob/master/LICENSE
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* https://mozilla.org/MPL/2.0/.
*
*/
#pragma once

#include <memory>
#include <cstdint>
#include <chrono>

namespace bcpptools {

class BCClockInstance
{
public:
    virtual uint64_t    now() const                 =0;
    virtual bool        advance(uint64_t seconds)   =0;
};

class BCClockSystem : public BCClockInstance
{
public:
    uint64_t now() const {
        using namespace std::chrono;
        const auto now = system_clock::now();
        const milliseconds ms = duration_cast<milliseconds>(now.time_since_epoch());
        return ms.count();
    }
    bool advance(uint64_t seconds) {
        // This clock does not support fast forward
        (void)(seconds);
        return false;
    }
};

class BCClockFFw : public BCClockInstance
{
    uint64_t   mTime;

public:
    BCClockFFw()
    : mTime(0)
    {}
    uint64_t now() const {
        return mTime;
    }
    bool advance(uint64_t seconds) {
        mTime += seconds;
        return true;
    }
};

class BCClock
{
public:
    typedef std::shared_ptr<BCClockInstance> BCClockPtr;

    static const int SECONDS = 1000;

    static uint64_t now() {
        return instance()->now();
    }
    static uint64_t nowAs(int unit) {
        return instance()->now() / unit;
    }
    static uint64_t nowAsSeconds() {
        return nowAs(SECONDS);
    }
    static bool advance(uint64_t seconds) {
        return instance()->advance(seconds);
    }
    static void setClock(BCClockPtr clock) {
        instance(clock);
    }
    static void setClock() {
        setClock(std::make_shared<BCClockSystem>());
    }

private:
    static BCClockPtr instance(BCClockPtr newInstance = BCClockPtr()) {
        static BCClockPtr mClock = std::make_shared<BCClockSystem>();
        if (newInstance) {
            mClock = newInstance;
        }
        return mClock;
    }
};

template<class TClock> class BCClockScoped
{
public:
    BCClockScoped() {
        BCClock::setClock(std::make_shared<TClock>());
    }
    ~BCClockScoped() {
        BCClock::setClock();
    }
};

typedef BCClockScoped<BCClockFFw> BCClockFFwScoped;

} // namespace bcpptools

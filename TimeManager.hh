#ifndef TIMEMANAGER_H_
#define TIMEMANAGER_H_

#include <chrono>

class TimeManager {
    private:
        static TimeManager tm;
        std::chrono::system_clock::time_point _Start;
        std::chrono::system_clock::time_point _Update;
        std::chrono::system_clock::time_point _Update2;
    public:
        ~TimeManager();
        static TimeManager& GetInstance();
        void Start();
        void Update();
        unsigned int GetElapsedTime() const;
        unsigned int GetStartedTime() const;
    protected:
        TimeManager();
        TimeManager& operator=(const TimeManager&);
        TimeManager(const TimeManager&);

};

#endif

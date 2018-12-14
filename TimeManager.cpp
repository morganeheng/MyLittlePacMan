#include "TimeManager.hh"

TimeManager TimeManager::tm = TimeManager();

TimeManager::TimeManager() {
    Start();
}

TimeManager::~TimeManager() {

}

TimeManager& TimeManager::GetInstance() {
    return tm;
}

void TimeManager::Start() {
    this->_Start = std::chrono::system_clock::now();
    this->_Update = this->_Start;
    this->_Update2 = this->_Start;
}

void TimeManager::Update() {
    this->_Update = this->_Update2;
    this->_Update2 = std::chrono::system_clock::now();
}

unsigned int TimeManager::GetElapsedTime() const {
    if (this->_Update <= this->_Start)
        return 0;
    return std::chrono::duration_cast<std::chrono::milliseconds>(this->_Update2 - this->_Update).count();
}

unsigned int TimeManager::GetStartedTime() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(this->_Update2 - this->_Start).count();
}

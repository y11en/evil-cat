#include <vector>
#include <functional>
#include <mutex>
#include "controller.h"
#include "settings.h"

Controller &Controller::getInstance() {
    static Controller instance;
    return instance;
}

// generally, we call this function in the 'init' stage
// we add all the GUI callbacks to the GUI thread

bool Controller::addGuiCallback(std::function<bool()> condition, std::function<void()> callback) {
    std::lock_guard lock(guiCallbacksMutex);
    guiCallbacks.emplace_back(condition, callback);
    return true;
}

// this function is invoked from the GUI thread
// we call all the gui callbacks here
// eg. if the 'ESP' is on, we call the ESP callback to draw boxes around the players

void Controller::callGuiCallbacks() {
    std::lock_guard lock(guiCallbacksMutex);
    for (const auto&[condition, callback]: guiCallbacks) {
        if (condition()) {
            callback();
        }
    }
}

// fast loop is designed to adapt 'lock health', 'lock position', ...
//
// the speed of the fast loop is not the same as the gui thread (up to 60 fps)
// it is just like a busy-wait loop, and it is asynchronous to the GUI thread.
//
// we use the return value of the callback to determine whether to continue
// calling it in the loop, return false means the callback want to be removed
// from the fast loop callback list.

bool Controller::addFastLoopCallback(std::function<bool()> callback) {
    std::lock_guard lock(fastLoopCallbacksMutex);
    fastLoopCallbacks.emplace_back(callback);

    // notify the fast loop thread to wake up
    // because if we don't use this feature, the fast loop thread will sleep
    // we don't want to consume too much CPU cycles :)
    fastLoopCV.notify_one();

    return true;
}

// call each callback in the fast loop callback list
// if each of them returns false, we remove it from the list

void Controller::callFastLoopCallbacks() {
    while (!Settings::getInstance().exit) {
        std::unique_lock lock(fastLoopCallbacksMutex);

        // wait until the fast loop callback list is not empty
        // but we should check the exit flag in the settings
        // because when we want to exit the program,
        // we should stop the fast loop thread
        if (!fastLoopCV.wait_for(
                lock,
                std::chrono::seconds(1),
                [this]() { return !fastLoopCallbacks.empty(); })) {
            continue;
        }

        // call each callback in the fast loop callback list
        for (auto it = fastLoopCallbacks.begin(); it != fastLoopCallbacks.end();) {
            auto callback = *it;
            if (!callback()) {
                it = fastLoopCallbacks.erase(it);
            } else {
                ++it;
            }
        }
    }
}




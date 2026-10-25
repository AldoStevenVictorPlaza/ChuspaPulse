#include <csignal>
#include <atomic>

std::atomic<bool> isRunning = true;

void handler(int signal) {
    isRunning = false;
}

void setupSignalHandler() {
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
}

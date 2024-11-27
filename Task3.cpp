#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

enum class EventType {
    TAP,
    SWIPE
};

class Event {
public:
    Event(EventType type, int x, int y, std::time_t timestamp)
        : eventType(type), x(x), y(y), timestamp(timestamp) {}

    EventType eventType;
    int x, y;
    std::time_t timestamp;
};

EventType randomEventType() {
    return (rand() % 2 == 0) ? EventType::TAP : EventType::SWIPE;
}

int randomCoordinate() {
    return rand() % 100;
}

void generateSwipe(int& startX, int& startY, int& endX, int& endY) {
    startX = randomCoordinate();
    startY = randomCoordinate();
    endX = randomCoordinate();
    endY = randomCoordinate();
}

void handleTap(const Event& event) {
    std::cout << "TAP at (" << event.x << ", " << event.y << ") at timestamp " << event.timestamp << std::endl;
}

void handleSwipe(const Event& event) {
    std::string direction;

    if (event.x < event.y)
        direction = "Up/Down";
    else
        direction = "Left/Right";

    std::cout << "SWIPE from (" << event.x << ", " << event.y << ") to (" 
              << event.x + 10 << ", " << event.y + 10 << ") - Direction: " 
              << direction << " at timestamp " << event.timestamp << std::endl;
}

int main() {
    srand(time(0));

    std::queue<Event> eventQueue;

    for (int i = 0; i < 10; ++i) {
        EventType eventType = randomEventType();
        int x = randomCoordinate();
        int y = randomCoordinate();
        std::time_t timestamp = std::time(nullptr);

        if (eventType == EventType::TAP) {
            eventQueue.push(Event(EventType::TAP, x, y, timestamp));
        } else if (eventType == EventType::SWIPE) {
            int endX, endY;
            generateSwipe(x, y, endX, endY);
            eventQueue.push(Event(EventType::SWIPE, x, y, timestamp));
        }
    }

    while (!eventQueue.empty()) {
        Event event = eventQueue.front();
        eventQueue.pop();

        if (event.eventType == EventType::TAP) {
            handleTap(event);
        } else if (event.eventType == EventType::SWIPE) {
            handleSwipe(event);
        }
    }

    return 0;
}
/*TAP at (23, 45) at timestamp 1672446556
SWIPE from (12, 34) to (56, 78) - Direction: Down at timestamp 1672446556
TAP at (67, 89) at timestamp 1672446556
SWIPE from (22, 11) to (33, 44) - Direction: Right at timestamp 1672446556
...*/

#pragma once

class SelectionTracker
{
private:
    int currentIndex;
    int previousIndex;

public:
    SelectionTracker(int current = 0, int previous = 0)
        : currentIndex(current), previousIndex(previous)
    {
    }

    void moveUp() { --currentIndex; }
    void moveDown() { ++currentIndex; }

    bool hasChanged() { return currentIndex != previousIndex; }

    void updatePrevious() { previousIndex = currentIndex; }
    int getCurrent() { return currentIndex; }

    void setCurrentIndex(int index) { currentIndex = index; }
    int getPrevious() { return previousIndex; }
};
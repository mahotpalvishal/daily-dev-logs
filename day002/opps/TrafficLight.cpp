// traffic_light.cpp
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

/**
 * Color represents the possible traffic light colors.
 * Durations: RED = 30s, GREEN = 25s, YELLOW = 5s.
 * Cycle: RED -> GREEN -> YELLOW -> RED -> ...
 */
enum class Color {
    RED,
    GREEN,
    YELLOW
};

// Duration (in seconds) for a given color.
static int durationOf(Color c) {
    switch (c) {
        case Color::RED:    return 30;
        case Color::GREEN:  return 25;
        case Color::YELLOW: return 5;
    }
    return 30; // unreachable
}

// Next color in the repeating cycle.
static Color nextOf(Color c) {
    switch (c) {
        case Color::RED:    return Color::GREEN;
        case Color::GREEN:  return Color::YELLOW;
        case Color::YELLOW: return Color::RED;
    }
    return Color::RED; // unreachable
}

// Name of the color, e.g. "RED".
static std::string nameOf(Color c) {
    switch (c) {
        case Color::RED:    return "RED";
        case Color::GREEN:  return "GREEN";
        case Color::YELLOW: return "YELLOW";
    }
    return "RED"; // unreachable
}

// Parse a color name (case-insensitive); unrecognized -> RED.
static Color parseColor(const std::string& s) {
    std::string upper = s;
    std::transform(upper.begin(), upper.end(), upper.begin(),
                   [](unsigned char ch) { return std::toupper(ch); });

    if (upper == "RED")    return Color::RED;
    if (upper == "GREEN")  return Color::GREEN;
    if (upper == "YELLOW") return Color::YELLOW;
    return Color::RED; // default for unrecognized
}

class TrafficLight {
public:
    /**
     * Constructs a TrafficLight starting on the given color.
     * Accepts RED, GREEN, or YELLOW (case-insensitive).
     * Any unrecognized value (or empty string) defaults to RED.
     */
    explicit TrafficLight(const std::string& startColor)
        : current_(parseColor(startColor)) {}

    // Returns the current color's name.
    std::string getColor() const {
        return nameOf(current_);
    }

    // Returns the current color's duration in seconds.
    int getDuration() const {
        return durationOf(current_);
    }

    // Advances once through the cycle and returns the new color's name.
    std::string next() {
        current_ = nextOf(current_);
        return nameOf(current_);
    }

    // Human-readable description, e.g. "RED for 30 seconds".
    std::string describe() const {
        return nameOf(current_) + " for " +
               std::to_string(durationOf(current_)) + " seconds";
    }

private:
    Color current_;
};

// ------------------- demo -------------------
int main() {
    TrafficLight t("green");
    std::cout << t.getColor()    << "\n"; // GREEN
    std::cout << t.getDuration() << "\n"; // 25
    std::cout << t.describe()    << "\n"; // GREEN for 25 seconds
    std::cout << t.next()        << "\n"; // YELLOW
    std::cout << t.next()        << "\n"; // RED
    std::cout << t.next()        << "\n"; // GREEN

    TrafficLight def("purple");           // unrecognized -> RED
    std::cout << def.getColor()  << "\n"; // RED
}
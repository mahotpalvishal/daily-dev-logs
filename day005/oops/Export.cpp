#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class ExportFormat {
public:
    virtual ~ExportFormat() = default;

    // Template Method
    string exportEvents(const vector<string>& events) {
        if (events.empty()) {
            return "INVALID";
        }
        return render(events);
    }

protected:
    virtual string render(const vector<string>& events) = 0;
};

class CsvFormat : public ExportFormat {
protected:
    string render(const vector<string>& events) override {
        string result;

        for (size_t i = 0; i < events.size(); i++) {
            if (i > 0) result += ",";
            result += events[i];
        }

        return result;
    }
};

class SummaryFormat : public ExportFormat {
protected:
    string render(const vector<string>& events) override {
        string result = to_string(events.size()) + " events: ";

        for (size_t i = 0; i < events.size(); i++) {
            if (i > 0) result += " | ";
            result += events[i];
        }

        return result;
    }
};

class JsonFormat : public ExportFormat {
protected:
    string render(const vector<string>& events) override {
        string result = "[";

        for (size_t i = 0; i < events.size(); i++) {
            if (i > 0) result += ",";
            result += "\"" + events[i] + "\"";
        }

        result += "]";
        return result;
    }
};

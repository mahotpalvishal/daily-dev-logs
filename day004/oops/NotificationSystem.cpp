/**
Design a notification center that can send messages through Email, SMS, and Push channels. Every channel has a destination and can identify itself, but each one renders messages differently.

The provided NotificationCenter class supports these operations:

- NotificationCenter() creates a center with no channels.
- int addEmail(String to) adds an Email channel and returns its index.
- int addSms(String phone) adds an SMS channel and returns its index.
- int addPush(String device) adds a Push channel and returns its index.
- int count() returns how many channels have been added.
- String channelOf(int index) returns "email", "sms" or "push".
- String send(int index, String message) returns what that channel produces.
- String[] sendAll(String message) returns what every channel produces, in the order they were added.
- Each channel owns its rendering rule:
    - Email returns "EMAIL to <to>: <message>" without changing the message.
    - SMS returns "SMS to <phone>: <message>", shortening messages longer than 20 characters to their first 20 characters.
    - Push returns "PUSH to <device>: <MESSAGE>", converting the message to uppercase.
- Indexes are assigned in the order channels are added, starting at 0. An index outside that range returns "UNKNOWN" from both send and channelOf.

- Your task is to implement the abstract Alert base class and the concrete EmailAlert, SmsAlert, and PushAlert subclasses. Do not modify the provided NotificationCenter class. The center should be able to call channel and render through the shared type without checking which concrete channel it holds.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Alert
class Alert {
public:
    virtual string channel() const = 0;
    virtual string render(const string& message) const = 0;
    virtual ~Alert() {}
};

class EmailAlert : public Alert {
private:
    string to;

public:
    EmailAlert(const string& to) : to(to) {}

    string channel() const override {
        return "email";
    }

    string render(const string& message) const override {
        return "EMAIL to " + to + ": " + message;
    }
};

class SmsAlert : public Alert {
private:
    string phone;

public:
    SmsAlert(const string& phone) : phone(phone) {}

    string channel() const override {
        return "sms";
    }

    string render(const string& message) const override {
        string text = message;
        if (text.length() > 20) {
            text = text.substr(0, 20);
        }
        return "SMS to " + phone + ": " + text;
    }
};

class PushAlert : public Alert {
private:
    string device;

public:
    PushAlert(const string& device) : device(device) {}

    string channel() const override {
        return "push";
    }

    string render(const string& message) const override {
        string upper = message;
        transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return "PUSH to " + device + ": " + upper;
    }
};

class NotificationCenter {
private:
    vector<Alert*> channels;

public:
    NotificationCenter() {}

    ~NotificationCenter() {
        for (Alert* a : channels) {
            delete a;
        }
    }

    int addEmail(string to) {
        channels.push_back(new EmailAlert(to));
        return channels.size() - 1;
    }

    int addSms(string phone) {
        channels.push_back(new SmsAlert(phone));
        return channels.size() - 1;
    }

    int addPush(string device) {
        channels.push_back(new PushAlert(device));
        return channels.size() - 1;
    }

    int count() const {
        return channels.size();
    }

    string channelOf(int index) const {
        if (index < 0 || index >= (int)channels.size()) {
            return "UNKNOWN";
        }
        return channels[index]->channel();
    }

    string send(int index, string message) const {
        if (index < 0 || index >= (int)channels.size()) {
            return "UNKNOWN";
        }
        return channels[index]->render(message);
    }

    vector<string> sendAll(string message) const {
        vector<string> result;
        for (Alert* a : channels) {
            result.push_back(a->render(message));
        }
        return result;
    }
};

// Runner
int main() {
    NotificationCenter nc;

    nc.addEmail("alice@example.com");
    nc.addSms("+123456789");
    nc.addPush("device-01");

    cout << nc.channelOf(0) << endl; // email
    cout << nc.channelOf(1) << endl; // sms
    cout << nc.channelOf(2) << endl; // push

    cout << nc.send(0, "Hello World") << endl;
    cout << nc.send(1, "This message is definitely longer than twenty characters") << endl;
    cout << nc.send(2, "Hello World") << endl;

    vector<string> all = nc.sendAll("Welcome User");

    for (const string& s : all) {
        cout << s << endl;
    }

    return 0;
}

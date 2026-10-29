#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class User {
private:
    string name_;
    vector<User*> following_;
    vector<User*> followers_;

public:
    explicit User(const string& name)
        : name_(name) {}

    string name() const {
        return name_;
    }

    vector<User*> following() const {
        return following_;
    }

    vector<User*> followers() const {
        return followers_;
    }

    bool startFollowing(User* target) {
        if (target == nullptr || target == this) {
            return false;
        }

        // Already following?
        if (find(following_.begin(), following_.end(), target) != following_.end()) {
            return false;
        }

        following_.push_back(target);
        target->followers_.push_back(this);

        return true;
    }

    bool stopFollowing(User* target) {
        if (target == nullptr) {
            return false;
        }

        auto it = find(following_.begin(), following_.end(), target);

        if (it == following_.end()) {
            return false;
        }

        following_.erase(it);

        auto followerIt =
            find(target->followers_.begin(),
                 target->followers_.end(),
                 this);

        if (followerIt != target->followers_.end()) {
            target->followers_.erase(followerIt);
        }

        return true;
    }
};
//s of User references. Expose name(), following(), followers(),
// startFollowing(), and stopFollowing(). Keep both collections consistent.
//
// FollowGraph is provided. Do not modify it.

class FollowGraph {
private:
    vector<unique_ptr<User>> users;

    User* find(const string& name) {
        for (const auto& user : users) {
            if (user->name() == name) {
                return user.get();
            }
        }
        return nullptr;
    }

    static vector<string> names(const vector<User*>& users) {
        vector<string> names;
        names.reserve(users.size());
        for (const User* user : users) {
            names.push_back(user->name());
        }
        return names;
    }

public:
    FollowGraph() = default;

    bool addUser(const string& name) {
        if (find(name) != nullptr) {
            return false;
        }
        users.push_back(make_unique<User>(name));
        return true;
    }

    bool follow(const string& followerName, const string& targetName) {
        User* follower = find(followerName);
        User* target = find(targetName);
        if (follower == nullptr || target == nullptr || follower == target) {
            return false;
        }
        return follower->startFollowing(target);
    }

    bool unfollow(const string& followerName, const string& targetName) {
        User* follower = find(followerName);
        User* target = find(targetName);
        if (follower == nullptr || target == nullptr) {
            return false;
        }
        return follower->stopFollowing(target);
    }

    vector<string> following(const string& name) {
        User* user = find(name);
        return user == nullptr ? vector<string>{} : names(user->following());
    }

    vector<string> followers(const string& name) {
        User* user = find(name);
        return user == nullptr ? vector<string>{} : names(user->followers());
    }

    bool isFollowing(const string& followerName, const string& targetName) {
        User* follower = find(followerName);
        User* target = find(targetName);
        if (follower == nullptr || target == nullptr) {
            return false;
        }
        for (const User* user : follower->following()) {
            if (user == target) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    FollowGraph obj;

    obj.addUser("Vishal");
    obj.addUser("Rahul");

    obj.follow("Vishal", "Rahul");

    cout << obj.isFollowing("Vishal", "Rahul") << endl; // 1

    obj.unfollow("Vishal", "Rahul");

    cout << obj.isFollowing("Vishal", "Rahul") << endl; // 0

    return 0;
}

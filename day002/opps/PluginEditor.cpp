#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_set>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <cctype>

// ============================================================
// The shared plugin contract
// ============================================================
class Plugin {
public:
    virtual ~Plugin() = default;
    virtual std::string getName() const = 0;
    virtual std::string transform(const std::string& text) const = 0;
};

// ============================================================
// Concrete plugin 1: Converts text to uppercase
// ============================================================
class UppercasePlugin : public Plugin {
public:
    std::string getName() const override { return "uppercase"; }
    std::string transform(const std::string& text) const override {
        std::string result = text;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        return result;
    }
};

// ============================================================
// Concrete plugin 2: Reverses the text
// ============================================================
class ReversePlugin : public Plugin {
public:
    std::string getName() const override { return "reverse"; }
    std::string transform(const std::string& text) const override {
        return std::string(text.rbegin(), text.rend());
    }
};

// ============================================================
// Concrete plugin 3: Removes all whitespace
// ============================================================
class NoSpacePlugin : public Plugin {
public:
    std::string getName() const override { return "nospace"; }
    std::string transform(const std::string& text) const override {
        std::string result;
        result.reserve(text.size());
        for (char c : text) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                result += c;
            }
        }
        return result;
    }
};

// ============================================================
// The editor that manages plugins
// ============================================================
class PluginEditor {
public:
    PluginEditor() = default;

    // Install a known plugin by name.
    // Returns true on success; false if unknown or already installed.
    bool install(const std::string& name) {
        auto it = knownPlugins().find(name);
        if (it == knownPlugins().end()) return false;   // unknown
        if (installedNames_.count(name)) return false;  // already installed

        plugins_.push_back(it->second());               // create new instance
        installedNames_.insert(name);
        return true;
    }

    // Installed plugin names in installation order.
    std::vector<std::string> installed() const {
        std::vector<std::string> names;
        names.reserve(plugins_.size());
        for (const auto& p : plugins_) {
            names.push_back(p->getName());
        }
        return names;
    }

    // Number of installed plugins.
    int pluginCount() const {
        return static_cast<int>(plugins_.size());
    }

    // Run all installed plugins on the given text, in installation order.
    std::string run(const std::string& text) const {
        std::string result = text;
        for (const auto& p : plugins_) {
            result = p->transform(result);
        }
        return result;
    }

private:
    // Factory of known plugins (by name).
    // std::function lets us store a callable that creates a fresh plugin.
    using Factory = std::function<std::unique_ptr<Plugin>()>;

    static const std::unordered_map<std::string, Factory>& knownPlugins() {
        static const std::unordered_map<std::string, Factory> registry = {
            { "uppercase", []() { return std::make_unique<UppercasePlugin>(); } },
            { "reverse",   []() { return std::make_unique<ReversePlugin>();   } },
            { "nospace",   []() { return std::make_unique<NoSpacePlugin>();   } },
        };
        return registry;
    }

    std::vector<std::unique_ptr<Plugin>> plugins_;   // preserves order
    std::unordered_set<std::string> installedNames_; // fast duplicate check
};

// ============================================================
// Demo
// ============================================================
int main() {
    PluginEditor editor;
    std::cout << "pluginCount: " << editor.pluginCount() << "\n";  // 0

    std::cout << std::boolalpha;
    std::cout << "install(uppercase): " << editor.install("uppercase") << "\n"; // true
    std::cout << "install(reverse):   " << editor.install("reverse")   << "\n"; // true
    std::cout << "install(uppercase): " << editor.install("uppercase") << "\n"; // false
    std::cout << "install(bogus):     " << editor.install("bogus")     << "\n"; // false

    std::cout << "installed: ";
    for (const auto& n : editor.installed()) std::cout << n << " ";
    std::cout << "\n";  // uppercase reverse

    std::cout << "pluginCount: " << editor.pluginCount() << "\n";  // 2
    std::cout << "run(\"Hello World\"): "
              << editor.run("Hello World") << "\n";                // DLROW OLLEH
    return 0;
}
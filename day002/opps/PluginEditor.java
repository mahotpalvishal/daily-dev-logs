/**
 * 
 *  Design the plugin system used by a PluginEditor class. Every plugin follows the same contract: it has a name and knows how to transform a piece of text. 
 * The editor can therefore run any installed plugin without knowing its concrete type or implementation.

 The PluginEditor class is provided. Complete the shared plugin contract and the three concrete plugin types so the editor behaves as follows:
 
 PluginEditor() creates an editor with no installed plugins.
 boolean install(String name) installs a known plugin and returns true. If the name is unknown or the plugin is already installed, leave the editor unchanged 
 and return false.
 String[] installed() returns the installed plugin names in installation order.
 int pluginCount() returns the number of installed plugins.
 String run(String text) passes the text through every installed plugin in order. Each plugin receives the previous plugin's output, and the final transformed 
 text is returned. With no plugins installed, return the original text unchanged.
 Implement these plugins:
 
 UpperPlugin reports the name "upper" and converts text to uppercase.
 TrimPlugin reports the name "trim" and removes leading and trailing spaces.
 ExclaimPlugin reports the name "exclaim" and appends !.
 Installation order matters because transformations are chained. For example, running trim and then exclaim on " b " produces "b!", while running exclaim and 
 then trim produces "b !".
 
 Adding another plugin later may require registering it with the editor's factory, but it must not require changing run. Read the supplied class to see the 
 exact interface, abstract class, or method names expected in your language.
 */

import java.util.*;

public class PluginEditor {
    // Preserves installation order
    private final List<Plugin> plugins = new ArrayList<>();
    // Quick lookup to avoid duplicates by name
    private final Set<String> installedNames = new HashSet<>();
    
    // Factory of known plugins (by name)
    private static final Map<String, java.util.function.Supplier<Plugin>> KNOWN = new LinkedHashMap<>();
    static {
        KNOWN.put("uppercase", UppercasePlugin::new);
        KNOWN.put("reverse",   ReversePlugin::new);
        KNOWN.put("nospace",   NoSpacePlugin::new);
    }
    
    public PluginEditor() {
        // no plugins installed initially
    }
    
    /**
     * Installs a known plugin by name.
     * @return true if installed; false if unknown or already installed.
     */
    public boolean install(String name) {
        if (name == null) return false;
        if (!KNOWN.containsKey(name)) return false;          // unknown
        if (installedNames.contains(name)) return false;      // already installed
        
        Plugin p = KNOWN.get(name).get();
        plugins.add(p);
        installedNames.add(name);
        return true;
    }
    
    /**
     * @return installed plugin names in installation order.
     */
    public String[] installed() {
        String[] result = new String[plugins.size()];
        for (int i = 0; i < plugins.size(); i++) {
            result[i] = plugins.get(i).getName();
        }
        return result;
    }
    
    /**
     * @return number of installed plugins.
     */
    public int pluginCount() {
        return plugins.size();
    }
    
    /**
     * Runs all installed plugins on the given text, in installation order.
     * Each plugin's output feeds the next plugin's input.
     */
    public String run(String text) {
        String result = text;
        for (Plugin p : plugins) {
            result = p.transform(result);
        }
        return result;
    }

    public static void main(String[] args){
        PluginEditor editor = new PluginEditor();
        System.out.println(editor.pluginCount());     // 0
        System.out.println(editor.install("uppercase")); // true
        System.out.println(editor.install("reverse"));   // true
        System.out.println(editor.install("uppercase")); // false (already installed)
        System.out.println(editor.install("bogus"));     // false (unknown)

        System.out.println(Arrays.toString(editor.installed())); // [uppercase, reverse]
        System.out.println(editor.pluginCount());     // 2
        System.out.println(editor.run("Hello World")); // "DLROW OLLEH"
    }
}

// The shared plugin contract
interface Plugin {
    String getName();
    String transform(String text);
}

// Concrete plugin 1: Converts text to uppercase
class UppercasePlugin implements Plugin {
    @Override
    public String getName() {
        return "uppercase";
    }
    
    @Override
    public String transform(String text) {
        return text == null ? null : text.toUpperCase();
    }
}

// Concrete plugin 2: Reverses the text
class ReversePlugin implements Plugin {
    @Override
    public String getName() {
        return "reverse";
    }
    
    @Override
    public String transform(String text) {
        if (text == null) return null;
        return new StringBuilder(text).reverse().toString();
    }
}

// Concrete plugin 3: Removes all whitespace
class NoSpacePlugin implements Plugin {
    @Override
    public String getName() {
        return "nospace";
    }
    
    @Override
    public String transform(String text) {
        return text == null ? null : text.replaceAll("\\s+", "");
    }
}

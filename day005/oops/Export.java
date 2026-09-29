import java.util.ArrayList;
import java.util.List;

// Abstract class
abstract class ExportFormat {

    // Template Method
    public final String exportEvents(List<String> events) {
        if (events.isEmpty()) {
            return "INVALID";
        }
        return render(events);
    }

    protected abstract String render(List<String> events);
}

// CSV Format
class CsvFormat extends ExportFormat {

    @Override
    protected String render(List<String> events) {
        return String.join(",", events);
    }
}

// Summary Format
class SummaryFormat extends ExportFormat {

    @Override
    protected String render(List<String> events) {
        return events.size() + " events: "
                + String.join(" | ", events);
    }
}

// JSON Format
class JsonFormat extends ExportFormat {

    @Override
    protected String render(List<String> events) {
        StringBuilder sb = new StringBuilder("[");

        for (int i = 0; i < events.size(); i++) {
            if (i > 0) {
                sb.append(",");
            }
            sb.append("\"").append(events.get(i)).append("\"");
        }

        sb.append("]");
        return sb.toString();
    }
}

public class Main {
    public static void main(String[] args) {

        List<String> events = new ArrayList<>();
        events.add("signup");
        events.add("login");

        ExportFormat csv = new CsvFormat();
        ExportFormat summary = new SummaryFormat();
        ExportFormat json = new JsonFormat();

        System.out.println("CSV:");
        System.out.println(csv.exportEvents(events));
        // signup,login

        System.out.println("\nSUMMARY:");
        System.out.println(summary.exportEvents(events));
        // 2 events: signup | login

        System.out.println("\nJSON:");
        System.out.println(json.exportEvents(events));
        // ["signup","login"]

        List<String> emptyEvents = new ArrayList<>();

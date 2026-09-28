import java.util.ArrayList;
import java.util.List;

abstract class Alert {
    public abstract String channel();
    public abstract String render(String message);
}

class EmailAlert extends Alert {
    private String to;

    public EmailAlert(String to) {
        this.to = to;
    }

    @Override
    public String channel() {
        return "email";
    }

    @Override
    public String render(String message) {
        return "EMAIL to " + to + ": " + message;
    }
}

class SmsAlert extends Alert {
    private String phone;

    public SmsAlert(String phone) {
        this.phone = phone;
    }

    @Override
    public String channel() {
        return "sms";
    }

    @Override
    public String render(String message) {
        String text = message;
        if (text.length() > 20) {
            text = text.substring(0, 20);
        }
        return "SMS to " + phone + ": " + text;
    }
}

class PushAlert extends Alert {
    private String device;

    public PushAlert(String device) {
        this.device = device;
    }

    @Override
    public String channel() {
        return "push";
    }

    @Override
    public String render(String message) {
        return "PUSH to " + device + ": " + message.toUpperCase();
    }
}

class NotificationCenter {
    private List<Alert> channels;

    public NotificationCenter() {
        channels = new ArrayList<>();
    }

    public int addEmail(String to) {
        channels.add(new EmailAlert(to));
        return channels.size() - 1;
    }

    public int addSms(String phone) {
        channels.add(new SmsAlert(phone));
        return channels.size() - 1;
    }

    public int addPush(String device) {
        channels.add(new PushAlert(device));
        return channels.size() - 1;
    }

    public int count() {
        return channels.size();
    }

    public String channelOf(int index) {
        if (index < 0 || index >= channels.size()) {
            return "UNKNOWN";
        }
        return channels.get(index).channel();
    }

    public String send(int index, String message) {
        if (index < 0 || index >= channels.size()) {
            return "UNKNOWN";
        }
        return channels.get(index).render(message);
    }

    public String[] sendAll(String message) {
        String[] result = new String[channels.size()];

        for (int i = 0; i < channels.size(); i++) {
            result[i] = channels.get(i).render(message);
        }

        return result;
    }
}

public class Main {
    public static void main(String[] args) {
        NotificationCenter center = new NotificationCenter();

        center.addEmail("alice@example.com");
        center.addSms("9876543210");
        center.addPush("device01");

        System.out.println(center.channelOf(0));
        System.out.println(center.channelOf(1));
        System.out.println(center.channelOf(2));

        System.out.println(center.send(0, "Hello World"));
        System.out.println(center.send(1,
                "This message is definitely longer than twenty characters"));
        System.out.println(center.send(2, "Hello World"));

        String[] all = center.sendAll("Welcome User");
        for (String s : all) {
            System.out.println(s);
        }
    }
}

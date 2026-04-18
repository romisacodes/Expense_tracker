import java.io.*;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class MonthlyReminder {
    public static void main(String[] args) {

        int dailyCount = 0;
        int reminderCount = 0;

        File file = new File("expenses.txt");

        if (!file.exists()) {
            System.out.println("No data yet.");
            return;
        }

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;

            while ((line = br.readLine()) != null) {
                line = line.trim();

                if (line.isEmpty()) continue;

                // Count daily entries
                if (line.matches("\\d+,.*")) {
                    dailyCount++;
                }

                // Count reminders
                if (line.startsWith("REMINDER")) {
                    reminderCount++;
                }
            }

        } catch (IOException e) {
            System.out.println("Error reading file.");
            return;
        }

        int daysLeft = 30 - (dailyCount % 30);
        if (daysLeft == 30) daysLeft = 0; // exactly month end

        LocalDate today = LocalDate.now();
        LocalDate reminderDate = today.plusDays(daysLeft);

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");

        // ---- Trigger Reminder ----
        if (dailyCount > 0 && dailyCount % 30 == 0 && reminderCount < (dailyCount / 30)) {
            try (FileWriter fw = new FileWriter("expenses.txt", true)) {
                fw.write("REMINDER: Month ending!\n");
                System.out.println("🔔 Reminder added! Month completed (" + dailyCount + " days).");
                System.out.println("👉 Please run C program to enter monthly expense.");
            } catch (IOException e) {
                System.out.println("Error writing reminder.");
            }
        } 
        
        // ---- Status Message ----
        else {
            System.out.println("📊 Progress Update:");
            System.out.println("Days recorded: " + dailyCount);
            System.out.println("Days left for next reminder: " + daysLeft);
            System.out.println("Expected reminder date: " + reminderDate.format(formatter));

            if (daysLeft > 0) {
                System.out.println("💡 Keep tracking your expenses. You're on track!");
            } else {
                System.out.println("⚠️ Month boundary reached, but reminder already handled.");
            }
        }
    }
}
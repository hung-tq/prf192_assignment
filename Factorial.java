import java.util.Scanner;
import java.time.LocalDate;
import java.time.Period;

public class Factorial {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.print("Enter your year of birth:");
            int birthYear = scanner.nextInt();

            LocalDate birthDate = LocalDate.of(birthYear, 1, 1);
            LocalDate currentDate = LocalDate.now();

            Period age = Period.between(birthDate, currentDate);

            System.out.println("Your age is " + age.getYears());
        }
        System.out.println("Goodbye!");
    }
}

// 

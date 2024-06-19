import java.security.*;
import java.util.Scanner;

public class Pg9_SHA512 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the message to be hashed: ");
        String text = sc.nextLine();
        sc.close();

        try {
            MessageDigest md = MessageDigest.getInstance("SHA-512");

            byte[] hashBytes = md.digest(text.getBytes());

            StringBuilder hexString = new StringBuilder();
            for (byte b : hashBytes) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }

            System.out.println("SHA-512 Hash: " + hexString);
        } catch (NoSuchAlgorithmException  e) {
            e.printStackTrace();
        }
    }
}
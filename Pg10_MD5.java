import java.security.*;
import java.util.Scanner;

public class Pg10_MD5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the message to be hashed: ");
        String text = sc.nextLine();
        sc.close();
        
        try {
            MessageDigest md = MessageDigest.getInstance("MD5");
            
            byte[] hashBytes = md.digest(text.getBytes());
            
            StringBuilder hexString = new StringBuilder();
            for (byte b : hashBytes) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            
            System.out.println("MD5 Hash: " + hexString);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }
}
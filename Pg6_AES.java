import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import java.util.*;

public class Pg6_AES {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter a 16-character key for AES encryption:");
        String keyStr = scanner.nextLine();

        // Check if the key is 16 characters
        if (keyStr.length() != 16) {
            System.out.println("Key must be 16 characters long.");
            scanner.close();
            return;
        }

        try {
            // Convert the key string to bytes
            byte[] key = keyStr.getBytes("UTF-8");

            // Create AES Key
            SecretKeySpec secretKey = new SecretKeySpec(key, "AES");

            // Create Cipher instance
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");

            // Get input message from user
            System.out.println("Enter message to encrypt:");
            String message = scanner.nextLine();

            // Encryption
            cipher.init(Cipher.ENCRYPT_MODE, secretKey);
            byte[] encryptedBytes = cipher.doFinal(message.getBytes("UTF-8"));
            String encryptedMessage = Base64.getEncoder().encodeToString(encryptedBytes);
            System.out.println("Encrypted message: " + encryptedMessage);

            // Decryption
            cipher.init(Cipher.DECRYPT_MODE, secretKey);
            byte[] decryptedBytes = cipher.doFinal(Base64.getDecoder().decode(encryptedMessage));
            String decryptedMessage = new String(decryptedBytes, "UTF-8");
            System.out.println("Decrypted message: " + decryptedMessage);

        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
}

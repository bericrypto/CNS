import java.math.BigInteger;
import java.util.Scanner;

public class Pg7_RSA {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read input values from the user
        System.out.println("Enter the message to be encrypted:");
        BigInteger msg = scanner.nextBigInteger();

        System.out.println("Enter the first prime number (p):");
        BigInteger p = scanner.nextBigInteger();

        System.out.println("Enter the second prime number (q):");
        BigInteger q = scanner.nextBigInteger();

        // Calculate n and phi
        BigInteger n = p.multiply(q);
        BigInteger phi = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));

        // Ensure the message is smaller than n
        if (msg.compareTo(n) >= 0) {
            System.out.println("The message must be smaller than n (p * q).");
            scanner.close();
            return;
        }

        System.out.println("The value of phi (φ) = " + phi);

        // Calculate e
        BigInteger e = calculateE(phi);
        System.out.println("The value of e = " + e);

        // Calculate d
        BigInteger d = e.modInverse(phi);
        System.out.println("The value of d = " + d);

        // Encrypt the message
        BigInteger encryptedMessage = msg.modPow(e, n);
        System.out.println("Encrypted message is: " + encryptedMessage);

        // Decrypt the message
        BigInteger decryptedMessage = encryptedMessage.modPow(d, n);
        System.out.println("Decrypted message is: " + decryptedMessage);

        scanner.close();
    }

    // Function to calculate the greatest common divisor (GCD)
    static BigInteger gcd(BigInteger a, BigInteger b) {
        if (a.equals(BigInteger.ZERO))
            return b;
        return gcd(b.mod(a), a);
    }

    // Function to calculate e (public key)
    static BigInteger calculateE(BigInteger phi) {
        BigInteger e = BigInteger.valueOf(2);
        while (e.compareTo(phi) < 0) {
            if (gcd(e, phi).equals(BigInteger.ONE)) {
                break;
            }
            e = e.add(BigInteger.ONE);
        }
        return e;
    }
}

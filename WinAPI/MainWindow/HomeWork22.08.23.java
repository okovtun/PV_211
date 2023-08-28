import java.util.Scanner;
//
public class Main {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        System.out.print("Введите размер фигуры: ");
        int n = kb.nextInt();
        // Шахматная доска из звездочек
        /*for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                System.out.print("* ");
            for(int j = 0; j < (n - 1)*2; j++)
                System.out.print(" ");
            for (int j = 0; j < n; j++)
            System.out.print("* ");
            for (int j = 0; j < (n - 1)*2; j++)
                System.out.print(" ");
            for(int j = 0; j < n; j++)
                System.out.print("* ");
            System.out.println();
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= (n - 1)*2; j++)
                System.out.print(" ");
            for(int j = 0; j < n; j++)
                System.out.print("* ");
            for (int j = 0; j < (n - 1)*2; j++)
                System.out.print(" ");
            for (int j = 0; j < n; j++)
                System.out.print("* ");
            System.out.println();
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                System.out.print("* ");
            for(int j = 0; j < (n - 1)*2; j++)
                System.out.print(" ");
            for (int j = 0; j < n; j++)
                System.out.print("* ");
            for (int j = 0; j < (n - 1)*2; j++)
                System.out.print(" ");
            for(int j = 0; j < n; j++)
                System.out.print("* ");
            System.out.println();
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= (n - 1)*2; j++)
                System.out.print(" ");
            for(int j = 0; j < n; j++)
                System.out.print("* ");
            for (int j = 0; j < (n - 1)*2; j++)
                System.out.print(" ");
            for (int j = 0; j < n; j++)
                System.out.print("* ");
            System.out.println();
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                System.out.print("* ");
            for(int j = 0; j < (n - 1)*2; j++)
                System.out.print(" ");
            for (int j = 0; j < n; j++)
                System.out.print("* ");
            for (int j = 0; j < (n - 1)*2; j++)
                System.out.print(" ");
            for(int j = 0; j < n; j++)
                System.out.print("* ");
            System.out.println();
        }*/

        // Треугольник паскаля
        /*for (int i = 0; i < n; i++)
        {
            int number  = 1;
            System.out.printf("%"+(n - i)*2+"s","");
            for (int j = 0; j <= i; j++) {
                System.out.printf("%4d", number);
                number=number * (i - j) / (j + 1);
            }
            System.out.println();
        }*/
    }
}



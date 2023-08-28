import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Введите размер фигуры:");
        if (scanner.hasNextInt()){
            int num = scanner.nextInt();//Вводим размерность фигуры
            for (int str = 1; str <= 5; str++){
                if (str % 2 != 0){
                    for(int i = 0; i < num; i++){
                        for (int j = 0; j < 5; j++){
                            if (j % 2 == 0) {
                                for(int b = 0; b < num; b++) {
                                    System.out.print("* ");
                                }
                            }
                            else {
                                for (int b1 = 0; b1 < num; b1++){
                                    System.out.print("  ");
                                }
                            }
                        }
                        System.out.println();
                    }
                }
                else {
                    for(int i = 0; i < num; i++){
                        for (int j = 0; j < 5; j++){
                            if (j % 2 != 0) {
                                for(int b = 0; b < num; b++) {
                                    System.out.print("* ");
                                }
                            }
                            else {
                                for (int b1 = 0; b1 < num; b1++){
                                    System.out.print("  ");
                                }
                            }
                        }
                        System.out.println();
                    }
                }
            }
        }
        else {
            System.out.println("Не число");
        }
    }
}
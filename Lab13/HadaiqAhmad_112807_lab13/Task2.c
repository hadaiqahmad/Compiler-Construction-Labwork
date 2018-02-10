package task2;

public class Sum {
    public static double sum(double[] array) {
        double total = 0.0;
        for (int i = 0; i < array.length; i++) {
            total += array[i];
        }
        return total;
    }

    public static void main(String[] args) {
        double[] array = new double[10000];
        for (int i = 0; i < array.length; i++) {
            array[i] = (double)i;
        }

        System.out.println("Dead code:");
        for (int i = 0; i < 5; i++) {
            double grand_total = 0.0;
            long start = System.currentTimeMillis();
            for (int j = 0; j < 10000; j++) {
                sum(array);
                grand_total += 1.0;
            }
            long stop = System.currentTimeMillis();
            System.out.println("Computed " + grand_total +
                               " in " + (stop - start) + " msecs");
        }

        System.out.println("\nLive code:");
        for (int i = 0; i < 5; i++) {
            double grand_total = 0.0;
            long start = System.currentTimeMillis();
            for (int j = 0; j < 10000; j++) {
                grand_total += sum(array);
            }
            long stop = System.currentTimeMillis();
            System.out.println("Computed " + grand_total +
                               " in " + (stop - start) + " msecs");
        }
    }
}
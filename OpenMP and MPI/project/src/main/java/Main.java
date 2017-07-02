import com.sun.jna.Native;

public class Main {
    public static void main(String[] args) {

        MyLib myLib = (MyLib) Native.loadLibrary("course", MyLib.class);
//        int seconds = myLib.start();

        //myLib._Z6start2v();
        //int[] b = {2, 3, 4, 1, 5};
        int[] a = {5, 7, 3, 2, 8, 0, 1, 3, 4, 9};
        //System.out.println(myLib._Z5startPii(b, 5));

        myLib._Z5startPii(a, 10);
         //myLib._Z6startxv();

    }
}

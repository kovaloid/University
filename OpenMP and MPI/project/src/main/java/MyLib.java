import com.sun.jna.Library;


public interface MyLib extends Library {
    void Matr(int[][] A, int n);
    //int _Z6startxv();
    int _Z5startPii(int[] A, int n);
    int main();
}

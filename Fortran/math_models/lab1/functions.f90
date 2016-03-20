!процедура метода прогонки
SUBROUTINE PROGON(N, A, B, C, G, X)

    INTEGER N
    REAL A(0:N), B(0:N), C(0:N), G(0:N), X(0:N)
    REAL Al(0:N), Bt(0:N)

    !прямой метод прогонки
    !вычисление начальных коэфф
    Al(0)=-(B(0)/C(0))
    Bt(0)=(G(0)/C(0))
    !вычисление остальных коэфф
    DO i=1,N-1
        Al(i)=( -B(i) )/( A(i)*Al(i-1)+C(i) )
        Bt(i)=(G(i)-A(i)*Bt(i-1))/(A(i)*Al(i-1)+C(i))
    END DO

    !обратный метод прогонки
    X(N)=(G(N)-A(N)*Bt(N-1))/(A(N)*Al(N-1)+C(N))
    DO i=N-1,0,-1
        X(i)=Al(i)*X(i+1)+Bt(i)
    END DO

END SUBROUTINE PROGON

!процедура создания сетки
SUBROUTINE MAKE_NETS(N, A, B, R, dh, h, h_)

    INTEGER A, B, N
    REAL R(0:80), h(0:80), h_(0:80), dh

    !сетка Ri
    dh=(REAL(B-A)/N)
    DO i=0,N
        R(i)=A+dh*i
    END DO

    !шаг основной сетки
    DO i=1,N
        h(i)=R(i)-R(i-1)
    END DO

    !шаг вспомогательной сетки
    h_(0)=h(1)/2
    DO i=1,(N-1)
        h_(i)=(h(i)+h(i+1))/2
    END DO
    h_(N)=h(N)/2

END SUBROUTINE MAKE_NETS

!процедура заполнения трехдиагональной матрицы коэфицентов
SUBROUTINE MAKE_MATRIX(N, Ak, Ck, Bk, Gk, V1, V2, R, h, h_)

    INTEGER N
    REAL K, Q, F, V1, V2
    REAL Ak(0:80), Ck(0:80), Bk(0:80), Gk(0:80)
    REAL R(0:80), h(0:80), h_(0:80)

    !Ck0,Bk0             = Gk0
    !   Ak1,Ck1,Bk1      = Gk1
    !       Ak2,Ck2,Bk2  = Gk2
    !...................
    !           AkN,CkN  = GkN
    !
    Ak(0)=0;
    Ck(0)=1.0
    Bk(0)=0.0
    Gk(0)=V1
    DO i=1,(N-1)
        Ak(i)=-(((R(i)+R(i-1))/2)**2*K(((R(i)+R(i-1))/2))/h(i))
        Bk(i)=-(((R(i)+R(i+1))/2)**2*K(((R(i)+R(i+1))/2))/h(i+1))
        Ck(i)=-Bk(i)-Ak(i)+h_(i)*R(i)**2*Q(R(i))
        Gk(i)=h_(i)*R(i)**2*F(R(i))
    END DO
    Ak(N)=0.0
    Bk(N)=0.0
    Ck(N)=1.0
    Gk(N)=V2

END SUBROUTINE MAKE_MATRIX

!процедура вычисления погрешности
SUBROUTINE FIND_ERROR(N, ER, ER_MAX, U, R)

    INTEGER N
    REAL ER_MAX, U_SOLUTION
    REAL R(0:80), U(0:80), ER(0:80)

    DO i=0,N
        ER(i)=ABS(U_SOLUTION(R(i))-U(i))
    END DO
    ER_MAX=ER(0)
    DO i=1,N
        IF(ER(i).GT.ER_MAX) ER_MAX=ER(i)
    END DO

END SUBROUTINE FIND_ERROR

!процедура вывода результатов
SUBROUTINE OUTPUT(N, R, U, ER, ER_MAX)

    INTEGER N
    REAL ER_MAX, U_SOLUTION
    REAL U(0:80), ER(0:80), R(0:80)

    DO i=0,N
        PRINT *,i,"r=",R(i),"u=",U_SOLUTION(R(i)),"v=",U(i),"e=",ER(i)
    END DO
    PRINT *,"max error=",ER_MAX
    PRINT *,""

END SUBROUTINE OUTPUT

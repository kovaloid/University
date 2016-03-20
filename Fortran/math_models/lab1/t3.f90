include 'functions.f90'

PROGRAM TEST_3

    INTEGER A, B, N
    REAL K, Q, F, V1, V2, ER_MAX
    REAL Ak(0:80), Ck(0:80), Bk(0:80), Gk(0:80), U(0:80)
    REAL ER(0:80), R(0:80), h(0:80), h_(0:80), dh

    !начальные значения
    V1=17
    V2=167
    A=1
    B=2
    PRINT *,"V1=",V1,"V2=",V2,"A=",A,"B=",B
    PRINT *,""

    N=10
    DO i=0,3
        PRINT *,"N=",N
        !создаем сетки
        CALL MAKE_NETS(N, A, B, R, dh, h, h_)
        !заполняем трехдиагональную матрицу коэфицентов
        CALL MAKE_MATRIX(N, Ak, Ck, Bk, Gk, V1, V2, R, h, h_)
        !решаем прогонкой
        CALL PROGON(N, Ak, Bk, Ck, Gk, U)
        !вычисляем погрешность
        CALL FIND_ERROR(N, ER, ER_MAX, U, R)
        !выводим результат работы
        CALL OUTPUT(N, R, U, ER, ER_MAX)
        N=N*2
    END DO

END PROGRAM TEST_3


!функции k(r), q(r), f(r) и точное решение u(r)
REAL FUNCTION K(R)
    REAL R
    K=7.0*R*R+8.0*R+3.0
END FUNCTION K

REAL FUNCTION Q(R)
    REAL R
    Q=4.0*R**3+6.0*R*R+5.0*R+1.0
END FUNCTION Q

REAL FUNCTION F(R)
    REAL R
    F=36.0*R**7+54.0*R**6+65.0*R**5-1725.0*R**4-1691.0*R**3-867.0*R*R-305.0*R-87.0
END FUNCTION F

REAL FUNCTION U_SOLUTION(R)
    REAL R
    U_SOLUTION=9.0*R**4+5.0*R*R+3.0
END FUNCTION U_SOLUTION

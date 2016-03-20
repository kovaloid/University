!функция для вычисления системы подпрограммой RKF45
subroutine func ( t, y, yp )
  implicit none

  integer, parameter :: neqn = 20
  real t
  real y(neqn)
  real yp(neqn)
  integer A, B, N, i
  real K, Q, F, V1, V2
  real Ak(neqn), Ck(neqn), Bk(neqn), Gk(neqn)
  real R(0:neqn+1), h(0:neqn+1), h_(0:neqn+1), dh

  !начальные значения
  A=1
  B=2
  N=neqn+1

  !создаем сетки
  call make_nets( N, A, B, R, dh, h, h_ )
  !заполняем трехдиагональную матрицу коэфицентов
  call make_matrix( N, Ak, Ck, Bk, Gk, R, h, h_, t )

  yp(1) = Ck(1) * y(1) + Bk(1) * y(2) + Gk(1)
  do i = 2, (N-2)
     yp(i) = Ak(i) * y(i-1) + Ck(i) * y(i) + Bk(i) * y(i+1) + Gk(i)
  end do
  yp(N-1) = Ak(N-1) * y(N-2) + Ck(N-1) * y(N-1) + Gk(N-1)

  return
end

!процедура создания сетки
subroutine make_nets( N, A, B, R, dh, h, h_ )

    integer A, B, N
    real R(0:N), h(0:N), h_(0:N), dh

    !сетка Ri
    dh=(REAL(B-A)/N)
    do i=0,N
        R(i)=A+dh*i
    end do

    !шаг основной сетки
    do i=1,N
        h(i)=R(i)-R(i-1)
    end do

    !шаг вспомогательной сетки
    h_(0)=h(1)/2
    do i=1,(N-1)
        h_(i)=(h(i)+h(i+1))/2
    end do
    h_(N)=h(N)/2

end

!процедура заполнения трехдиагональной матрицы коэфицентов
subroutine make_matrix( N, Ak, Ck, Bk, Gk, R, h, h_, t )

    integer N
    real t
    real K, Q, F, V1, V2
    real Ak(N-1), Ck(N-1), Bk(N-1), Gk(N-1)
    real R(0:N), h(0:N), h_(0:N)

    !Ck1,Bk1                 ; Gk1
    !   Ak2,Ck2,Bk2          ; Gk2
    !       Ak3,Ck3,Bk3      ; Gk3
    !....................... ; ....
    !           AkN-1,CkN-1  ; GkN-1
    !

    Ak(1)=0.0
    Bk(1)=((R(1)+R(2))/2)**2*K((R(1)+R(2))/2,t)/(h(2)*h_(1)*R(1)**2)
    Ck(1)=-((R(1)+R(0))/2)**2*K((R(1)+R(0))/2,t)/(h(1)*h_(1)*R(1)**2)-Bk(1)-Q(R(1),t)
    Gk(1)=F(R(1),t)+V1(t)*((R(1)+R(0))/2)**2*K((R(1)+R(0))/2,t)/(h(1)*h_(1)*R(1)**2)

    do i=2,(N-2)
        Ak(i)=((R(i)+R(i-1))/2)**2*K((R(i)+R(i-1))/2,t)/(h(i)*h_(i)*R(i)**2)
        Bk(i)=((R(i)+R(i+1))/2)**2*K((R(i)+R(i+1))/2,t)/(h(i+1)*h_(i)*R(i)**2)
        Ck(i)=-Bk(i)-Ak(i)-Q(R(i),t)
        Gk(i)=F(R(i),t)
    end do

    Ak(N-1)=((R(N-1)+R(N-2))/2)**2*K((R(N-1)+R(N-2))/2,t)/(h(N-1)*h_(N-1)*R(N-1)**2)
    Bk(N-1)=0.0
    Ck(N-1)=-Ak(N-1)-((R(N-1)+R(N))/2)**2*K((R(N-1)+R(N))/2,t)/(h(N)*h_(N-1)*R(N-1)**2)-Q(R(N-1),t)
    Gk(N-1)=F(R(N-1),t)+V2(t)*((R(N)+R(N-1))/2)**2*K((R(N)+R(N-1))/2,t)/(h(N)*h_(N-1)*R(N-1)**2)

end

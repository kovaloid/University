include 'lsode.f90'

program lsode_test_1

    integer, parameter :: N = 20
    integer, parameter :: MAX_STEPS = 10000000
    real :: t = 0.0
    real :: t_out = 12.0
    integer :: MF = 22

!     MF = METHOD FLAG.  STANDARD VALUES ARE..
!          10 FOR NONSTIFF (ADAMS) METHOD, NO JACOBIAN USED.
!          21 FOR STIFF (BDF) METHOD, USER-SUPPLIED FULL JACOBIAN.
!          22 FOR STIFF METHOD, INTERNALLY GENERATED FULL JACOBIAN.
!          24 FOR STIFF METHOD, USER-SUPPLIED BANDED JACOBIAN.
!          25 FOR STIFF METHOD, INTERNALLY GENERATED BANDED JACOBIAN.

    real r(0:N)
    real V(1:N-1)
    real er(1:N-1)
    integer, parameter :: LRW = 22+9*N+N**2
    integer, parameter :: LIW = 20+N
    integer :: IWORK(LIW) = 0
    real :: RWORK(LRW) = 0.0
    integer :: IOPT = 1
    integer :: ITASK = 1
    integer :: ISTATE = 1
    integer :: ITOL = 1
    real :: ATOL = 1E-7;
    real :: RTOL = 1E-5;
    integer i

    IWORK(6) = MAX_STEPS

    r(0)=1.0
    do i = 1, N-1
        r(i) = 1.0 + real(i)/real(N)
        V(i) = 1.0 + real(i)/real(N)
    end do
    r(N)=2.0

    call LSODE(FEX,N,V,t,t_out,ITOL,RTOL,ATOL,ITASK,ISTATE,IOPT,RWORK,LRW,IWORK,LIW,JAC,MF)
    if ( ISTATE < 0 ) then
        print *,'ERROR HALT.. ISTATE =',ISTATE
        stop
    endif

    write ( *, '(a)' ) ' '
    write ( *, '(a)' ) '  LSODE TEST 1'
    write ( *, '(a)' ) ' '
    write ( *, '(a5,i4,a10,i2,a7,f10.6,a8,i4)' ) 'N =', N, 'FLAG =', istate, 'T =', t_out, 'MF =', MF
    write ( *, '(a)' ) ' '
    write ( *, '(a)' ) '   i        u           v            e'
    write ( *, '(a)' ) ' '

    do i = 1, N-1
        er(i) = ABS(U(r(i),t_out) - V(i))
        write(*,'(i4,2f12.6,e16.6)') i, U(r(i),t_out), V(i), er(i)
    end do

    write ( *, '(a)' ) ' '
    write ( *, '(a12,i5,a18,i5,a18,i5)' ) 'NO. STEPS =',IWORK(11),' NO. F-S =',IWORK(12),' NO. J-S =',IWORK(13)
    write ( *, '(a9,e14.6)' ) 'MAXERR =',maxval(er)

CONTAINS

    subroutine FEX (N, T, V, dV)
		real t, V(1:N-1), dV(1:N-1)
        real Ak(N-1), Ck(N-1), Bk(N-1), Gk(N-1)
        integer i

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
        Ck(N-1)=-Ak(N-1)-((R(N-1)+R(N))/2)**2*K((R(N-1)+R(N))/2,t)/(h(N)*h_(N-1)*R(N-1)**2)-Q(R(N-1),t)
        Gk(N-1)=F(R(N-1),t)+V2(t)*((R(N)+R(N-1))/2)**2*K((R(N)+R(N-1))/2,t)/(h(N)*h_(N-1)*R(N-1)**2)

        dV(1) = Ck(1) * V(1) + Bk(1) * V(2) + Gk(1)
        do i = 2, (N-2)
            dV(i) = Ak(i) * V(i-1) + Ck(i) * V(i) + Bk(i) * V(i+1) + Gk(i)
        end do
        dV(N-1) = Ak(N-1) * V(N-2) + Ck(N-1) * V(N-1) + Gk(N-1)
    end

    subroutine JAC (NEQ, T, Y, ML, MU, PD, NROWPD)
        integer NEQ, ML, MU, NROWPD
        real T, Y(*), PD(NROWPD,*)
        integer i, j

        do i = 1, N
            do j = 1, N
                PD(i,j) = 0.0
            end do
        end do

        PD(1,2) = ((R(1)+R(2))/2)**2*K((R(1)+R(2))/2,t)/(h(2)*h_(1)*R(1)**2)
        PD(1,1) = -((R(1)+R(0))/2)**2*K((R(1)+R(0))/2,t)/(h(1)*h_(1)*R(1)**2)-PD(1,2)-Q(R(1),t)
        j = 2
        do i = 2, N-2
            PD(i,j-1) = ((R(i)+R(i-1))/2)**2*K((R(i)+R(i-1))/2,t)/(h(i)*h_(i)*R(i)**2)
            PD(i,j+1) = ((R(i)+R(i+1))/2)**2*K((R(i)+R(i+1))/2,t)/(h(i+1)*h_(i)*R(i)**2)
            PD(i,j) = -PD(i,j-1)-PD(i,j+1)-Q(R(i),t)
            j = j + 1
        end do
        PD(N-1,N-2) = ((R(N-1)+R(N-2))/2)**2*K((R(N-1)+R(N-2))/2,t)/(h(N-1)*h_(N-1)*R(N-1)**2)
        PD(N-1,N-1) = -PD(N-1,N-2)-((R(N-1)+R(N))/2)**2*K((R(N-1)+R(N))/2,t)/(h(N)*h_(N-1)*R(N-1)**2)-Q(R(N-1),t)
    end

    real function K(r,t)
        real r, t
        K=1.0
    end

    real function Q(r,t)
        real r, t
        Q=1.0
    end

    real function F(r,t)
        real r, t
        F=1.0
    end

    real function V1(t)
        real t
        V1=1.0
    end

    real function V2(t)
        real t
        V2=1.0
    end

    real function U(r,t)
        real r, t
        U=1.0
    end

    real function h(i)
        integer i
        h=r(i)-r(i-1)
    end

    real function h_(i)
        integer i
        if (i .EQ. 0) then
            h_=h(1)/2.0
        else if (i .EQ. N) then
            h_=h(N)/2.0
        else
            h_=(h(i)+h(i+1))/2.0
        end if
    end

end

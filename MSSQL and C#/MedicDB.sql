create table diagnosis
(
  idd int not null identity (1,1),
  name varchar (50) null,
  constraint pk_diagnosis primary key (idd)
) 
create table wards
(
  idd int not null identity (1,1),
  name varchar (50) null,
  max_cout int null,
  constraint pk_wards primary key (idd)
) 
create table peoples
(
  idd int not null identity (1,1),
  family varchar (50) null,
  name varchar (50) null,
  parentname varchar (50) null,
  diagnosis_id int null,
  wards_id int null,
  constraint pk_peoples primary key (idd),
  constraint fk_peoples_diagnosis foreign key (diagnosis_id) references diagnosis (idd),
  constraint fk_peoples_wards foreign key (wards_id) references wards (idd)
)
insert into diagnosis values ('��������')
insert into diagnosis values ('����������')
insert into diagnosis values ('�������')
insert into diagnosis values ('�������������')
 
select * from diagnosis

insert into wards values ('�������� 1', 4)
insert into wards values ('�������� 2', 2)
insert into wards values ('���������� 1', 3)
insert into wards values ('���������� 2', 2)
insert into wards values ('������� 1', 3)
insert into wards values ('������� 2', 2)
insert into wards values ('������������� 1', 1)
insert into wards values ('������������� 2', 1)
insert into wards values ('���������� 1', 6)

select * from diagnosis

select * from wards
select * from peoples 

insert into peoples values ('������','����','��������', 1, 1)
insert into peoples values ('�������','������','��������', 2, 3)
insert into peoples values ('�������','�����','���������', 3, 5)
insert into peoples values ('������','����','��������', 4, 7)
insert into peoples values ('��������','�������','����������', 1, 2)
insert into peoples values ('�������','�����','���������', 2, 4)
insert into peoples values ('�������','�����','���������', 3, 6)
insert into peoples values ('�������','������','��������', 4, 1)
insert into peoples values ('�������','��������','�������������', 2, 3)
insert into peoples values ('������','����','�����', 1, 1)
insert into peoples values ('�����','����','���������', 1, default)

select * from peoples 

--������� ������
--������������� �������
--1 ������� ��� ��������

select idd, name from diagnosis

--2 ������� ���� ������� � �������� ���������
 
select family, name, parentname from peoples where diagnosis_id=2 

--3 ������� ��� ��������, ���������� �� � ���������� ������� �� ������������

select name from diagnosis order by name 

--4 ������� ��� ������, ���������� �� � �������� ������� �� ����������� � � ������ ������� �� ������������

select max_cout, name  from wards order by max_cout desc, name asc

select count(*) from wards


--5 ������� ���� �������, � ������� ������� ����������� "?��"

select family, name, parentname from peoples where family like '%��'

--������� � ������������
--1 ������� ���� �������, ������� � ������ � �������� �������������
select * from wards
select family, name, parentname from peoples 
       where wards_id in (select idd from wards where name = '���������� 1')


select * from diagnosis
select * from peoples 
select * from wards
--2 �������  ����� ����� ��� �������� � �������� ������������
select count (*) as [number] from wards
       where idd in (
       select wards_id from peoples where diagnosis_id  = 2)


--3 ������� ����� ������� , ������� � ������ � �������� �������������

select count (*) as [number] from peoples 
       where wards_id in (select idd from wards where name =  '���������� 1')


--���������� ������
--1 ������� ������� � ������������ �����

select p.family, p.name, p.parentname, w.name from peoples as p
       inner join wards as w on wards_id = w.idd

--2 ������� ������� � ������������ �����, ������� ������, � ������� ������ ���

select p.family, p.name, p.parentname, w.name from peoples as p 
        right outer join wards as w on wards_id = w.idd

--3 ������� ������� � ������������ �����, ������� ������, 
--� ������� ������ ��� � �������, �������������� �� � ���� ������

select p.family, p.name, p.parentname, w.name from peoples as p
        full outer join wards as w on wards_id = w.idd

--4 ������� ��� ������ � ���������� ������� ������� � ���

select * from peoples
select w.name, count (*) as [number] from peoples as p 
        inner join wards as w on wards_id = w.idd group by w.name

--5 ������� ��� ��������, ���������� ������� � �����, ���������� ����� ��������

select * from wards
select * from diagnosis
select * from peoples
select d.name, count (*) as [number_peopl] from peoples
       inner join diagnosis as d 
       on diagnosis_id = d.idd group by d.name

select d.name, count (*) as [number_wards] from wards
       inner join peoples as p  
diagnosis as d
       on wards_id = d.idd group by d.name



'select count (*) as [number] from wards
       where idd in (
       select wards_id from peoples where diagnosis_id  = 2)'



select a.name, a.pacients, b.wards from 
(
select d.name, diagnosis_id, count(diagnosis_id) as pacients from diagnosis d
left join peoples p on d.idd = p.diagnosis_id
group by diagnosis_id, d.name
) as a
inner join 
(
select d.idd as diagnosis_id, count(distinct wards_id) as wards from diagnosis d
left join peoples p on d.idd = p.diagnosis_id
group by d.idd
) as b
on a.diagnosis_id = b.diagnosis_id



--5 ����� ���������� (�������������)
select d.name, count(p.idd), count(distinct w.idd)
from diagnosis d
join peoples p on d.idd = p.diagnosis_id
join wards w on p.wards_id = w.idd
group by d.name



--������� ������
-- ������������� �������
--1 �������� ����� �������

insert into diagnosis values ('�����������')

--2 �������� �������� � ��������� �� �1


--insert into peoples select '���������', '����', '����������'--, diagnosis.iid, null from (select idd from diagnosis where name =  '�����������')as diagnosis
insert into peoples 
select '���������', '����', '����������', diag.idd, null 
       from (select * from diagnosis where name = '�����������' ) as diag
--insert into peoples select '��������', '����', '����������', iid, null from diagnosis where name = '�����������' -- from diagnosis--(select idd from diagnosis where name =  '�����������')as diagnosis

select '���������', '����', '����������', idd, null 
       from diagnosis where name = '�����������'

delete from diagnosis 
       where idd=6

begin tran 

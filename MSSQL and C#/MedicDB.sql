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
insert into diagnosis values ('хирургия')
insert into diagnosis values ('невралогия')
insert into diagnosis values ('терапия')
insert into diagnosis values ('травматология')
 
select * from diagnosis

insert into wards values ('хирургия 1', 4)
insert into wards values ('хирургия 2', 2)
insert into wards values ('невралогия 1', 3)
insert into wards values ('невралогия 2', 2)
insert into wards values ('терапия 1', 3)
insert into wards values ('терапия 2', 2)
insert into wards values ('травматология 1', 1)
insert into wards values ('травматология 2', 1)
insert into wards values ('невралогия 1', 6)

select * from diagnosis

select * from wards
select * from peoples 

insert into peoples values ('Иванов','Иван','Иванович', 1, 1)
insert into peoples values ('Иванова','Регина','Ивановна', 2, 3)
insert into peoples values ('Семенов','Семен','Семенович', 3, 5)
insert into peoples values ('Петров','Петр','Петрович', 4, 7)
insert into peoples values ('Николаев','Николай','Николаевич', 1, 2)
insert into peoples values ('Сидоров','Сидор','Сидорович', 2, 4)
insert into peoples values ('Федоров','Федор','Федорович', 3, 6)
insert into peoples values ('Никитин','Никита','Иванович', 4, 1)
insert into peoples values ('Светина','Светлана','Станиславовна', 2, 3)
insert into peoples values ('Фомкин','Фома','Фомич', 1, 1)
insert into peoples values ('Фокин','Петр','Семенович', 1, default)

select * from peoples 

--выборка данных
--однотабличная выборка
--1 вывести все диагнозы

select idd, name from diagnosis

--2 вывести всех больних с заданным диагнозом
 
select family, name, parentname from peoples where diagnosis_id=2 

--3 вывести все диагнозы, упорядочив из в алфавитном порядке по наименованию

select name from diagnosis order by name 

--4 вывести все палаты, упорядочив их в обратном порядке по вместимости и в прямом порядке по наименованию

select max_cout, name  from wards order by max_cout desc, name asc

select count(*) from wards


--5 вывести всех больных, в фамилии которых встречается "?ов"

select family, name, parentname from peoples where family like '%ов'

--выборка с подзапросами
--1 вывести всех больных, лежащих в палате с заданным наименованием
select * from wards
select family, name, parentname from peoples 
       where wards_id in (select idd from wards where name = 'невралогия 1')


select * from diagnosis
select * from peoples 
select * from wards
--2 вывести  число палат для диагноза с заданным наименование
select count (*) as [number] from wards
       where idd in (
       select wards_id from peoples where diagnosis_id  = 2)


--3 вывести число больных , лежащих в палате с заданным наименованием

select count (*) as [number] from peoples 
       where wards_id in (select idd from wards where name =  'невралогия 1')


--склеивание таблиц
--1 вывести больных и наименования палат

select p.family, p.name, p.parentname, w.name from peoples as p
       inner join wards as w on wards_id = w.idd

--2 вывести больных и наименование палат, включая палаты, в которых никого нет

select p.family, p.name, p.parentname, w.name from peoples as p 
        right outer join wards as w on wards_id = w.idd

--3 вывести больних и наименование палат, включая палаты, 
--в которых никого нет и больных, неопределенных ни в одну палату

select p.family, p.name, p.parentname, w.name from peoples as p
        full outer join wards as w on wards_id = w.idd

--4 вывести все палаты и количество больных лежащих в них

select * from peoples
select w.name, count (*) as [number] from peoples as p 
        inner join wards as w on wards_id = w.idd group by w.name

--5 вывести все диагнозы, количество больных и палат, занимаемых этими больными

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



--5 часть склеивания (преподаватель)
select d.name, count(p.idd), count(distinct w.idd)
from diagnosis d
join peoples p on d.idd = p.diagnosis_id
join wards w on p.wards_id = w.idd
group by d.name



--вставка данных
-- однотабличная вставка
--1 добавить новый диагноз

insert into diagnosis values ('кардиология')

--2 добавить больного с диагнозом из п1


--insert into peoples select 'Васечькин', 'Петр', 'Васильевич'--, diagnosis.iid, null from (select idd from diagnosis where name =  'кардиология')as diagnosis
insert into peoples 
select 'Васечькин', 'Петр', 'Васильевич', diag.idd, null 
       from (select * from diagnosis where name = 'кардиология' ) as diag
--insert into peoples select 'Васичкин', 'Петр', 'Васильевич', iid, null from diagnosis where name = 'кардиология' -- from diagnosis--(select idd from diagnosis where name =  'кардиология')as diagnosis

select 'Васечькин', 'Петр', 'Васильевич', idd, null 
       from diagnosis where name = 'кардиология'

delete from diagnosis 
       where idd=6

begin tran 

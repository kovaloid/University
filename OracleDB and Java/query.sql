 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 ---   Выборка данных
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 --Hints: select, count, join, where, in, exists, order by, group by, having
 
--•	однотабличная выборка
--1.	Вывести названия всех маршрутов
SELECT NAME FROM KOVAL.ROUTES;
--2.	Вывести номера автомобилей заданного цвета
SELECT NUM FROM KOVAL.AUTO WHERE COLOR = 'синий';
--3.	Вывести ФИО персонала, упорядочив в алфавитном порядке по фамилии
SELECT LAST_NAME, FIRST_NAME, FATHER_NAME FROM KOVAL.AUTO_PERSONNEL ORDER BY LAST_NAME ASC;
--4.	Вывести ФИО персонала, упорядочив в алфавитном порядке по фамилии и в обратном порядке по имени
SELECT LAST_NAME, FIRST_NAME, FATHER_NAME FROM KOVAL.AUTO_PERSONNEL ORDER BY LAST_NAME ASC, FIRST_NAME DESC;
--5.	Вывести даты приезда из тех записей журнала оператора, дата выезда которых больше некоторой даты
SELECT TIME_IN FROM KOVAL.JOURNAL WHERE TIME_OUT > '31-MAY-14';
--6.	Вывести номера автомобилей, у которых первая буква номера «р»
SELECT NUM FROM KOVAL.AUTO WHERE NUM LIKE 'р%';
--7.	Посчитать количество автомобилей, у которых первая буква номера «р»
SELECT COUNT(*) AS P_COUNTER FROM KOVAL.AUTO WHERE NUM LIKE 'р%';

--•	выборка с подзапросами
--1.	Вывести номера автомобилей водителя с заданной фамилией
SELECT NUM FROM KOVAL.AUTO WHERE PERSONNEL_ID IN 
(SELECT ID FROM KOVAL.AUTO_PERSONNEL WHERE LAST_NAME = 'Петров');
--2.	Вывести наименования рейсов, в которых были автомобили водителя с заданной фамилией
SELECT NAME FROM KOVAL.ROUTES WHERE ID IN 
(SELECT ROUTE_ID FROM KOVAL.JOURNAL WHERE AUTO_ID IN 
(SELECT ID FROM KOVAL.AUTO WHERE PERSONNEL_ID IN 
(SELECT ID FROM KOVAL.AUTO_PERSONNEL WHERE LAST_NAME = 'Сидоров')));
--3.	Вывести наименования маршрутов, на которых есть не вернувшиеся автомобили
SELECT NAME FROM KOVAL.ROUTES WHERE ID IN 
(SELECT ROUTE_ID FROM KOVAL.JOURNAL WHERE TIME_IN IS NULL);

--•	склеивание таблиц (join)
--1.	Вывеси наименования маршрутов и даты отправки/возвращения из журнала оператора
SELECT ROUTES.NAME, JOURNAL.TIME_OUT, JOURNAL.TIME_IN FROM KOVAL.JOURNAL JOIN KOVAL.ROUTES ON JOURNAL.ROUTE_ID = ROUTES.ID;
--2.	Вывести время отправки из журнала оператора и наименования маршрутов, включая маршруты, по которым рейсов не было
SELECT JOURNAL.TIME_OUT, ROUTES.NAME FROM KOVAL.JOURNAL RIGHT JOIN KOVAL.ROUTES ON JOURNAL.ROUTE_ID = ROUTES.ID;
--3.	Вывести времена отправки/прибытия из журнала оператора, наименования маршрутов поездок, включая маршруты, по которым не было рейсов, и номера автомобилей, включая автомобили которые не участвовали в рейсах.
SELECT JOURNAL.TIME_OUT, JOURNAL.TIME_IN, ROUTES.NAME, AUTO.NUM
FROM KOVAL.JOURNAL 
FULL JOIN KOVAL.ROUTES ON JOURNAL.ROUTE_ID = ROUTES.ID
FULL JOIN KOVAL.AUTO ON JOURNAL.AUTO_ID = AUTO.ID
ORDER BY NAME, NUM;

--•	для реализации проекта
--1.	Вывести самое короткое время проезда по заданному наименованием маршруту и номер автомобиля, который поставил рекорд.
SELECT NUM, (TIME_IN-TIME_OUT) AS DELTA FROM KOVAL.JOURNAL JOIN KOVAL.AUTO ON JOURNAL.AUTO_ID = AUTO.ID
JOIN KOVAL.ROUTES ON JOURNAL.ROUTE_ID = ROUTES.ID 
WHERE (TIME_IN-TIME_OUT) = (SELECT MIN(TIME_IN-TIME_OUT) FROM KOVAL.JOURNAL) AND
NAME = 'Петергофский';

--2.	Количество автомобилей находящихся в рейсе по заданному наименованием маршруту
SELECT COUNT(AUTO_ID) FROM KOVAL.JOURNAL JOIN KOVAL.ROUTES ON JOURNAL.ROUTE_ID = ROUTES.ID
WHERE NAME = 'Выборгский' AND TIME_IN IS NULL;

 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 ---   Вставка данных
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 --Hints: insert, where, in, exists, commit, rollback
 
--•	однотабличная вставка
--1.	Добавить нового водителя
INSERT INTO KOVAL.AUTO_PERSONNEL (FIRST_NAME, LAST_NAME, FATHER_NAME) VALUES ('Иван','Иванов','Иванович');

--2.	Добавить водителю с заданной фамилией два автомобиля
INSERT INTO KOVAL.AUTO (NUM, COLOR, MARK, PERSONNEL_ID) VALUES ('у567о','зеленый','Форд',(
    SELECT ID FROM KOVAL.AUTO_PERSONNEL WHERE LAST_NAME = 'Петров'));
INSERT INTO KOVAL.AUTO (NUM, COLOR, MARK, PERSONNEL_ID) VALUES ('в767т','красный','Мерседес',(
    SELECT ID FROM KOVAL.AUTO_PERSONNEL WHERE LAST_NAME = 'Петров'));

--3.	Отправить водителя с заданной фамилией на желтой машине в рейс по маршруту с известным id.
INSERT INTO KOVAL.JOURNAL (TIME_OUT, AUTO_ID, ROUTE_ID) VALUES ('31-MAY-14 10.30.00.000000000 AM',(
    SELECT AUTO.ID FROM KOVAL.AUTO INNER JOIN KOVAL.AUTO_PERSONNEL ON AUTO.PERSONNEL_ID = AUTO_PERSONNEL.ID 
        WHERE(AUTO.COLOR LIKE 'желтый' AND AUTO_PERSONNEL.LAST_NAME = 'Петров')),'3');

--•	многотабличная вставка в рамках транзакции
--1.	Добавить в рамках транзакции водителя, автомобиль и запись в журнал оператора об отъезде в какой-либо рейс
BEGIN
INSERT INTO KOVAL.AUTO_PERSONNEL (FIRST_NAME,LAST_NAME,FATHER_NAME) VALUES ('Боромир', 'Петров', 'Эдуардович');
INSERT INTO KOVAL.AUTO (NUM,COLOR,MARK,PERSONNEL_ID) VALUES ('H843TO','Black','Mercedes',(SELECT ID FROM (SELECT * FROM KOVAL.AUTO_PERSONNEL ORDER BY AUTO_PERSONNEL.ID DESC) WHERE ROWNUM=1));
INSERT INTO KOVAL.JOURNAL (TIME_OUT,AUTO_ID,ROUTE_ID) VALUES ('31-MAY-14 10.30.00.000000000 AM',(SELECT ID FROM (SELECT * FROM KOVAL.AUTO ORDER BY AUTO.ID DESC) WHERE ROWNUM=1),'4');
COMMIT;
END;

--2.	Добавить запись в журнал, в случае, если автомобилей в данном рейсе больше 2-ух, транзакцию откатить
DECLARE auto_counter NUMBER;
BEGIN
INSERT INTO KOVAL.JOURNAL (TIME_OUT,AUTO_ID,ROUTE_ID) VALUES ((select to_char(sysdate) from dual),'1','1');
SELECT COUNT(AUTO_ID) INTO auto_counter FROM KOVAL.JOURNAL WHERE ROUTE_ID = 1;
IF (auto_counter > 2) THEN
    ROLLBACK;
ELSE
    COMMIT;
END IF;
END;

 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 ---   Удаление данных
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 --Hints: delete, where, in, exists, commit, rollback
 
--•	удаление по фильтру и удаление из связанных таблиц
--1.	Удалить поездки из журнала, где дата прибытия меньше некоторой даты
DELETE FROM KOVAL.JOURNAL WHERE TIME_IN < '27-MAR-15 08.26.39.080000000 AM';

--2.	Удалить маршрут и все, связанные с ним, записи в журнале
DELETE FROM KOVAL.JOURNAL WHERE ROUTE_ID='6';
DELETE FROM KOVAL.ROUTES WHERE ID='6';

--3.	Удалить персонал, не имеющий автомобилей
DELETE FROM KOVAL.AUTO_PERSONNEL WHERE ID NOT IN (SELECT PERSONNEL_ID FROM KOVAL.AUTO);

--•	удаление в рамках транзакции
--1.	Удалить в рамках транзакции заданного водителя и его автомобили
BEGIN
DELETE FROM KOVAL.AUTO_PERSONNEL WHERE ID='10';
DELETE FROM KOVAL.AUTO WHERE PERSONNEL_ID='10';
COMMIT;
END;

--2.	то же, что и п1, но транзакцию откатить
BEGIN
DELETE FROM KOVAL.AUTO_PERSONNEL WHERE ID='10';
DELETE FROM KOVAL.AUTO WHERE PERSONNEL_ID='10';
ROLLBACK;
END;

 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 ---   Модификация данных
 --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 --Hints: update, where, in, exists, commit, rollback
 
--•	модификация по фильтру
--1.	Изменить цвет автомобиля с заданным номером
UPDATE KOVAL.AUTO SET COLOR='красный' WHERE NUM='у567о';

--2.	Изменить время прибытия у заданной строки журнала оператора
UPDATE KOVAL.JOURNAL SET TIME_IN=(select to_char(sysdate) from dual) WHERE ID='75';

--3.	Изменить маршрут, по которому следует автомобиль с заданным номером
UPDATE KOVAL.JOURNAL SET ROUTE_ID = 1 WHERE AUTO_ID IN (
  SELECT ID FROM KOVAL.AUTO WHERE NUM = 'у567о');

--•	модификация в рамках транзакции
--1.	В рамках транзакции поменять заданный маршрут всех поездок в журнале на другой и удалить заданный маршрут.
BEGIN
UPDATE KOVAL.JOURNAL SET ROUTE_ID='4' WHERE ROUTE_ID='6';
DELETE FROM KOVAL.ROUTES WHERE ID='6';
COMMIT;
END;

--2.	то же, что и п1, но транзакцию откатить
BEGIN
UPDATE KOVAL.JOURNAL SET ROUTE_ID='4' WHERE ROUTE_ID='6';
DELETE FROM KOVAL.ROUTES WHERE ID='6';
ROLLBACK;
END;

--------------------------------------------------------
--  File created - Tuesday-May-26-2015   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Sequence AUTO_PERSONNEL_SEQ
--------------------------------------------------------

   CREATE SEQUENCE  "AUTO_PERSONNEL_SEQ"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 41 CACHE 20 NOORDER  NOCYCLE
--------------------------------------------------------
--  DDL for Sequence AUTO_SEQ
--------------------------------------------------------

   CREATE SEQUENCE  "AUTO_SEQ"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 41 CACHE 20 NOORDER  NOCYCLE
--------------------------------------------------------
--  DDL for Sequence JOURNAL_SEQ
--------------------------------------------------------

   CREATE SEQUENCE  "JOURNAL_SEQ"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 41 CACHE 20 NOORDER  NOCYCLE
--------------------------------------------------------
--  DDL for Sequence ROUTES_SEQ
--------------------------------------------------------

   CREATE SEQUENCE  "ROUTES_SEQ"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 61 CACHE 20 NOORDER  NOCYCLE
--------------------------------------------------------
--  DDL for Table AUTO
--------------------------------------------------------

  CREATE TABLE "AUTO" 
   (	"ID" NUMBER(*,0), 
	"NUM" VARCHAR2(20), 
	"COLOR" VARCHAR2(20), 
	"MARK" VARCHAR2(20), 
	"PERSONNEL_ID" NUMBER(*,0)
   )
--------------------------------------------------------
--  DDL for Table AUTO_PERSONNEL
--------------------------------------------------------

  CREATE TABLE "AUTO_PERSONNEL" 
   (	"ID" NUMBER(*,0), 
	"FIRST_NAME" VARCHAR2(20), 
	"LAST_NAME" VARCHAR2(20), 
	"FATHER_NAME" VARCHAR2(20)
   )
--------------------------------------------------------
--  DDL for Table JOURNAL
--------------------------------------------------------

  CREATE TABLE "JOURNAL" 
   (	"ID" NUMBER(*,0), 
	"TIME_OUT" TIMESTAMP (6), 
	"TIME_IN" TIMESTAMP (6), 
	"AUTO_ID" NUMBER(*,0), 
	"ROUTE_ID" NUMBER(*,0)
   )
--------------------------------------------------------
--  DDL for Table ROUTES
--------------------------------------------------------

  CREATE TABLE "ROUTES" 
   (	"ID" NUMBER(*,0), 
	"NAME" VARCHAR2(50)
   )
--------------------------------------------------------
--  DDL for View VIEW_1
--------------------------------------------------------

  CREATE OR REPLACE VIEW "VIEW_1" ("FIRST_NAME", "LAST_NAME", "FATHER_NAME") AS 
  SELECT FIRST_NAME, LAST_NAME, FATHER_NAME FROM KOVAL.AUTO_PERSONNEL
--------------------------------------------------------
--  DDL for View VIEW_2
--------------------------------------------------------

  CREATE OR REPLACE VIEW "VIEW_2" ("FIRST_NAME", "LAST_NAME", "FATHER_NAME") AS 
  SELECT FIRST_NAME, LAST_NAME, FATHER_NAME FROM KOVAL.AUTO_PERSONNEL
WHERE LAST_NAME LIKE 'И%'
--------------------------------------------------------
--  DDL for View VIEW_3
--------------------------------------------------------

  CREATE OR REPLACE VIEW "VIEW_3" ("PERSONNEL_ID", "FIRST_NAME", "LAST_NAME", "NUMBER_OF_AUTO") AS 
  SELECT PERSONNEL_ID, FIRST_NAME, LAST_NAME, COUNT(AUTO_PERSONNEL.ID) AS NUMBER_OF_AUTO FROM KOVAL.AUTO 
JOIN KOVAL.AUTO_PERSONNEL ON PERSONNEL_ID = AUTO_PERSONNEL.ID
GROUP BY PERSONNEL_ID, FIRST_NAME, LAST_NAME
--------------------------------------------------------
--  DDL for View VIEW_4
--------------------------------------------------------

  CREATE OR REPLACE VIEW "VIEW_4" ("NAME", "NUM", "MARK") AS 
  SELECT NAME, NUM, MARK FROM KOVAL.ROUTES 
JOIN KOVAL.JOURNAL ON ROUTE_ID = ROUTES.ID
JOIN KOVAL.AUTO ON AUTO.ID = AUTO_ID
WHERE TIME_OUT > '28-MAR-15 08.26.39.080000000 AM' AND TIME_IN < '16-MAY-15 12.00.00.000000000 AM'
ORDER BY NAME
--------------------------------------------------------
--  DDL for View VIEW_5
--------------------------------------------------------

  CREATE OR REPLACE VIEW "VIEW_5" ("NAME", "NUMBER_OF_AUTO") AS 
  SELECT NAME, COUNT(AUTO.ID) FROM KOVAL.ROUTES 
JOIN KOVAL.JOURNAL ON ROUTE_ID = ROUTES.ID
JOIN KOVAL.AUTO ON AUTO.ID = AUTO_ID
GROUP BY NAME
ORDER BY NAME
REM INSERTING into AUTO
SET DEFINE OFF;
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (1,'с145ин','красный','Газель',1);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (2,'л456дс','оранжевый','Форд',1);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (3,'е894уе','желтый','Мерседес',2);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (4,'д297ин','зеленый','Газель',3);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (5,'ф585уц','синий','Форд',3);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (6,'т924гш','фиолетовый','Мерседес',3);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (7,'л633щз','черный','Газель',4);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (8,'к880ьр','белый','Форд',5);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (9,'р129ек','коричневый','Мерседес',6);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (10,'е578ст','синий','Мерседес',2);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (11,'л831ит','зеленый','Форд',7);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (12,'ы936ол','коричневый','Мерседес',8);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (13,'и233ьв','белый','Газель',9);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (14,'и467лл','красный','Форд',10);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (15,'й453аа','синий','Газель',11);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (16,'и678йц','зеленый','Форд',11);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (17,'а555рр','желтый','Мерседес',14);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (18,'в739ла','красный','Газель',12);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (19,'г704то','белый','Мерседес',12);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (20,'л578ру','оранжевый','Форд',12);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (21,'old: ','weegwegwe',null,null);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (22,null,'Мерседес','оранжевый',null);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (23,null,'Форд','синий',null);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (24,null,'Газель','синий',1);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (25,null,'Газель','синий',5);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (26,'qwe','Газель','синий',1);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (27,'йцу','Газель','синий',1);
Insert into AUTO (ID,NUM,COLOR,MARK,PERSONNEL_ID) values (28,'u999i','Газель','синий',24);
REM INSERTING into AUTO_PERSONNEL
SET DEFINE OFF;
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (1,'Александр','Сидоров','Алексеевич');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (2,'Василий','Петров','Дмитриевич');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (3,'Петр','Макаров','Иванович');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (4,'Иван','Романов','Петрович');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (5,'Дмитрий','Ковалев','Васильевич');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (6,'Алексей','Колесников','Петрович');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (7,'Роман','Николаев','Дмитриевич');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (8,'Артем','Шведенко','Алексеевич');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (9,'Андрей','Васильев','Васильевич');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (10,'Егор','Карпов','Иванович');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (11,'Алексей','Петров','Петрович');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (12,'Григорий','Трубин','Дмитиревич');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (13,'Святослав','Лермонтов','Алексеевич');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (16,'Дмитрий','Пушкин','Васильевич');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (14,'Александр','Белоусов','Иванович');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (15,'Яков','Новиков','Петрович');
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (18,'qwe','qwe',null);
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (19,'qwe','qweyu',null);
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (20,'vv','v',null);
Insert into AUTO_PERSONNEL (ID,FIRST_NAME,LAST_NAME,FATHER_NAME) values (24,'qwrqwr','qqwrqwrqwrqwr',null);
REM INSERTING into JOURNAL
SET DEFINE OFF;
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (1,to_timestamp('28-MAR-15 08.26.39.080000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('28-MAR-15 08.27.11.916000000 AM','DD-MON-RR HH.MI.SSXFF AM'),1,2);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (2,to_timestamp('28-MAR-15 08.27.02.994000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('29-MAR-15 08.27.14.154000000 AM','DD-MON-RR HH.MI.SSXFF AM'),5,2);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (3,to_timestamp('28-MAR-15 08.27.06.854000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('29-MAR-15 08.27.16.297000000 AM','DD-MON-RR HH.MI.SSXFF AM'),6,1);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (4,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),null,4,3);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (5,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('30-MAR-15 05.27.18.278000000 AM','DD-MON-RR HH.MI.SSXFF AM'),3,7);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (6,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),null,2,3);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (7,to_timestamp('26-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('31-MAR-15 06.27.18.278000000 AM','DD-MON-RR HH.MI.SSXFF AM'),2,5);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (8,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),null,3,2);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (9,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('31-MAR-15 08.27.18.278000000 AM','DD-MON-RR HH.MI.SSXFF AM'),4,1);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (10,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('31-MAR-15 08.27.18.278000000 AM','DD-MON-RR HH.MI.SSXFF AM'),5,5);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (11,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('31-MAR-15 08.27.18.278000000 AM','DD-MON-RR HH.MI.SSXFF AM'),2,7);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (12,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),null,2,7);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (13,null,null,null,null);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (14,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),null,6,4);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (15,null,null,1,1);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (16,null,null,17,1);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (20,to_timestamp('28-MAR-15 08.27.06.854000000 AM','DD-MON-RR HH.MI.SSXFF AM'),null,21,8);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (18,to_timestamp('28-MAR-15 08.27.09.685000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('30-MAR-15 12.00.00.000000000 AM','DD-MON-RR HH.MI.SSXFF AM'),20,33);
Insert into JOURNAL (ID,TIME_OUT,TIME_IN,AUTO_ID,ROUTE_ID) values (21,to_timestamp('28-MAR-15 08.27.06.854000000 AM','DD-MON-RR HH.MI.SSXFF AM'),to_timestamp('28-MAR-15 08.27.06.854000000 AM','DD-MON-RR HH.MI.SSXFF AM'),16,1);
REM INSERTING into ROUTES
SET DEFINE OFF;
Insert into ROUTES (ID,NAME) values (1,'Выборгский');
Insert into ROUTES (ID,NAME) values (2,'Пулковский');
Insert into ROUTES (ID,NAME) values (3,'Петергофский');
Insert into ROUTES (ID,NAME) values (4,'Пермский');
Insert into ROUTES (ID,NAME) values (5,'Гатчински');
Insert into ROUTES (ID,NAME) values (6,'Московский');
Insert into ROUTES (ID,NAME) values (7,'Ломоносовский');
Insert into ROUTES (ID,NAME) values (8,'Новгородский');
Insert into ROUTES (ID,NAME) values (9,'Тверской');
Insert into ROUTES (ID,NAME) values (10,'Краснодарский');
Insert into ROUTES (ID,NAME) values (11,'Волгоградский');
Insert into ROUTES (ID,NAME) values (12,'Владикавказский');
Insert into ROUTES (ID,NAME) values (13,'Якутский');
Insert into ROUTES (ID,NAME) values (14,'Баварский');
Insert into ROUTES (ID,NAME) values (15,'Мюнхенский');
Insert into ROUTES (ID,NAME) values (16,'Парижский');
Insert into ROUTES (ID,NAME) values (17,'Лондонский');
Insert into ROUTES (ID,NAME) values (18,'Карельский');
Insert into ROUTES (ID,NAME) values (29,'QWE');
Insert into ROUTES (ID,NAME) values (37,'qwe');
Insert into ROUTES (ID,NAME) values (31,'QWE');
Insert into ROUTES (ID,NAME) values (32,'QWE');
Insert into ROUTES (ID,NAME) values (33,'QWE');
Insert into ROUTES (ID,NAME) values (28,'привет');
Insert into ROUTES (ID,NAME) values (45,'vvvvvvvvvvv');
REM INSERTING into VIEW_1
SET DEFINE OFF;
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Александр','Сидоров','Алексеевич');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Василий','Петров','Дмитриевич');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Петр','Макаров','Иванович');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Иван','Романов','Петрович');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Дмитрий','Ковалев','Васильевич');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Алексей','Колесников','Петрович');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Роман','Николаев','Дмитриевич');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Артем','Шведенко','Алексеевич');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Андрей','Васильев','Васильевич');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Егор','Карпов','Иванович');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Алексей','Петров','Петрович');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Григорий','Трубин','Дмитиревич');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Святослав','Лермонтов','Алексеевич');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Дмитрий','Пушкин','Васильевич');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Александр','Белоусов','Иванович');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('Яков','Новиков','Петрович');
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('qwe','qwe',null);
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('qwe','qweyu',null);
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('vv','v',null);
Insert into VIEW_1 (FIRST_NAME,LAST_NAME,FATHER_NAME) values ('qwrqwr','qqwrqwrqwrqwr',null);
REM INSERTING into VIEW_2
SET DEFINE OFF;
REM INSERTING into VIEW_3
SET DEFINE OFF;
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (11,'Алексей','Петров',2);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (2,'Василий','Петров',2);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (14,'Александр','Белоусов',1);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (7,'Роман','Николаев',1);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (8,'Артем','Шведенко',1);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (12,'Григорий','Трубин',3);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (5,'Дмитрий','Ковалев',2);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (1,'Александр','Сидоров',5);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (3,'Петр','Макаров',3);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (4,'Иван','Романов',1);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (9,'Андрей','Васильев',1);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (10,'Егор','Карпов',1);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (24,'qwrqwr','qqwrqwrqwrqwr',1);
Insert into VIEW_3 (PERSONNEL_ID,FIRST_NAME,LAST_NAME,NUMBER_OF_AUTO) values (6,'Алексей','Колесников',1);
REM INSERTING into VIEW_4
SET DEFINE OFF;
Insert into VIEW_4 (NAME,NUM,MARK) values ('QWE','л578ру','Форд');
Insert into VIEW_4 (NAME,NUM,MARK) values ('Выборгский','и678йц','Форд');
Insert into VIEW_4 (NAME,NUM,MARK) values ('Выборгский','т924гш','Мерседес');
Insert into VIEW_4 (NAME,NUM,MARK) values ('Выборгский','д297ин','Газель');
Insert into VIEW_4 (NAME,NUM,MARK) values ('Гатчински','ф585уц','Форд');
Insert into VIEW_4 (NAME,NUM,MARK) values ('Ломоносовский','е894уе','Мерседес');
Insert into VIEW_4 (NAME,NUM,MARK) values ('Ломоносовский','л456дс','Форд');
Insert into VIEW_4 (NAME,NUM,MARK) values ('Пулковский','ф585уц','Форд');
REM INSERTING into VIEW_5
SET DEFINE OFF;
Insert into VIEW_5 (NAME,NUMBER_OF_AUTO) values ('QWE',1);
Insert into VIEW_5 (NAME,NUMBER_OF_AUTO) values ('Выборгский',5);
Insert into VIEW_5 (NAME,NUMBER_OF_AUTO) values ('Гатчински',2);
Insert into VIEW_5 (NAME,NUMBER_OF_AUTO) values ('Ломоносовский',3);
Insert into VIEW_5 (NAME,NUMBER_OF_AUTO) values ('Новгородский',1);
Insert into VIEW_5 (NAME,NUMBER_OF_AUTO) values ('Пермский',1);
Insert into VIEW_5 (NAME,NUMBER_OF_AUTO) values ('Петергофский',2);
Insert into VIEW_5 (NAME,NUMBER_OF_AUTO) values ('Пулковский',3);
--------------------------------------------------------
--  Constraints for Table AUTO
--------------------------------------------------------

  ALTER TABLE "AUTO" ADD CONSTRAINT "AUTO_PK" PRIMARY KEY ("ID") ENABLE
  ALTER TABLE "AUTO" MODIFY ("ID" NOT NULL ENABLE)
--------------------------------------------------------
--  Constraints for Table AUTO_PERSONNEL
--------------------------------------------------------

  ALTER TABLE "AUTO_PERSONNEL" ADD CONSTRAINT "AUTO_PERSONNEL_PK" PRIMARY KEY ("ID") ENABLE
  ALTER TABLE "AUTO_PERSONNEL" MODIFY ("ID" NOT NULL ENABLE)
--------------------------------------------------------
--  Constraints for Table JOURNAL
--------------------------------------------------------

  ALTER TABLE "JOURNAL" ADD CONSTRAINT "JOURNAL_PK" PRIMARY KEY ("ID") ENABLE
  ALTER TABLE "JOURNAL" MODIFY ("ID" NOT NULL ENABLE)
--------------------------------------------------------
--  Constraints for Table ROUTES
--------------------------------------------------------

  ALTER TABLE "ROUTES" ADD CONSTRAINT "ROUTES_PK" PRIMARY KEY ("ID") ENABLE
--------------------------------------------------------
--  Ref Constraints for Table AUTO
--------------------------------------------------------

  ALTER TABLE "AUTO" ADD CONSTRAINT "FK_AUTO_AUTO_PERSONNEL" FOREIGN KEY ("PERSONNEL_ID")
	  REFERENCES "AUTO_PERSONNEL" ("ID") ENABLE
--------------------------------------------------------
--  Ref Constraints for Table JOURNAL
--------------------------------------------------------

  ALTER TABLE "JOURNAL" ADD CONSTRAINT "FK_JOURNAL_AUTO" FOREIGN KEY ("AUTO_ID")
	  REFERENCES "AUTO" ("ID") ENABLE
  ALTER TABLE "JOURNAL" ADD CONSTRAINT "FK_JOURNAL_ROUTES" FOREIGN KEY ("ROUTE_ID")
	  REFERENCES "ROUTES" ("ID") ENABLE
--------------------------------------------------------
--  DDL for Trigger AUTO_PERSONNEL_TRG
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "AUTO_PERSONNEL_TRG" 
BEFORE INSERT ON KOVAL.AUTO_PERSONNEL 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.ID IS NULL THEN
      SELECT AUTO_PERSONNEL_SEQ.NEXTVAL INTO :NEW.ID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
ALTER TRIGGER "AUTO_PERSONNEL_TRG" ENABLE
--------------------------------------------------------
--  DDL for Trigger AUTO_TRG
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "AUTO_TRG" 
BEFORE INSERT ON KOVAL.AUTO 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.ID IS NULL THEN
      SELECT AUTO_SEQ.NEXTVAL INTO :NEW.ID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
ALTER TRIGGER "AUTO_TRG" ENABLE
--------------------------------------------------------
--  DDL for Trigger JOURNAL_TRG
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "JOURNAL_TRG" 
BEFORE INSERT ON KOVAL.JOURNAL 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.ID IS NULL THEN
      SELECT JOURNAL_SEQ.NEXTVAL INTO :NEW.ID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
ALTER TRIGGER "JOURNAL_TRG" ENABLE
--------------------------------------------------------
--  DDL for Trigger ROUTES_TRG
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "ROUTES_TRG" 
BEFORE INSERT ON KOVAL.ROUTES 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.ID IS NULL THEN
      SELECT ROUTES_SEQ.NEXTVAL INTO :NEW.ID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
ALTER TRIGGER "ROUTES_TRG" ENABLE
--------------------------------------------------------
--  DDL for Trigger TRIGGER_11
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "TRIGGER_11" 
BEFORE INSERT ON KOVAL.AUTO
FOR EACH ROW
DECLARE
tmp NUMBER;
BEGIN
  SELECT COUNT(*) INTO tmp FROM KOVAL.AUTO WHERE NUM=:new.NUM;
  IF tmp>0 THEN
  raise_application_error(-20001,'Car with this number already exists!');
  END IF;
END;
ALTER TRIGGER "TRIGGER_11" ENABLE
--------------------------------------------------------
--  DDL for Trigger TRIGGER_12
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "TRIGGER_12" 
BEFORE INSERT ON KOVAL.JOURNAL
FOR EACH ROW
DECLARE
tmp NUMBER;
BEGIN
  SELECT COUNT(*) INTO tmp FROM KOVAL.JOURNAL WHERE :new.TIME_IN IS NOT NULL;
  IF tmp>0 THEN
  raise_application_error(-20001,'Time in is not null!');
  END IF;
END;
ALTER TRIGGER "TRIGGER_12" ENABLE
--------------------------------------------------------
--  DDL for Trigger TRIGGER_13
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "TRIGGER_13" 
BEFORE INSERT ON KOVAL.JOURNAL
FOR EACH ROW
DECLARE
tmp NUMBER;
BEGIN
  SELECT COUNT(*) INTO tmp FROM KOVAL.JOURNAL WHERE TIME_IN IS NULL AND :new.AUTO_ID = AUTO_ID;
  IF tmp>0 THEN
  raise_application_error(-20001,'Auto is not back!');
  END IF;
END;
ALTER TRIGGER "TRIGGER_13" ENABLE
--------------------------------------------------------
--  DDL for Trigger TRIGGER_21
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "TRIGGER_21" 
BEFORE UPDATE ON KOVAL.AUTO
FOR EACH ROW
BEGIN
  IF :new.NUM<>:old.NUM THEN
  :new.NUM:=:old.NUM;
  END IF;
END;
ALTER TRIGGER "TRIGGER_21" ENABLE
--------------------------------------------------------
--  DDL for Trigger TRIGGER_22
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "TRIGGER_22" 
BEFORE UPDATE ON KOVAL.JOURNAL
FOR EACH ROW
BEGIN
  IF :new.ROUTE_ID<>:old.ROUTE_ID AND :old.TIME_IN is null THEN
  :new.ROUTE_ID:=:old.ROUTE_ID;
  END IF;
END;
ALTER TRIGGER "TRIGGER_22" ENABLE
--------------------------------------------------------
--  DDL for Trigger TRIGGER_24
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "TRIGGER_24" 
BEFORE UPDATE ON KOVAL.JOURNAL
FOR EACH ROW
BEGIN
  IF :new.TIME_IN < :old.TIME_OUT THEN
  raise_application_error(-20001,'Time in error!');
  END IF;
END;
ALTER TRIGGER "TRIGGER_24" ENABLE
--------------------------------------------------------
--  DDL for Trigger TRIGGER_31
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "TRIGGER_31" 
BEFORE DELETE ON KOVAL.ROUTES
FOR EACH ROW
DECLARE
  tmp NUMBER;
BEGIN
  SELECT COUNT(*) INTO tmp FROM KOVAL.JOURNAL
  WHERE :old.ID = ROUTE_ID;
  IF(tmp > 0) THEN
    raise_application_error(-20001,'Can not delete this route!');
  END IF;
END;
ALTER TRIGGER "TRIGGER_31" ENABLE
--------------------------------------------------------
--  DDL for Trigger TRIGGER_32
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "TRIGGER_32" 
BEFORE DELETE ON KOVAL.AUTO
FOR EACH ROW
DECLARE
  tmp NUMBER;
BEGIN
  SELECT COUNT(*) INTO tmp FROM KOVAL.JOURNAL
  WHERE :old.ID = AUTO_ID;
  IF(tmp > 0) THEN
    raise_application_error(-20001,'Can not delete this auto!');
  END IF;
END;
ALTER TRIGGER "TRIGGER_32" ENABLE
--------------------------------------------------------
--  DDL for Trigger TRIGGER_33
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "TRIGGER_33" 
BEFORE DELETE ON KOVAL.AUTO_PERSONNEL
FOR EACH ROW
DECLARE
  tmp NUMBER;
BEGIN
  SELECT COUNT(*) INTO tmp FROM KOVAL.AUTO
  WHERE :old.ID = PERSONNEL_ID;
  IF(tmp > 0) THEN
    raise_application_error(-20001,'Can not delete this person!');
  END IF;
END;
ALTER TRIGGER "TRIGGER_33" ENABLE
--------------------------------------------------------
--  DDL for Procedure PROCEDURE_11
--------------------------------------------------------
set define off;

  CREATE OR REPLACE PROCEDURE "PROCEDURE_11" IS
BEGIN
FOR r_row IN ( 
SELECT PERSONNEL_ID p, FIRST_NAME f, LAST_NAME l FROM KOVAL.AUTO 
JOIN KOVAL.AUTO_PERSONNEL ON PERSONNEL_ID = AUTO_PERSONNEL.ID
GROUP BY PERSONNEL_ID, FIRST_NAME, LAST_NAME
HAVING COUNT(PERSONNEL_ID) = (SELECT MAX(NUMBER_OF_AUTO) FROM (SELECT COUNT(PERSONNEL_ID) AS NUMBER_OF_AUTO FROM KOVAL.AUTO 
GROUP BY PERSONNEL_ID))
) LOOP
dbms_output.put_line(r_row.p||'     '||r_row.f||'     '||r_row.l);
END LOOP;
END;
--------------------------------------------------------
--  DDL for Procedure PROCEDURE_12
--------------------------------------------------------
set define off;

  CREATE OR REPLACE PROCEDURE "PROCEDURE_12" IS
BEGIN
FOR r_row IN ( 
SELECT COLOR s FROM KOVAL.AUTO
GROUP BY COLOR
HAVING COUNT(COLOR) = (SELECT MAX(POPULAR_COLOR) FROM (SELECT COUNT(COLOR) AS POPULAR_COLOR FROM KOVAL.AUTO GROUP BY COLOR))
) LOOP
dbms_output.put_line(r_row.s);
END LOOP;
END;
--------------------------------------------------------
--  DDL for Procedure PROCEDURE_13
--------------------------------------------------------
set define off;

  CREATE OR REPLACE PROCEDURE "PROCEDURE_13" IS
BEGIN
FOR r_row IN ( 
SELECT ROUTE_ID r, NAME n, AVG(sysdate + (TIME_IN - TIME_OUT)*24*60 - sysdate) AS MIDDLE_TIME_IN_MINUTES FROM KOVAL.JOURNAL
JOIN KOVAL.ROUTES ON ROUTE_ID = ROUTES.ID
GROUP BY ROUTE_ID, NAME
ORDER BY ROUTE_ID
) LOOP
dbms_output.put_line(r_row.r||'     '||r_row.n||'     '||r_row.MIDDLE_TIME_IN_MINUTES);
END LOOP;
END;
--------------------------------------------------------
--  DDL for Procedure PROCEDURE_21
--------------------------------------------------------
set define off;

  CREATE OR REPLACE PROCEDURE "PROCEDURE_21" 
(
  ROUTE_ID_PARAM IN NUMBER 
) IS 
BEGIN
FOR r_row IN ( 
SELECT DISTINCT AUTO_ID i, MARK m FROM KOVAL.JOURNAL
JOIN KOVAL.AUTO ON AUTO.ID = AUTO_ID
WHERE ROUTE_ID = ROUTE_ID_PARAM
ORDER BY AUTO_ID
) LOOP
dbms_output.put_line(r_row.i||'     '||r_row.m);
END LOOP;
END;
--------------------------------------------------------
--  DDL for Procedure PROCEDURE_22
--------------------------------------------------------
set define off;

  CREATE OR REPLACE PROCEDURE "PROCEDURE_22" 
(
  AUTO_ID_PARAM IN NUMBER 
) IS 
BEGIN
FOR r_row IN ( 
SELECT DISTINCT ROUTE_ID i, NAME n FROM KOVAL.JOURNAL
JOIN KOVAL.ROUTES ON ROUTES.ID = ROUTE_ID
WHERE AUTO_ID = AUTO_ID_PARAM
ORDER BY ROUTE_ID
) LOOP
dbms_output.put_line(r_row.i||'     '||r_row.n);
END LOOP;
END;
--------------------------------------------------------
--  DDL for Procedure PROCEDURE_23
--------------------------------------------------------
set define off;

  CREATE OR REPLACE PROCEDURE "PROCEDURE_23" 
(
  AUTO_ID_PARAM1 IN NUMBER,
  AUTO_ID_PARAM2 IN NUMBER
) IS 
BEGIN
FOR r_row IN ( 
SELECT R1 AS ROUTE_ID, NAME n FROM (SELECT ROUTE_ID R1, (TIME_IN - TIME_OUT) AS DELTA1 FROM KOVAL.JOURNAL WHERE AUTO_ID = AUTO_ID_PARAM1)
JOIN (SELECT ROUTE_ID R2, (TIME_IN - TIME_OUT) AS DELTA2 FROM KOVAL.JOURNAL WHERE AUTO_ID = AUTO_ID_PARAM2) ON R1 = R2
JOIN KOVAL.ROUTES ON R1 = ROUTES.ID
WHERE DELTA1 > DELTA2
) LOOP
dbms_output.put_line(r_row.ROUTE_ID||'     '||r_row.n);
END LOOP;
END;
--------------------------------------------------------
--  DDL for Procedure PROCEDURE_31
--------------------------------------------------------
set define off;

  CREATE OR REPLACE PROCEDURE "PROCEDURE_31" 
(
  COLOR_PARAM IN VARCHAR
, COUNTER_AUTO OUT NUMBER
) IS 
BEGIN
SELECT COUNT(*) INTO COUNTER_AUTO FROM KOVAL.AUTO
WHERE COLOR = COLOR_PARAM;
END;
--------------------------------------------------------
--  DDL for Procedure PROCEDURE_32
--------------------------------------------------------
set define off;

  CREATE OR REPLACE PROCEDURE "PROCEDURE_32" 
(
  ROUTE_ID_PARAM IN NUMBER
, COUNTER_AUTO OUT NUMBER
) IS 
BEGIN
SELECT COUNT(*) INTO COUNTER_AUTO FROM KOVAL.JOURNAL
WHERE ROUTE_ID = ROUTE_ID_PARAM;
END;
--------------------------------------------------------
--  DDL for Procedure PROCEDURE_33
--------------------------------------------------------
set define off;

  CREATE OR REPLACE PROCEDURE "PROCEDURE_33" 
(
  ROUTE_ID_PARAM IN NUMBER 
, BEST_TIME OUT NUMBER
, BEST_AUTO OUT NUMBER
) IS 
BEGIN
SELECT AUTO_ID, (sysdate + (TIME_IN - TIME_OUT)*24*60*60 - sysdate) AS btime_in_sec INTO BEST_AUTO, BEST_TIME FROM 
    (SELECT * FROM KOVAL.JOURNAL WHERE JOURNAL.ROUTE_ID = ROUTE_ID_PARAM ORDER BY (TIME_IN - TIME_OUT)) WHERE ROWNUM=1;
END;

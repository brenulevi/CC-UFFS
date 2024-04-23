-- create tablespaces 1 and 2
CREATE TABLESPACE mytb01 LOCATION '/mypgtbs/mytb01';
CREATE TABLESPACE mytb02 LOCATION '/mypgtbs/mytb02';

-- create user1 and user2
CREATE USER user1 PASSWORD 'user1';
CREATE USER user2 PASSWORD 'user2';

-- create database using tablespace
CREATE DATABASE mydb TABLESPACE mytb01;

-- connect to mydb
\c mydb postgres

-- create schema
CREATE SCHEMA myschema;

-- set schema default to user and database
ALTER USER user1 SET search_path TO myschema;
ALTER DATABASE mydb SET search_path TO myschema;
GRANT USAGE,CREATE ON SCHEMA myschema TO user1;

-- change db owner
ALTER DATABASE mydb OWNER TO user1;

-- script to populate mydb
CREATE TABLE product (					
	pid INTEGER NOT NULL PRIMARY KEY,				
	name VARCHAR(30) NOT NULL,					
	pqty INTEGER NOT NULL);

CREATE TABLE sale (
   sid integer not null primary key,
   sdate date not null);
   
CREATE TABLE sale_item (
	sid INTEGER NOT NULL,
	pid INTEGER NOT NULL,
	sqty INTEGER NOT NULL,
	CONSTRAINT pk_sale_item PRIMARY KEY (sid,pid),
	CONSTRAINT fk_sale_item_sale FOREIGN KEY (sid) REFERENCES sale(sid),
	CONSTRAINT fk_sale_item_product FOREIGN KEY (pid) REFERENCES product(pid)
);

CREATE OR REPLACE PROCEDURE ins_product(qttup int ) LANGUAGE plpgsql
AS $$
DECLARE
   prd_tup product%rowtype;
   counter int:=0;
   stock int[5]:='{3,5,8,10,15}'; -- primeira posicao é 1
BEGIN
   -- Or stock:=Array[3,5,8,10,15];
   LOOP
      prd_tup.pid:=(random()*100*qttup)::int;
      prd_tup.name:=left(MD5(random()::text),20);
      prd_tup.pqty:=stock[(random()*4)::int+1];
      IF (NOT EXISTS (SELECT 1 FROM product WHERE pid=prd_tup.pid))
      THEN
        INSERT INTO product (pid,name,pqty) VALUES (prd_tup.pid,prd_tup.name,prd_tup.pqty);
        counter:=counter+1;
      END IF;
      EXIT WHEN counter >= qttup;
   END LOOP;
END; $$;
--
CREATE OR REPLACE PROCEDURE ins_sale(qttup int ) LANGUAGE plpgsql
AS $$
DECLARE
   sale_tup sale%rowtype;
   counter int:=0;
BEGIN
   LOOP
      sale_tup.sid:=(random()*100*qttup)::int;
      sale_tup.sdate:='2023-01-01 00:00:00'::timestamp + random()*(now()-timestamp '2023-01-01 00:00:00');
      IF (NOT EXISTS (SELECT 1 FROM sale WHERE sid=sale_tup.sid))
      THEN
        INSERT INTO sale (sid,sdate) VALUES (sale_tup.sid,sale_tup.sdate);
        counter:=counter+1;
      END IF;
      EXIT WHEN counter >= qttup;
   END LOOP;
END; $$;

CREATE OR REPLACE PROCEDURE ins_sale_item (qttup int, qttsale int, qttprod int) LANGUAGE plpgsql
AS $$
DECLARE
  sale_item_tup sale_item%rowtype;
  itBySale int[6]:='{2,4,7,8,9,10}';
  counter1 int:=0;
  counter2 int:=0;
  n int:=0;
  sale_id int:=0;
  prod_id int:=0;
BEGIN
   LOOP
      counter2:=0;
      n:=itBySale[(random()*5)::int+1];

      LOOP
         SELECT sid FROM sale INTO sale_id WHERE sid=(random()*100*qttsale)::int;
         EXIT WHEN sale_id<>0;
      END LOOP;
      
      sale_item_tup.sid:=sale_id;

      LOOP
         LOOP
            SELECT pid, pqty FROM product INTO prod_id,sale_item_tup.sqty WHERE pid=(random()*100*qttprod)::int;
            EXIT WHEN prod_id<>0;
         END LOOP;

         sale_item_tup.pid:=prod_id;

         IF(NOT EXISTS (SELECT 1 FROM sale_item WHERE sid=sale_item_tup.sid AND pid=sale_item_tup.pid)) THEN
            INSERT INTO sale_item (sid, pid, sqty) VALUES (sale_item_tup.sid, sale_item_tup.pid, sale_item_tup.sqty);
            counter2:=counter2+1;
            counter1:=counter1+1;
         END IF;
         EXIT WHEN counter2>=n;
      END LOOP;
      EXIT WHEN counter1>=qttup;
   END LOOP;
END; $$;

CREATE OR REPLACE PROCEDURE call_all (qtsale int, qtprod int, qtitem int) LANGUAGE plpgsql
AS $$
BEGIN
   CALL ins_product(qtprod);
   CALL ins_sale(qtsale);
   CALL ins_sale_item(qtitem, qtsale, qtprod);
END; $$;

CALL call_all(500, 1000, 1250);

-- create audit table
CREATE TABLE audit (
aoperation CHAR NOT NULL,
aold INTEGER NOT NULL,
anew INTEGER NULL,
adate TIMESTAMP NOT NULL,
auser TEXT NOT NULL
);

-- create trigger
CREATE OR REPLACE FUNCTION trig_sale_item_audit()
RETURNS trigger
LANGUAGE plpgsql
AS $$
BEGIN
   IF(TG_OP = 'DELETE') THEN
      INSERT INTO audit (aoperation, aold, adate, auser) VALUES ('D', OLD.sqty, now(), current_user);
      RETURN OLD;
   ELSIF(TG_OP = 'UPDATE') THEN
      INSERT INTO audit (aoperation, aold, anew, adate, auser) VALUES ('U', OLD.sqty, NEW.sqty, now(), current_user);
      RETURN NEW;
   END IF;
   RETURN NULL;
END; $$;

CREATE TRIGGER sale_item_audit AFTER UPDATE OR DELETE ON sale_item FOR EACH ROW EXECUTE PROCEDURE trig_sale_item_audit();

-- grant privilege of select in sale and product
GRANT SELECT ON product TO user2;
GRANT SELECT ON sale TO user2;

-- grant all privilege to user2 in sale_item
GRANT ALL ON sale_item TO user2;



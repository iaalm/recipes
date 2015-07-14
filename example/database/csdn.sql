load data local infile '/home/simon/a.sql' 
into table csdn
FIELDS terminated by '\ \#\ ';
select count(*) from csdn;
select * from csdn order by password;
DELETE FROM csdn
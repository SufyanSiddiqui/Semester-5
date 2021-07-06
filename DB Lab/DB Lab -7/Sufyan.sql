-----------LAB07--------------------

SET SERVEROUTPUT ON;

DECLARE
Width INTEGER;
Height INTEGER := 2 ;
Area INTEGER;

BEGIN
Area := 6;
Width := area/height;
DBMS_OUTPUT.PUT_LINE( 'width = ' || width);

EXCEPTION
WHEN ZERO_DIVIDE THEN
DBMS_OUTPUT.PUT_LINE('Division by Zero');

END;

------Program 2--------
SET SERVEROUTPUT ON;
declare
eno HR.EMPLOYEES.Employee_id%type;
name1 HR.EMPLOYEES.first_name%type;

begin
eno := 100;
select first_name into name1 from HR.EMPLOYEES where EMPLOYEE_ID=eno;
dbms_output.put_line('name of the employee is '||name1);
end;

------Program 3--------
SET SERVEROUTPUT ON;
declare
eno HR.EMPLOYEES.Employee_id%type;
name1 HR.EMPLOYEES.first_name%type;

begin
eno := 1;
select first_name into name1 from HR.EMPLOYEES where EMPLOYEE_ID=eno;
dbms_output.put_line('name of the employee is '||name1);

EXCEPTION
WHEN NO_DATA_FOUND
THEN dbms_output.put_line('No Data Found');

end;


--------Task1-------------
SET SERVEROUTPUT ON;

Declare
a1 integer;
a2 integer;
sum1 integer;

begin
a1:=&a1;
a2:=&a2;

sum1 := a1+a2;
dbms_output.put_line('Sum of the integers '||sum1);

end;

------------Task2-------------
SET SERVEROUTPUT ON;

Declare
a1 integer;
a2 integer;
i integer;
sum1 integer;
begin
sum1:=0;
a1:=&a1;
a2:=&a2;
i:=a1;
while i<=a2 loop
sum1:= sum1+i;
i:=i+1;
end loop;
dbms_output.put_line('sum1 =' || sum1);
end;


------------Task3-------------

SET SERVEROUTPUT ON;
declare
eno HR.EMPLOYEES.Employee_id%type;
name1 HR.EMPLOYEES.first_name%type;
deptname HR.Departments.department_name%type;
deptid HR.EMPLOYEES.department_id%TYPE;
hdate HR.EMPLOYEES.hire_date%type;

begin
eno := &eno;
select first_name,EMPLOYEE_ID,Hr.departments.department_name,HIRE_DATE into name1,eno,deptname,hdate from HR.EMPLOYEES 
join hr.departments on departments.department_id = employees.department_id where employee_id=eno;
dbms_output.put_line('name of the employee is '||name1);
dbms_output.put_line('ID of the employee is '||eno);
dbms_output.put_line('department of the employee is '||deptname);
dbms_output.put_line('hire date of the employee is '||hdate);

EXCEPTION
WHEN NO_DATA_FOUND
THEN dbms_output.put_line('No Data Found');

end;
-------TASK6-----------
SET SERVEROUTPUT ON;
declare
eno HR.EMPLOYEES.Employee_id%type;
name1 HR.EMPLOYEES.first_name%type;
name2 HR.EMPLOYEES.last_name%type;
email HR.EMPLOYEES.email%type;
nos HR.EMPLOYEES.phone_number%type;
j_id HR.EMPLOYEES.JOB_ID%type;
salary HR.EMPLOYEES.Salary%type;
mg_id HR.EMPLOYEES.manager_id%type;
deptid HR.EMPLOYEES.department_id%TYPE;
hdate HR.EMPLOYEES.hire_date%type;


begin
eno :=&eno;
name1 :=&name1;
name2 := &name2;
email :=&email;
nos := &nos;
j_id := &j_id;
salary := &salary;
mg_id := &mg_id;
dept_id := &dept_id;
h_date := &h_date;

insert into HR.EMPLOYEES values(eno,name1,name2);
end;


-----TASK9---------
SET SERVEROUTPUT ON;

Declare
a1 integer;
a2 integer;
i integer;
sum1 integer;
begin
sum1:=0;
a1:=1;
i:=a1;
while i<=100 loop
sum1:= sum1+i;
i:=i+1;
end loop;
dbms_output.put_line('sum1 =' || sum1);
end;
SET SERVEROUTPUT ON;
Declare
n integer;
sum1 integer;
 BEGIN
 sum1 :=0;
 n :=100;
 sum1:= n*(n+1)/2;
 dbms_output.put_line('sum1 =' || sum1);
 
 end;
 
Create or replace view Emp_View AS 
Select * FROM HR.employees
where department_id = 110;


Select * from emp_view;

SET SERVEROUTPUT ON;
Create or replace Procedure Sum2 (a IN Number, b IN Number)
IS
s1 NUMBER:=0;
Begin
s1 := 0;
s1 := a+b;
DBMS_OUTPUT.PUT_LINE('SUM IS: ' || s1);
END;
/
EXEC Sum2(2,2);
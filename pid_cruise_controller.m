close all;
clear all;

v_old=input('enter current velocity of car');
v_des=input('enter desired velocity of car');
kp=5;kd=1;ki=6;
e_old=0;
k=0.01

for t=0:0.02:20;
    en=v_des-v_old;
    e_dot=en-e_old;
    E=e_old+en;
    a=kp*en+kd*e_dot+ki*E;
   v_new=v_old+a*k;
    e_old=en;
    v_old=v_new;
  p=[t v_new]
  plot(t,v_new,'k-*')
  hold on
end


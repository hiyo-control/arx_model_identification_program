%% �f�[�^�C���|�[�g
cd ../
raw_data = csvread('0_process_data_backward_difference.csv',1,0);
process_data = csvread('1_process_data_analysis.csv',1,0);
impulse = csvread('2_impulse_response.csv',1,0);
arx_estimate = csvread('3_5_arx_model_estimate.csv',1,0);
pole_and_zero = csvread('4_poles_and_zeros.csv',2,0);
reduced_arx_estimate = csvread('5_3_reduced_arx_model_estimate.csv',1,0);

%% �O���t�o��
cd matlab_graph

figure(1);
plot(raw_data(:,1), raw_data(:,2), 'linewidth',2);grid;
set(gca,'fontsize', 16);ylim([0 5.1]);
xlabel('Time [sec]','fontsize',18);ylabel('Input command [-]','fontsize',18);
saveas(gcf,'�������_���f�[�^.jpg');

figure(2);
plot(raw_data(:,1), raw_data(:,3), 'linewidth',2);grid;
set(gca,'fontsize', 16);
xlabel('Time [sec]','fontsize',18);ylabel('output [rad/sec]','fontsize',18);
saveas(gcf,'����o��_���f�[�^.jpg');

figure(3);
plot(process_data(:,1), process_data(:,2), 'linewidth',2);grid;
set(gca,'fontsize', 16);
xlabel('Time [sec]','fontsize',18);ylabel('input command [-]','fontsize',18);
saveas(gcf,'�������_�O�����ς�.jpg');

figure(4);
plot(process_data(:,1), process_data(:,3), 'linewidth',2);grid;
set(gca,'fontsize', 16);
xlabel('Time [sec]','fontsize',18);ylabel('output [rad/sec]','fontsize',18);
saveas(gcf,'����o��_�O�����ς�.jpg');

figure(5);
plot(impulse(:,1), impulse(:,2), 'o', 'linewidth',2);grid;
set(gca,'fontsize', 16);xlim([0 20]);
xlabel('lag','fontsize',18);ylabel('response','fontsize',18);
saveas(gcf,'�C���p���X����_���։�͖@.jpg');

figure(6);
plot(arx_estimate(:,1), arx_estimate(:,2), arx_estimate(:,1), arx_estimate(:,3), 'linewidth',2);grid;
set(gca,'fontsize', 16);
legend({'�����l','����l'},'fontsize',14, 'location', 'best');
xlabel('Time [sec]','fontsize',18);ylabel('output [rad/sec]','fontsize',18);
saveas(gcf,'arx���f��_�����l�Ɛ���l.jpg');

figure(7);
plot(pole_and_zero(:,1),   pole_and_zero(:,2)  ,'x', ...
     pole_and_zero(1:6,4), pole_and_zero(1:6,5),'o', ...
     'linewidth',2, 'MarkerSize', 10);grid;
set(gca,'fontsize', 16);xlim([-1.2 1.2]);ylim([-0.8 0.8]);
legend({'��','��_'},'fontsize',14, 'location', 'best');
xlabel('Real','fontsize',18);ylabel('Image','fontsize',18);
saveas(gcf,'�ɁE��_.jpg');

figure(8);
plot(reduced_arx_estimate(:,1), reduced_arx_estimate(:,2), ...
     reduced_arx_estimate(:,1), reduced_arx_estimate(:,3), 'linewidth',2);grid;
set(gca,'fontsize', 16);
legend({'�����l','����l'},'fontsize',14, 'location', 'best');
xlabel('Time [sec]','fontsize',18);ylabel('output [rad/sec]','fontsize',18);
saveas(gcf,'�᎟��arx���f��_�����l�Ɛ���l.jpg');

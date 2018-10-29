%% Clear
clear;
close all;
clc;

%% Retrieve data
raw = csvread('raw.csv')';
t = raw(1,:);
tmin = 73000;
tmax = 82500;

% Retreive only meaningful data
idx = [1 0];
for i = t
    if (i > tmin)
        idx = idx+[0 1];
    else
        idx = idx+[1 1];
    end
    if (i > tmax)
        break;
    end
end

p1 = raw(2,:);   % Pressure transducer 1 (left)
p2 = raw(3,:);    % Pressure transducer 2 (right)
pavg = (p1+p2)/2; % Mean pressure
lc = raw(4,:);    % Load cell

%idx2 = 0;
%for i = lc
%    idx2 = idx2+1;
%    if i < 0
%        lc(idx2) = 0;
%    end
%end

%% Total impulse
tint = t(idx(1):idx(2))/1000;
lcint = lc(idx(1):idx(2))*9.80665;
imp = zeros(1, length(tint));
for i = 1:(length(tint)-1)
    int = tint(i+1)-tint(i);
    imp(i+1) = imp(i)+lcint(i)*int;
end

%% Plot
figure('pos', [0 0 1600 1000]);
figure(1);
    plot(t(idx(1):idx(2))/1000, p1(idx(1):idx(2))); hold on;
    plot(t(idx(1):idx(2))/1000, p2(idx(1):idx(2)));
    grid on; grid minor;
    title('Pressure Transducer Raw Data');
    xlabel('Time (seconds)');
    ylabel('Pressure (bar)');
figure('pos', [0 0 1600 1000]);
figure(2);
    plot(t(idx(1):idx(2))/1000, pavg(idx(1):idx(2)));
    grid on; grid minor;
    title('Pressure Transducer Average');
    xlabel('Time (seconds)');
    ylabel('Pressure (bar)');
figure('pos', [0 0 1600 1000]);
figure(3);
    plot(t(idx(1):idx(2))/1000, lc(idx(1):idx(2)));
    grid on; grid minor;
    title('Load Cell Raw Data');
    xlabel('Time (seconds)');
    ylabel('Force (kgf)');
figure('pos', [0 0 1600 1000]);
figure(4);
    plot(t(idx(1):idx(2))/1000, lc(idx(1):idx(2))*9.80665);
    grid on; grid minor;
    title('Load Cell Raw Data');
    xlabel('Time (seconds)');
    ylabel('Force (N)');
figure('pos', [0 0 1600 1000]);
figure(5);
    plot(tint, imp);
    grid on; grid minor;
    title('Total Impulse');
    xlabel('Time (seconds)');
    ylabel('Force*Time (N*s)');
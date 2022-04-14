%-------------------------------------------------------------------
% ECE1774 Advanced Power - Quiz 1 Material Code
% Elizabeth Gilman Spring 2022
%-------------------------------------------------------------------

clear 
clc

%------DEFINITIONS AND DATA COLLECTION--------%

w = 377;
j = 1i;

%Find the Number of Nodes and Lines in the System
[N, numLines] = find_lines_nodes();

%Find Bus Connections
bus_connections = find_bus_connections(N);

%Have User Define the Connections
line_bus_connections = find_line_connections(N, numLines);

%line_bus_connections = [1 1 0 0 0; 1 0 1 1 0; 0 1 1 0 1; 0 0 0 1 1];

%Find the Bus Types
bus_type = find_bus_types();

%Line Data
conductor.r = 0.385; %ohm/mi
conductor.GMR = 0.0217; %ft
conductor.diam = 0.642/12; %ft 
conductor.d = 1.5; %ft
conductor.nb = 2; 

[n_conductor1, n_conductor2] = find_neutral_cond_info();

%Find More Line Data
[line_lengths, phase_distance] = find_line_lengths(numLines);

%--------SOLVING FOR YBUS---------%
%Find Transformer Information
[TX, TX_connections, numTX, TX_lines] = find_transformers();

%Find Admittance of the Lines
Y_lines = find_line_admittance(w, j, numLines, phase_distance, conductor, line_lengths, TX, numTX, TX_lines);

%Find the Shunt Admittance of the Lines
shunt = find_shunt_admittance(numLines, phase_distance, conductor, line_lengths, w, j);

%Find the Diagonal Elements of the Ybus
diagMatrix = find_diag_elements(line_bus_connections, Y_lines, shunt, N, numLines, TX, TX_connections, numTX);

%Find Outside Diaglonal Elements of Ybus
off_diag = find_off_diag_elements(line_bus_connections, Y_lines, numLines, N, TX, TX_connections, numTX);

%Find the Ybus
Ybus = find_Ybus_matrix(diagMatrix, off_diag, bus_connections, N);

%Print Result
% bus_table_label_ex = "";
% for i = 1:N
%     single_bus_table_label = "Bus " + num2str(i);
%     bus_table_label_ex = [bus_table_label_ex single_bus_table_label];
% end
% bus_table_label = bus_table_label_ex(2:N+1);
% bus_table_label = convertStringsToChars(bus_table_label);
% disp(bus_table_label)
disp('Milestone 1:')
disp(' ')
disp("Ybus: ")
Ybus_table = array2table(Ybus);
disp(Ybus_table)

%Milestone 2 & 3--------------------------------------------------------

%Bus Power Information
P = [0 0 0 0 1 1.1 1]; 
Q = [0 0 0 0 .65 .50 .70]; 

%Flat Start Information
V_o = [1.0 1.0 1.0 1.0 1.0 1.0 1.0];
delta = [0 0 0 0 0 0 0];

%The amount of iterations to do
number = 3;

%The convergence criteria in pu
criteria = 0.0001;

%Set iteration counter
counter = 0;

%Newton 1, Fast Decoupled 2, DC Power 3
flow_type = 1;

disp(' ')
disp('Milestone 2: ')
disp(' ')

%-----------Solving for Iterations-----------%

switch flow_type
    case 1
        %funciton for Newton Rasp
        cap_set = 0;
        newton_rasp_power_flow(Ybus, V_o, delta, P, Q, N, criteria, counter, bus_type, Y_lines, line_bus_connections, numLines, flow_type, cap_set, number);
    case 2
        %function for fast decoupled 
        fast_decoupled_power_flow(Ybus, V_o, delta, P, Q, N, criteria, counter, bus_type, Y_lines, line_bus_connections, numLines, flow_type, number);
    case 3
        %function for DC Power Flow
        
end


%------FUNCTIONS------%

function Deq = find_Deq(data)
    Deq = (data.Dab*data.Dbc*data.Dca)^(1/3);
end

function D_SL = find_D_SL(cond) 
    if (cond.nb ==1)
       D_SL = cond.GMR; 
    end
    if (cond.nb == 2) 
        D_SL = sqrt(cond.GMR * cond.d);
    end 
    if(cond.nb == 3)
       D_SL = (cond.GMR * (cond.d)^2)^(1/3);
    end
    if (cond.nb == 4)
       D_SL = (1.091 *((cond.GMR * (cond.d)^3)^(1/4)));
    end
end 

function R = find_resistance(cond, length) 
    %length should be in miles
    R = (cond.r / cond.nb) * length;
end

function X = find_reactance(w, Deq, D_SL,length)
    %Length should be in meters
    new_length = length * 1609.34;
    X = w * (2e-7) * log(Deq/D_SL) * new_length;
end

function Y = calc_shunt_line(length, D_SC, Deq, j, w)
    
    Y = ((j * w * 2 * pi * (8.8541878e-12)) / (log(Deq/D_SC))) * 1609.34 * length;

end 

function [N, numLines] = find_lines_nodes()
    
%     prompt = {'How Many Nodes in the System? : ', 'How Many Lines in the System? : '};
%     dlgtitle = 'General System Data Collection';
%     dims = [1 35];
%     answer = inputdlg(prompt, dlgtitle,dims);
%     N = str2num(answer{1});
%     numLines = str2num(answer{2});
    N = 7;
    numLines = 7;
    
    
end

function bus_type = find_bus_types()
%     prompt = {'Label the Bus Types (1) Slack (2) PV (0) Other: : '};
%     dlgtitle = 'General System Data Collection';
%     dims = [1 35];
%     answer = inputdlg(prompt, dlgtitle,dims);
%     bus_type = str2num(answer{1});

    bus_type = [1 0 0 2 0 0 0];
end

function [line_lengths, phase_distance] = find_line_lengths(numLines)
%     prompt = {'Enter Each Line Length (in miles) Seperated by a Space: '};
%     dlgtitle = 'Line Length Collection';
%     dims = [1 35];
%     answer = inputdlg(prompt, dlgtitle,dims);
%     string = answer;
%     line_lengths = str2num(string{1});
%     
%     prompt = {'Enter the distance from Phase A to B (in feet): ', 'Enter the distance from Phase B to C (in feet): ', 'Enter the distance from Phase C to A (in feet): '};
%     dlgtitle = 'Phase Distance Data Collection';
%     dims = [1 35];
%     answer = inputdlg(prompt, dlgtitle,dims);
%     phase_distance.Dab = str2num(answer{1});
%     phase_distance.Dbc = str2num(answer{2});
%     phase_distance.Dca = str2num(answer{3});

    line_lengths = zeros(1,numLines);
    line_lengths(1) = 10;
    line_lengths(2) = 25;
    line_lengths(3) = 20;
    line_lengths(4) = 10;
    line_lengths(5) = 35;
    phase_distance.Dab = 19.5;
    phase_distance.Dbc = 19.5;
    phase_distance.Dca = 39;
    
    
end

function conductor = find_conductor_info()
%     prompt = {'What is resistance (r)(ohm/mi)? : ', 'What is the Geometric Mean Radius (GMR)(ft)? : ', 'What is the diameter (d)(ft)? : ', 'What is distance between subconductors (d)(ft)? : ', 'How many subconductors in the bundle? : '};
%     dlgtitle = 'Conductor Type Data';
%     dims = [1 100];
%     definput = {'', ''};
%     answer = inputdlg(prompt, dlgtitle,dims);
%     conductor.r = str2num(answer{1});
%     conductor.GMR = str2num(answer{2});
%     conductor.diam = str2num(answer{3});
%     conductor.d = str2num(answer{4});
%     conductor.nb = str2num(answer{5});
    
    conductor.r = 0.385; %ohm/mi
    conductor.GMR = 0.0217; %ft
    conductor.diam = 0.642/12; %ft 
    conductor.d = 1.5; %ft
    conductor.nb = 2; 
end

function [X, R] = get_X_R_pu()
    prompt = {'Enter Each Line Resistance (R in pu) Seperated by a Space: ', 'Enter Each Line Reactance (X in pu) Seperated by a Space: '};
    dlgtitle = 'Per Unit Resistance Collection';
    dims = [1 50];
    answer = inputdlg(prompt, dlgtitle,dims);
    string = answer;
    R = str2num(string{1});
    X = str2num(string{2});

end 

function Y_lines = find_line_admittance(w, j, numLines, phase_distance, conductor, line_lengths, TX, numTX, TX_lines)
    
%     prompt = {'Type 1 if you have the per unit X and R already, Type 2 if you have conductor information to input: '};
%     dlgtitle = 'Line Admittance Data Collection';
%     dims = [1 35];
%     answer = inputdlg(prompt, dlgtitle,dims);
%     type = str2num(answer{1});
% 
%     if (type == 1)
%         [X, R] = get_X_R_pu();
%         Y_lines = find_line_admittances_with_pu(X, R, numLines);
%         line_lengths = 0;
%         phase_distance = 0; 
%         conductor = 0;
%     else 
%         %Find Length of Lines
%         [line_lengths, phase_distance] = find_line_lengths();
% 
%         %Find Conductor Information
%         conductor = find_conductor_info();
%         
%         Y_lines = find_line_admittances_with_line_data(phase_distance, conductor, line_lengths, w, j, numLines);
%     end

    Y_lines = find_line_admittances_with_line_data(phase_distance, conductor, line_lengths, w, j, numLines);
    for i = 1:numTX
        index = TX_lines(i);
        Y_lines(index) = TX(i);
    end
end

function Y_lines = find_line_admittances_with_pu(X, R, numLines) 

    Y_lines = zeros(1, numLines);
    for i = 1:numLines
       Y_lines(i) = 1/(R(i) + j*X(i));    
    end

end

function Ypu = find_line_admittances_with_line_data(phase_distance, conductor, line_lengths, w, j, numLines)
    %Find Deq
    Deq = find_Deq(phase_distance);
    
    %Find Equivalent GMR
    D_SL = find_D_SL(conductor);

    %Find resistance
    R = zeros(1,numLines);
    for i = 1:numLines
        R(i) = find_resistance(conductor, line_lengths(i));
    end

    %printR_results(R1, R2, R3, R4, R5);

    %Find Reactances
    X = zeros(1,numLines);
    for k = 1:numLines
        X(k) = find_reactance(w, Deq, D_SL, line_lengths(k));
    end

    %Build Impedances
    Z = zeros(1,numLines);
    for q = 1:numLines
        Z(q) = R(q) + (j * X(q));
    end

    
    %Get System Information for Zbase Calculation
%     prompt = {'What is the Voltage Base (kV) of the System? : ', 'What is the Apparent Power (S MVA) the System? : '};
%     dlgtitle = 'General System Data Collection';
%     dims = [1 35];
%     answer = inputdlg(prompt, dlgtitle,dims);
%     V_sys = str2num(answer{1});
%     S_sys = str2num(answer{2});
    
    V_sys = 230;
    S_sys = 100;
    
    Zbase = (V_sys * 1000)^2 / (S_sys * 1e6);
    
    %Per Unit of Impedance
    Zpu = zeros(1,numLines);
    for p = 1:numLines
        Zpu(p) = Z(p) / Zbase;
    end
    
    %Convert to Admittance
    Ypu = zeros(1,numLines);
    for t = 1:numLines
        if(Zpu(t) ~= 0)
            Ypu(t) = (1/Zpu(t)); 
        else
            Ypu(t) = 0 + i*0;
        end
    end    
end

function bus_connections = find_bus_connections(N)
    
%     bus_connections = zeros(N,N);
%     string1 = 'Which Buses are Connected to Bus ';
%     string2 = ' Put in Order 1 for Connected and 0 for Not, Space Inbetween Each: ';
%     for i = 1:N
%         string3 = num2str(i);
%         string = strcat(string1, string2, string3);
%         prompt = {string};
%         dlgtitle = 'Bus Connection Data Collection';
%         dims = [1 50];
%         answer = inputdlg(prompt, dlgtitle,dims);
%         bus_connections(i,:) = str2num(answer{1});
%     end

    bus_connections = [1 1 0 0 0 0 0;
                       1 1 0 0 1 0 0;
                       0 0 1 1 1 1 0;
                       0 0 1 1 0 0 0;
                       0 1 1 0 1 0 1;
                       0 0 1 0 0 1 1;
                       0 0 0 0 1 1 1];

end

function line_bus_connections = find_line_connections(N, numLines)
%Fill In Matrix With Which Lines are Connected to Which Buses

    %Define Matrix of Line to Bus connections
%     line_bus_connections = zeros(N, numLines);
% 
%     for i = 1:N 
%        for k = 1:numLines
%           ansCon = input(sprintf("Is Line %d Connected to Bus %d ? y/n : ", k, i), 's'); 
%           if (ansCon == 'y') 
%              line_bus_connections(i,k) = 1; 
%           end
%        end
%     end

    line_bus_connections = [0 0 0 0 0 1 0;
                            1 0 0 0 0 1 0;
                            0 1 1 0 0 0 1;
                            0 0 0 0 0 0 1;
                            1 1 0 1 0 0 0;
                            0 0 1 0 1 0 0;
                            0 0 0 1 1 0 0];
end

function B = get_B_pu(numLines)
    prompt = {'Enter Each Line Shunt Admittance (B in pu) Seperated by a Space: '};
    dlgtitle = 'Shunt Admittance Collection';
    dims = [1 50];
    answer = inputdlg(prompt, dlgtitle,dims);
    string = answer;
    B_not = str2num(string{1});
    B = zeros(1,numLines);
    for i = 1:numLines
        B(i) = B_not(i) * 0.5;
    end
end

function D_SC = find_D_SC(cond)
    D_SC = sqrt((cond.diam/2) * cond.d);
end

function Y_shunt_lines = find_shunt_admittances_with_line_data(phase_distance, conductor, line_lengths, j, w, numLines)
    Deq = find_Deq(phase_distance);
    D_SC = find_D_SC(conductor);
    
    Y_shunt_lines = zeros(1,numLines);
    for i = 1:numLines
        Y_shunt_lines(i) = calc_shunt_line(line_lengths(i), D_SC, Deq, j, w);
    end
    
    Z_shunt_lines = zeros(1,numLines);
    for j = 1:numLines
       Z_shunt_lines(j) = (1/Y_shunt_lines(j));
    end
    
    V_sys = 230;
    S_sys = 100;
    
    Zbase = (V_sys * 1000)^2 / (S_sys * 1e6);
    
    %Per Unit of Impedance
    Zpu = zeros(1,numLines);
    for p = 1:numLines
        Zpu(p) = Z_shunt_lines(p) / Zbase;
    end
    
    for k = 1:numLines
       Y_shunt_lines(k) = (1/Zpu(k));
    end
    
end

function Y_shunt = find_shunt_admittance(numLines, phase_distance, conductor, line_lengths, w, j)
%     prompt = {'Type 1 if you have the per unit B already, Type 2 if you want to use conductor information: '};
%     dlgtitle = 'Shunt Admittance Data Collection';
%     dims = [1 35];
%     answer = inputdlg(prompt, dlgtitle,dims);
%     type = str2num(answer{1});
% 
%     if (type == 1)
%         Y_shunt = get_B_pu(numLines);
%     else 
%         Y_shunt = find_shunt_admittances_with_line_data(phase_distance, conductor, line_lengths, w, j, numLines);
%     end

    Y_shunt = find_shunt_admittances_with_line_data(phase_distance, conductor, line_lengths, w, j, numLines);
end

function [TX, TX_connections, numTX, TX_lines] = find_transformers()

%     prompt = {'Type How Many Transformers There? '};
%     dlgtitle = 'Number of Transformers';
%     dims = [1 35];
%     answer = inputdlg(prompt, dlgtitle,dims);
%     numTX = str2num(answer{1});
%     
%     TX = [1, numTX];
%     TX_connections = [2, numTX];
%     
%     if (numTX > 0) 
%         for i = 1:numTX
%             prompt = {'Type 1 if You Know the Impedance Already: '};
%             dlgtitle = 'Number of Transformers';
%             dims = [1 35];
%             answer = inputdlg(prompt, dlgtitle,dims);
%             ansTX = str2num(answer{1});
%             
%             if(ansTX == 1)
%                 prompt = {'Type Real Part then Space then Complex: '};
%                 dlgtitle = 'Transformer Input';
%                 dims = [1 35];
%                 answer = inputdlg(prompt, dlgtitle,dims);
%                 realTX = str2num(answer{1});
%                 complexTX = str2num(answer{2});
%             else
%                 prompt = {'What is MVA base of TX: ', 'What is MVA base of System: ', 'What is current pu: ', 'What is x/r Ratio: '};
%                 dlgtitle = 'Transformer Calculation';
%                 dims = [1 35];
%                 answer = inputdlg(prompt, dlgtitle,dims);
%                 MVA_TX = str2num(answer{1});
%                 MVA_base = str2num(answer{2});
%                 pu_old = str2num(answer{3});
%                 xr = str2num(answer{4});
%                 
%                 realTX = (pu_old) * (MVA_base / MVA_TX);
%                 complexTX = atan(xr);
%             end
%             
%             prompt = {'Type First Bus Then Space Then Second Bus: '};
%             dlgtitle = 'Transformer Bus Connections';
%             dims = [1 35];
%             answer = inputdlg(prompt, dlgtitle,dims);
%             bus1 = str2num(answer{1});
%             bus2 = str2num(answer{2});
%             
%             TX(i) = realTX + complexTX;
%             TX_connections(1,i) = bus1;
%             TX_connections(2,i) = bus2;
%             
%         end
%     end
    j = 1i;

    TX = [(1.463-j*14.63) (1.582-j*18.98)];
    TX_connections = [1 3; 2 4];
    TX_lines = [6 7];
    numTX = 2;
    
end

function diagMatrix = find_diag_elements(connection, Y_lines, shunt, N, numLines, TX, TX_connections, numTX)

    j = 1i;

    matrix = zeros(N, 1);
    sum = 0;
    for i = 1:N
        bus_info = connection(i,:);
        element1 = (bus_info .* Y_lines);
        element2 = (bus_info .* (j*shunt));
        for k = 1:numLines
            sum = sum + element1(k) + element2(k);
        end
        matrix(i) = sum;
        sum = 0;
    end
    
%     if(numTX > 0)        
%         for q = 1:numTX
%             bus = TX_connections(1,q);
%             matrix(bus) = matrix(bus) + TX(q);
%         end
%     end    
    diagMatrix = matrix;

end

function off_diag = find_off_diag_elements(line_bus_connections, Y_lines, numLines, N, TX, TX_connections, numTX)
    
    off_diag = zeros(N,N);

    for i = 1:numLines
        count = 0;
        while count < 1
            for k = 1:N
                if(line_bus_connections(k,i)==1)
                    bus1 = k;
                    count = count + 1;
                end
            end
        end
        
        count = 0;
        while count < 1
            for h = 1:N
                if(line_bus_connections(h,i)==1 && h ~= bus1)
                    bus2 = h;
                    count = count + 1;
                end
            end
        end
        
        off_diag(bus1, bus2) = -1 * Y_lines(i);
        off_diag(bus2, bus1) = -1 * Y_lines(i);
        
        if(numTX > 0)        
            for q = 1:numTX
                if(TX_connections(1,q) == bus1 && TX_connections(2,q) == bus2)
                    off_diag(bus1, bus2) = off_diag(bus1, bus2) + TX(q);
                    off_diag(bus2, bus1) = off_diag(bus2, bus1) + TX(q);
                end
            end
        end
        
    end
    
end

function Ybus = find_Ybus_matrix(diagMatrix, off_diag, bus_connections, N)
    Ybus = zeros(N,N);
    for i = 1:N
       for k = 1:N
          if(k==i)
             Ybus(k,k) = diagMatrix(k); 
          else 
             Ybus(i,k) = off_diag(i,k); 
          end
       end
    end
    
    Ybus = Ybus .* bus_connections;
    
end 

function [real, imag] = convert_to_polar(mag, ang)
    [real, imag] = cart2pol(ang * (pi/180), mag);
    %num = real + i*imag;
end

function [mismatch, bus_type] = find_mismatch_matrix(Ybus, V_o, delta, P, Q, N, bus_type)
    disp('hello')
    result = 0;
    mismatch_P = zeros(N, 1);
    
    for k = 1:N
        for n = 1:N
            num = abs(Ybus(k,n)) * V_o(n) * cos(delta(k) - delta(n) - angle(Ybus(k,n)));
            result = result + num; 
        end
        disp('result:')
        disp(result)
            mismatch_P(k,1) = V_o(k) * result;
    end
        
    result = 0;
    mismatch_Q = zeros(N, 1);
    
    for k = 1:N
        for n = 1:N
            num = abs(Ybus(k,n)) * V_o(n) * sin(delta(k) - delta(n) - angle(Ybus(k,n)));
            result = result + num;
        end
            mismatch_Q(k,1) = V_o(k) * result;
    end
    
    mismatch_x = [mismatch_P ; mismatch_Q];
    
    expected = zeros(N,1);
    for i = 1:N
        expected(i, 1) = P(i);
    end
    for y = N+1:N*2
        expected(y, 1) = Q(y-N);
    end
    
    m = expected - mismatch_x;
    
    %Find slack bus 
    for i = 1:N
       if (bus_type(i) == 1)
          %Delete row and column for slack bus
           m(i, :) = [];
           m((i+N-1), :) = [];
       end
    end
    
    count = 2;
    
    %Find PV and delete the row and column for each
    for q = 1:N
       if(bus_type(q) == 2)
           m((q-count+N), :) = [];
       end
       count = count + 1;
    end
    
    mismatch = m;
    
end

function J1_kn = find_J1_kn_element(V_o, Ybus, delta, k, n)
    
    J1_kn = V_o(k) * abs(Ybus(k,n)) * V_o(n) * sin(delta(k) - delta(n) - angle(Ybus(k,n)));
    
end 

function J2_kn = find_J2_kn_element(V_o, Ybus, delta, k, n)
    
    J2_kn = V_o(k) * abs(Ybus(k,n)) * cos(delta(k) - delta(n) - angle(Ybus(k,n)));
    
end 

function J3_kn = find_J3_kn_element(V_o, Ybus, delta, k, n)
    
    J3_kn = -1 * V_o(k) * abs(Ybus(k,n)) * V_o(n) * cos(delta(k) - delta(n) - angle(Ybus(k,n)));
    
end 

function J4_kn = find_J4_kn_element(V_o, Ybus, delta, k, n)
    
    J4_kn = V_o(k) * abs(Ybus(k,n)) * sin(delta(k) - delta(n) - angle(Ybus(k,n)));
    
end 

function J1_kk = find_J1_kk_element(V_o, Ybus, delta, k, N)
    result = 0;
    for n = 1:N
        
        num = abs(Ybus(k,n)) * V_o(n) * sin(delta(k) - delta(n) - angle(Ybus(k,n)));
        if n == k
            num = 0;
        end
        result = result + num;
    end
    
    J1_kk = -1 * V_o(k) * result;
    
end 

function J2_kk = find_J2_kk_element(V_o, Ybus, delta, k, N)
    result = 0;
    for n = 1:N
        num = abs(Ybus(k,n)) * V_o(n) * cos(delta(k) - delta(n) - angle(Ybus(k,n)));
        result = result + num;
    end
    
    J2_kk = (V_o(k) * abs(Ybus(k,k)) * cos(angle(Ybus(k,k)))) + result;
    
end 

function J3_kk = find_J3_kk_element(V_o, Ybus, delta, k, N)
    result = 0;
    for n = 1:N
        num = abs(Ybus(k,n)) * V_o(n) * cos(delta(k) - delta(n) - angle(Ybus(k,n)));
        if n == k
            num = 0;
        end
        result = result + num;
    end
    
    J3_kk = V_o(k) * result;
    
end 

function J4_kk = find_J4_kk_element(V_o, Ybus, delta, k, N)
    result = 0;
    for n = 1:N
        num = abs(Ybus(k,n)) * V_o(n) * sin(delta(k) - delta(n) - angle(Ybus(k,n)));
        result = result + num;
    end
    
    J4_kk = (-1 * V_o(k) * abs(Ybus(k,k)) * sin(angle(Ybus(k,k)))) + result;
    
end 

function J1 = find_J1(V_o, Ybus, delta, N)
    
    J1 = zeros(N,N);
    
    for k = 1:N
        for n = 1:N
           if k == n 
               J1(k,k) = find_J1_kk_element(V_o, Ybus, delta, k, N);
           else
               J1(k,n) = find_J1_kn_element(V_o, Ybus, delta, k, n);
           end
        end
    end 
    
    
end

function J2 = find_J2(V_o, Ybus, delta, N)
    
    J2 = zeros(N,N);
    
    for k = 1:N
        for n = 1:N
           if k == n 
               J2(k,k) = find_J2_kk_element(V_o, Ybus, delta, k, N);
           else
               J2(k,n) = find_J2_kn_element(V_o, Ybus, delta, k, n);
           end
        end
    end 
    
    
end

function J3 = find_J3(V_o, Ybus, delta, N)
    
    J3 = zeros(N,N);
    
    for k = 1:N
        for n = 1:N
           if k == n 
               J3(k,k) = find_J3_kk_element(V_o, Ybus, delta, k, N);
           else
               J3(k,n) = find_J3_kn_element(V_o, Ybus, delta, k, n);
           end
        end
    end 
    
    
end

function J4 = find_J4(V_o, Ybus, delta, N)
    
    J4 = zeros(N,N);
    
    for k = 1:N
        for n = 1:N
           if k == n 
               J4(k,k) = find_J4_kk_element(V_o, Ybus, delta, k, N);
           else
               J4(k,n) = find_J4_kn_element(V_o, Ybus, delta, k, n);
           end
        end
    end 
    
    
end

function [J, delta_y_new] = find_jacobian(V_o, Ybus, delta, N, bus_type, flow_type, delta_y) 

    if(flow_type == 1)
        J1 = find_J1(V_o, Ybus, delta, N);
        J2 = find_J2(V_o, Ybus, delta, N);
        J3 = find_J3(V_o, Ybus, delta, N);
        J4 = find_J4(V_o, Ybus, delta, N);

        J = [J1 J2; J3 J4];
        
        J_t = array2table(J);
    disp(J_t)

        %Find slack bus 
        for i = 1:N
           if (bus_type(i) == 1)
              %Delete row and column for slack bus
               J(i, :) = [];
               delta_y(i, :) = [];
               J(:, i) = [];
               J((i+N-1), :) = [];
               delta_y(i+N-1, :) = [];
               J(:, (i+N-1)) = [];
           end
        end

        count = 1;

        %Find PV and delete the row and column for each
        for q = 1:N
           if(bus_type(q) == 2)
               J((q+N-2), :) = [];
               delta_y((q+N-2), :) = [];
               J(:, (q+N-2)) = [];
           end
           count = count + 1;
        end
    end
    
    
    if(flow_type == 2)
        
        J1 = find_J1(V_o, Ybus, delta, N);
        J4 = find_J4(V_o, Ybus, delta, N);

        J = [J1; J4];
        


        %Find slack bus 
        for i = 1:N
           if (bus_type(i) == 1)
              %Delete row and column for slack bus
               J(i, :) = [];
               delta_y(i, :) = [];
               J(:, i) = [];
           end
        end

        count = 2;

        %Find PV and delete the row and column for each
        for q = 1:N
           if(bus_type(q) == 2)
               J((q-count+N), :) = [];
               delta_y((q-count+N), :) = [];
               J(:, (q-count+N)) = [];
           end
           count = count + 1;
        end
    end
    
    delta_y_new = delta_y;
    
    

end

function [V_delta_mismatch, V_delta_mismatch_new, newV, newDelta] = find_V_delta_mismatch(mismatch, J, N, V_o, delta, bus_type, delta_y)
    newV = zeros(1,N);
    newDelta = zeros(1,N);
    V_delta_mismatch_new = zeros(1, N*2);
    bus_type = [bus_type bus_type];
    
    count = 0;
    
    V_delta_mismatch = inv(J) * mismatch;
    disp('V_delta_mismatch')
    disp(V_delta_mismatch)
    for q = 1:N*2
        if(bus_type(q) == 1)
            
           V_delta_mismatch_new(q) = 0;
           count = count - 1;
        elseif(bus_type(q) == 2)
           V_delta_mismatch_new(q) = 0;
           count = count - 1;
        else
            V_delta_mismatch_new(q) = V_delta_mismatch(q+count,1);
        end
    end
    
    for i = 1:N
        newV(i) = V_delta_mismatch_new(i) + V_o(i);
    end
    for k = 1:N
       newDelta(k) = V_delta_mismatch_new(k+N) + delta(k);
    end
    
end 

function met = find_convergance(power, criteria, N)
    mettemp = true;
    %disp(mismatch)
    for i = 1:N*2
        if(abs(power(i)) <= criteria)
        else
            %disp(['Failing Component: ' num2str(i)]);
            %disp(power(i))
            mettemp = false;
        end
    end
    met = mettemp;
end

function print_results(J, delta_y, N, newV, newDelta, counter)
    
    delta_y = delta_y.';

    disp("For Iteration " + counter)
    disp('')
    
    disp("Jacobian: ")
    J_table = array2table(J);
    disp(J_table)
   
    disp("The Real Power Mismatch is: ")
    realP = delta_y(1:N);
    real_p_table = array2table(realP);
    disp(real_p_table)
    disp("The Reactive Power Mismatch is: ")
    reactiveQ = delta_y(N+1:N*2);
    reactive_p_table = array2table(reactiveQ);
    disp(reactive_p_table)
    disp('Voltage for Next Iteration:')
    newV_table = array2table(newV);
    disp(newV_table)
    disp('Angles for Next Iteration:')
    newDelta_table = array2table(newDelta);
    disp(newDelta_table)
   

%     disp("Real Power from Each Bus: ")
%     P_table = array2table(P_x);
%     disp(P_table)
%     disp("Reactive Power from Each Bus: ")
%     Q_table = array2table(Q_x);
%     disp(Q_table)
%     disp("Real System Losses: " + real_loss)
%     disp("Reactive System Losses: " + reactive_loss)
%     disp("Magnitude Currents: ")
%     disp(abs(currents))
%     disp("Angle of Currents: ")
%     disp(angle(currents))

    
end

function [newV, newDelta, newcounter, met] = iteration(Ybus, V_o, delta, P, Q, N, criteria, counter, bus_type, Y_lines, line_bus_connections, numLines, flow_type)
        
        for l = 1:N
           delta(l) = delta(l)*(pi/180); 
        end

        if(flow_type==3)
        %DC Power Flow
            %Find Susceptance
            %sus_matrix = find_suseptance_matrix()
            %Invert Matrix
        end
        
        data = zeros(1,N);
        
        %Compute delta(y(i)) = [delta(P(i)) delta(Q(i))]
        [newP, newQ, P_x, Q_x] = find_P_Q(Ybus, V_o, delta, N, P, Q);
        
        %Define delta(y(i)) from power mismatch
        delta_y = [P_x.'; Q_x.'];
        %delta_y = [newP; newQ];
        disp('delta y')
        disp(delta_y)
        
        %Find the Jacobian
        [J, delta_y_new] = find_jacobian(V_o, Ybus, delta, N, bus_type, flow_type, delta_y);
        
        %[mismatch, bus_type] = find_mismatch_matrix(Ybus, V_o, delta, P, Q, N, bus_type);

        %Find delta and voltage mismatch
        [V_delta_mismatch, mismatch_new, newV, newDelta] = find_V_delta_mismatch(delta_y_new, J, N, V_o, delta, bus_type, delta_y);
                
%         for i = 1:N
%             data(i) = newV(i) + newDelta(i);
%         end

        %currents = find_current_directions(Y_lines, data, N, line_bus_connections, numLines);
        
        power = [newP newQ];
 
        [real_loss, reactive_loss] = find_losses(P_x, Q_x, N);
        
        met = find_convergance(delta_y, criteria, N);
        
        print_results(J, delta_y, N, newV, newDelta, counter);
        
        newcounter = counter+1;
end

function [newP, newQ, P_x, Q_x] = find_P_Q(Ybus, V_o, delta, N, P, Q)
    
    newP = zeros(N,1);
    newQ = zeros(N,1);
    
    disp('P')
    disp(P)
    disp('Q')
    disp(Q)
    disp('V_o')
    disp(V_o)
    disp('delta')
    disp(delta)

       
    for k = 1:N
        result = 0; 
        for n = 1:N
%             disp('delta k')
%             disp(delta(k))
%             disp('delta n')
%             disp(delta(n))
            num = abs(Ybus(k,n)) * V_o(n) * cos(delta(k) - delta(n) - angle(Ybus(k,n)));
            result = result + num; 
        end
            disp('result P')
            disp(result)
            newP(k,1) = V_o(k) * result;
    end
   
    for q = 1:N
        result = 0;
        for w = 1:N
            num = abs(Ybus(q,w)) * V_o(w) * sin(delta(q) - delta(w) - angle(Ybus(q,w)));
            result = result + num;
        end
            disp('result Q')
            disp(result)
            newQ(q,1) = V_o(q) * result;
    end

    
    P_x = newP.';
    disp('P')
    disp(P)
    disp('P mismatch')
    disp(P_x)
    Q_x = newQ.';
    disp('Q')
    disp(Q)
    disp('Q mismatch')
    disp(Q_x)
    newP = P - P_x;
    newQ = Q - Q_x;
    disp('newP')
    disp(newP)
    
end

function [real_loss, reactive_loss] = find_losses(P_x, Q_x, N)

    real_loss = 0;
    reactive_loss = 0;

    for i = 1:N
       real_loss = real_loss + P_x(i); 
       reactive_loss = reactive_loss + Q_x(i);
    end

end

function currents = find_current_directions(Ylines, data, N, line_bus_connections, numLines)

    currents = zeros(1,N);
    %disp(data)
    %disp("Ylines: ")
    %disp(Ylines)

    for i = 1:numLines
        count = 0;
        while count < 1
            for k = 1:N
                if(line_bus_connections(k,i)==1)
                    bus1 = k;
                    count = count + 1;
                end
            end
        end
        
        count = 0;
        while count < 1
            for h = 1:N
                if(line_bus_connections(h,i)==1 && h ~= bus1)
                    bus2 = h;
                    count = count + 1;
                end
            end
        end
        
        currents(i) = find_current(data(bus1), data(bus2), Ylines(i)); %1-2
        %disp(currents(i))
    end
end 

function I = find_current(V1, V2, Y) 
    I = (V1-V2)*Y;
end 

function Q = add_cap(Q_start, var)
    Q = Q_start + var;
end

function newton_rasp_power_flow(Ybus, V_o, delta, P, Q, N, criteria, counter, bus_type, Y_lines, line_bus_connections, numLines, flow_type, cap_set, number)
    
    %Add capactior if needed
    if(cap_set == 1)
        disp("Turning on Capacitor")
        bus_add_cap = 7;
        var = .1;
        Q(bus_add_cap) = add_cap(Q(bus_add_cap), var);
        cap_set = 0;
    end
    
    bus_add_cap = 0;
    
    %First Iteration from Flat Start
    [newV, newDelta, newcounter, met] = iteration(Ybus, V_o, delta, P, Q, N, criteria, counter, bus_type, Y_lines, line_bus_connections, numLines, flow_type);
    disp("Converge?: " + met)
    
    disp(' ')
    disp('Milestone 3: ')
    disp(' ')

    %Continue until convergance or max iterations
    while(newcounter < number && met == false)
        [newV, newDelta, newcounter, met] = iteration(Ybus, newV, newDelta, P, Q, N, criteria, newcounter, bus_type, Y_lines, line_bus_connections, numLines, flow_type);
        disp("Converge?: " + met)
    end
    
    for y = 1:N
        if(bus_type(y) == 2)
            if(Q(y) > 1.75)
                bus_type(y) = 0;
                setQ = y;
                cap_set = 1;
                %Set the Q value of the bus
                Q(setQ) = 1.75;
            end
        end
    end
    
        %Return to compare with cap bank
        if (cap_set == 1)
            disp("Running Newton Raspson with Capacitor Bank Incorporated")
            newton_rasp_power_flow(Ybus, V_o, delta, P, Q, N, criteria, counter, bus_type, Y_lines, line_bus_connections, numLines, flow_type, cap_set, number);
        end 
   
end

function fast_decoupled_power_flow(Ybus, V_o, delta, P, Q, N, criteria, counter, bus_type, Y_lines, line_bus_connections, numLines, flow_type, cap_set, number)
   
    %First Iteration from Flat Start
    [newV, newDelta, newcounter, met] = iteration(Ybus, V_o, delta, P, Q, N, criteria, counter, bus_type, Y_lines, line_bus_connections, numLines, flow_type);
    disp("Converge?: " + met)

    %Continue until convergance or max iterations
    while(newcounter < number && met == false)
        [newV, newDelta, newcounter, met] = iteration(Ybus, newV, newDelta, P, Q, N, criteria, newcounter, bus_type, Y_lines, line_bus_connections, numLines, flow_type);
        disp("Converge?: " + met)
    end
   
end

function [n_conductor1, n_conductor2] = find_neutral_cond_info()
    n_conductor1.r = 0.385; %ohm/mi
    n_conductor1.GMR = 0.0217; %ft
    n_conductor1.diam = 0.642/12; %ft 
    n_conductor1.d = 1.5; %ft
    n_conductor1.nb = 2; 
    
    n_conductor2.r = 0.385; %ohm/mi
    n_conductor2.GMR = 0.0217; %ft
    n_conductor2.diam = 0.642/12; %ft 
    n_conductor2.d = 1.5; %ft
    n_conductor2.nb = 2; 
end

%function [pos_gen_matrix, neg_gen_matrix, zero_gen_matrix] = find generator_sequence_matrices()

%end

%Milestone 5---------------------------------------------------------
function [Zbus_pos, Zbus_neg, Zbus_zero] = find_Zbus_for_sequences(numLines, N, line_bus_connections, bus_connections, Y_lines, bus_types)
    
    numGen = 0;
    for i = 1:N
       if(bus_types(i) == 1 || bus_types(i) == 2)
          numGen = numGen + 1; 
       end
    end
    numLines = numLines + numGen;
    
    bus_connections_pos = find_bus_connections_for_pos_seq(bus_connections);
    line_bus_connections_pos = find_line_bus_connections_pos_seq(line_bus_connections);
    Y_lines_pos = find_Y_lines_for_pos_seq(Y_lines, numLines);

    diagMatrix = find_diag_elements(line_bus_connections_pos, Y_lines_pos, N, numLines);
    off_diag = find_off_diag_elements(line_bus_connections_pos, Y_lines_pos, numLines, N);
    Ybus = find_Ybus_matrix(diagMatrix, off_diag, bus_connections_pos, N);
%     Ybus_table = array2table(Ybus);
%     disp('Positive Sequence Network Ybus')
%     disp(Ybus_table)
    Zbus_pos = inv(Ybus);
    Zbus_table = array2table(Zbus);
    disp('Positive Sequence Network Zbus')
    disp(Zbus_table)

    bus_connections_zero = find_bus_connections_for_zero_seq(bus_connections);
    line_bus_connections_zero = find_line_bus_connections_zero_seq(line_bus_connections);
    Y_lines_zero = find_Y_lines_for_zero_seq(Y_lines, numLines);

    diagMatrix = find_diag_elements(line_bus_connections_zero, Y_lines_zero, N, numLines);
    off_diag = find_off_diag_elements(line_bus_connections_zero, Y_lines_zero, numLines, N);
    Ybus = find_Ybus_matrix(diagMatrix, off_diag, bus_connections_zero, N);
%     Ybus_table = array2table(Ybus);
%     disp('Zero Sequence Network Ybus')
%     disp(Ybus_table)
    Zbus_zero = inv(Ybus);
    Zbus_table = array2table(Zbus);
    disp('Zero Sequence Network Zbus')
    disp(Zbus_table)

    bus_connections_neg = find_bus_connections_for_neg_seq(bus_connections);
    line_bus_connections_neg = find_line_bus_connections_neg_seq(line_bus_connections);
    Y_lines_neg = find_Y_lines_for_neg_seq(Y_lines, numLines);

    diagMatrix = find_diag_elements(line_bus_connections_neg, Y_lines_neg, N, numLines);
    off_diag = find_off_diag_elements(line_bus_connections_neg, Y_lines_neg, numLines, N);
    Ybus = find_Ybus_matrix(diagMatrix, off_diag, bus_connections_neg, N);
%     Ybus_table = array2table(Ybus);
%     disp('Negative Sequence Network Ybus')
%     disp(Ybus_table)
    Zbus_neg = inv(Ybus);
    Zbus_table = array2table(Zbus);
    disp('Negative Sequence Network Zbus')
    disp(Zbus_table)
end

function bus_connections_pos = find_bus_connections_for_pos_seq(bus_connections)
    bus_connections_pos = bus_connections;
end
function line_bus_connections_pos = find_line_bus_connections_pos_seq(line_bus_connections)
    line_bus_connections_pos = line_bus_connections;
end
function Y_lines_pos = find_Y_lines_for_pos_seq(Y_lines, numLines)
end

function bus_connections_neg = find_bus_connections_for_neg_seq(bus_connections)
    bus_connections_neg = bus_connections;
end
function line_bus_connections_neg = find_line_bus_connections_neg_seq(line_bus_connections)
    line_bus_connections_neg = line_bus_connections;
end
function Y_lines_neg = find_Y_lines_for_neg_seq(Y_lines, numLines)
end

function bus_connections_zero = find_bus_connections_for_zero_seq(bus_connections)
    bus_connections_zero = bus_connections;
end
function line_bus_connections_zero = find_line_bus_connections_zero_seq(line_bus_connections)
    line_bus_connections_zero = line_bus_connections;
end
function Y_lines_zero = find_Y_lines_for_zero_seq(Y_lines, numLines)
end

%Milestone 6----------------------------------------------------------
function [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = single_line_to_gnd(V_f, Z_f, Z0, Z1, Z2)
    
    
    seq_fault_currents = zeros(1,3);
    
    seq_fault_currents(1) = V_f / (Z0 + Z1 + Z2 + 3*Z_f);
    seq_fault_currents(2) = seq_fault_currents(1);
    seq_fault_currents(3) = seq_fault_currents(2);
    
    seq_fault_voltages = [0; V_f; 0] - [Z0 0 0; 0 Z1 0; 0 0 Z2]*[seq_fault_currents(1); seq_fault_currents(2); seq_fault_currents(3)];
    seq_fault_voltages = seq_fault_voltages.';
%     seq_fault_voltages(1) = Z1 * seq_fault_currents(1);
%     seq_fault_voltages(2) = -1 * Z2 * seq_fault_currents(2);
%     seq_fault_voltages(3) = -1 * Z0 * seq_fault_currents(3);

    ph_fault_currents = zeros(1,3);
    ph_fault_voltages = zeros(1,3);
    
    ph_fault_currents(1) = 3 * seq_fault_currents(1);
    ph_fault_currents(2) = 0;
    ph_fault_currents(3) = 0;
    
    ph_fault_voltages(1) = Z_f * ph_fault_currents(1);
    ph_fault_voltages(2) = Z_f * ph_fault_currents(2);
    ph_fault_voltages(3) = Z_f * ph_fault_currents(3);
    
    disp('Symmetrical Fault at Bus ')
    disp(' ')
    [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = single_line_to_gnd(V_f, Z_f, Z0, Z1, Z2);
    disp('Sequence Fault Current: ')
    disp(['I0: ' num2str(seq_fault_currents(1)) 'A'])
    disp(['I1: ' num2str(seq_fault_currents(2)) 'A'])
    disp(['I2: ' num2str(seq_fault_currents(3)) 'A'])
    disp(' ')
    disp('Sequence Fault Voltages:')
    disp(['V0: ' num2str(seq_fault_voltages(1)) 'V'])
    disp(['V1 ' num2str(seq_fault_voltages(2)) 'V'])
    disp(['V2 ' num2str(seq_fault_voltages(3)) 'V'])
    disp('Phase Fault Current: ')
    disp(['Ia: ' num2str(ph_fault_currents(1)) 'A'])
    disp(['Ib: ' num2str(ph_fault_currents(2)) 'A'])
    disp(['Ic: ' num2str(ph_fault_currents(3)) 'A'])
    disp(' ')
    disp('Phase Fault Voltages:')
    disp(['Va: ' num2str(ph_fault_voltages(1)) 'V'])
    disp(['Vb: ' num2str(ph_fault_voltages(2)) 'V'])
    disp(['Vc: ' num2str(ph_fault_voltages(3)) 'V'])
        
end

function [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = line_to_line_fault(V_f, Z_f, Z0, Z1, Z2)
    
    seq_fault_currents = zeros(1,3);
    seq_fault_voltages = zeros(1,3);
    
    seq_fault_currents(1) = V_f / (Z1 + Z2 + Z_f);
    seq_fault_currents(2) = -1 * seq_fault_currents(1);
    seq_fault_currents(3) = 0;
       
    seq_fault_voltages = Z_f * seq_fault_currents(1);
    
    ph_fault_currents = zeros(1,3);
    ph_fault_voltages = zeros(1,3);
    
    a = -0.5+i*0.8660254038;
    ph_fault_currents = zeros(1,3);
    ph_fault_currents(1) = 0;
    ph_fault_currents(2) = (a^2 - a) * seq_fault_currents(1);
    ph_fault_currents(3) = -1 * ph_fault_currents(2);
    
    ph_fault_voltages = Z_f * ph_fault_currents(2);
    
    disp(' ')
    disp('Line to Line Fault Between Phases B and C at Bus 3')
    [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = line_to_line_fault(V_f, Z_f, Z0, Z1, Z2);
    disp('Sequence Fault Current: ')
    disp(['I0: ' num2str(seq_fault_currents(1)) 'A'])
    disp(['I1: ' num2str(seq_fault_currents(2)) 'A'])
    disp(['I2: ' num2str(seq_fault_currents(3)) 'A'])
    disp(' ')
    disp('Sequence Fault Voltage (V1 - V2):')
    disp(['V: ' num2str(seq_fault_voltages) 'V'])
    disp('Phase Fault Current: ')
    disp(['Ia: ' num2str(ph_fault_currents(1)) 'A'])
    disp(['Ib: ' num2str(ph_fault_currents(2)) 'A'])
    disp(['Ic: ' num2str(ph_fault_currents(3)) 'A'])
    disp(' ')
    disp('Phase Fault Voltage (Vb - Vc):')
    disp(['V: ' num2str(ph_fault_voltages) 'V'])
    
end

function [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = symmetrical_fault(V_f, Z_f, Z0, Z1, Z2)
    
    seq_fault_currents = zeros(1,3);
    seq_fault_voltages = zeros(1,3);
    
    seq_fault_currents(1) = V_f / (Z1 + Z2 + Z_f);
    seq_fault_currents(2) = -1 * seq_fault_currents(1);
    seq_fault_currents(3) = 0;
       
    seq_fault_voltages = Z_f * seq_fault_currents(1);
    
    ph_fault_currents = zeros(1,3);
    ph_fault_voltages = zeros(1,3);
    
    a = -0.5+i*0.8660254038;
    ph_fault_currents = zeros(1,3);
    ph_fault_currents(1) = 0;
    ph_fault_currents(2) = (a^2 - a) * seq_fault_currents(1);
    ph_fault_currents(3) = -1 * ph_fault_currents(2);
    
    ph_fault_voltages = Z_f * ph_fault_currents(2);
    
    disp(' ')
    disp('Line to Line Fault Between Phases B and C at Bus 3')
    [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = line_to_line_fault(V_f, Z_f, Z0, Z1, Z2);
    disp('Sequence Fault Current: ')
    disp(['I0: ' num2str(seq_fault_currents(1)) 'A'])
    disp(['I1: ' num2str(seq_fault_currents(2)) 'A'])
    disp(['I2: ' num2str(seq_fault_currents(3)) 'A'])
    disp(' ')
    disp('Sequence Fault Voltage (V1 - V2):')
    disp(['V: ' num2str(seq_fault_voltages) 'V'])
    disp('Phase Fault Current: ')
    disp(['Ia: ' num2str(ph_fault_currents(1)) 'A'])
    disp(['Ib: ' num2str(ph_fault_currents(2)) 'A'])
    disp(['Ic: ' num2str(ph_fault_currents(3)) 'A'])
    disp(' ')
    disp('Phase Fault Voltage (Vb - Vc):')
    disp(['V: ' num2str(ph_fault_voltages) 'V'])
    
end

function [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = double_line_to_gnd(V_f, Z_f, Z0, Z1, Z2)
    
    seq_fault_currents = zeros(1,3);
    seq_fault_voltages = zeros(1,3);
    
    seq_fault_currents(1) = V_f / (Z1 + Z2 + Z_f);
    seq_fault_currents(2) = -1 * seq_fault_currents(1);
    seq_fault_currents(3) = 0;
       
    seq_fault_voltages = Z_f * seq_fault_currents(1);
    
    ph_fault_currents = zeros(1,3);
    ph_fault_voltages = zeros(1,3);
    
    a = -0.5+i*0.8660254038;
    ph_fault_currents = zeros(1,3);
    ph_fault_currents(1) = 0;
    ph_fault_currents(2) = (a^2 - a) * seq_fault_currents(1);
    ph_fault_currents(3) = -1 * ph_fault_currents(2);
    
    ph_fault_voltages = Z_f * ph_fault_currents(2);
    
    disp(' ')
    disp('Double Line to Ground Fault at Bus ')
    [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = line_to_line_fault(V_f, Z_f, Z0, Z1, Z2);
    disp('Sequence Fault Current: ')
    disp(['I0: ' num2str(seq_fault_currents(1)) 'A'])
    disp(['I1: ' num2str(seq_fault_currents(2)) 'A'])
    disp(['I2: ' num2str(seq_fault_currents(3)) 'A'])
    disp(' ')
    disp('Sequence Fault Voltage (V1 - V2):')
    disp(['V: ' num2str(seq_fault_voltages) 'V'])
    disp('Phase Fault Current: ')
    disp(['Ia: ' num2str(ph_fault_currents(1)) 'A'])
    disp(['Ib: ' num2str(ph_fault_currents(2)) 'A'])
    disp(['Ic: ' num2str(ph_fault_currents(3)) 'A'])
    disp(' ')
    disp('Phase Fault Voltage (Vb - Vc):')
    disp(['V: ' num2str(ph_fault_voltages) 'V'])
    
end

function perform_fault_analysis(V_f, Z_f, Z0, Z1, Z2)
    
    [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = line_to_line_fault(V_f, Z_f, Z0, Z1, Z2);
    [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = single_line_to_gnd(V_f, Z_f, Z0, Z1, Z2);
    [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = symmetrical_fault(V_f, Z_f, Z0, Z1, Z2);
    [seq_fault_currents, seq_fault_voltages, ph_fault_currents, ph_fault_voltages] = double_line_to_gnd(V_f, Z_f, Z0, Z1, Z2);
   
end
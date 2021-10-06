std::cout << std::endl;
std::string pid2{""};
pid2.push_back(c_array[5]);
pid2.push_back(c_array[6]);

std::cout << "parsed data is the following: " << std::endl;
std::cout << "process id: " << pid2 << std::endl;

std::string a2_time{""};
a2_time.push_back(c_array[7]);

std::cout << "process arrival time: " << a2_time << std::endl;

std::string b2_time;
b2_time.push_back(c_array[8]);
b2_time.push_back(c_array[9]);
std::cout << "process burst time: " << b2_time <<std::endl;

P2.id = pid2;
P2.at = stoi(a2_time);
P2.bt = stoi(b2_time);
std::cout << P2.id <<std::endl;

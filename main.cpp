#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

typedef std::array<short, 4> IP;
typedef std::vector<IP> IPList;

// DONE extract IP from string     "I.I.I.I\t..." -> {I, I, I, I}
IP getIP(std::string s) {
    IP res{0, 0, 0, 0};
    auto i = 0;
    std::string::size_type start = 0;
    std::string::size_type stop = s.find_first_of(".");
    while (stop != std::string::npos && i < 4)
    {
        res[i++] = std::stoi(s.substr(start, stop - start));
        start = stop + 1;
        stop = s.find_first_of(".\t ", start);
    }
    return res;
}

// DONE print function
auto print_pool = [](auto const& p) { 
    for (auto &&i : p) { 
        std::cout << i[0] << "." << i[1] << "." << i[2] << "." << i[3] << std::endl;
    };
};

int main() {
    try {

        // DONE Read IP list
        IPList ip_pool;
        for(std::string line; std::getline(std::cin, line);)
        {
            ip_pool.emplace_back(getIP(line));
        }

        
        // DONE reverse lexicographically sort and output
        // 222.173.235.246
        // 222.130.177.64
        // ...
        // 1.29.168.152
        // 1.1.234.8
        std::sort(ip_pool.begin(), ip_pool.end(), [](auto &a, auto &b){
                for (size_t i = 0; i < 4; i++) {
                    if (a[i] < b[i]) return false;
                    if (a[i] > b[i]) return true;
                }
                return true;
            });
        print_pool(ip_pool);


        // DONE filter by first byte and output
        // ip = filter(1)
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        IPList ip_pool_1;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_pool_1), [n=1](auto const& ip){ 
                return ip[0] == n;
            ;});
        print_pool(ip_pool_1);


        // DONE filter by first and second bytes and output
        // ip = filter(46, 70)
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        IPList ip_pool_1_2;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_pool_1_2), [n1=46,n2=70](auto const& ip){ 
                return ip[0] == n1 && ip[1] == n2;
            ;});
        print_pool(ip_pool_1_2);


        // DONE filter by any byte and output
        // ip = filter_any(46)
        // 186.204.34.46
        // 186.46.222.194
        // ...
        // 39.46.86.85
        // 5.189.203.46
        IPList ip_pool_any;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_pool_any), [n=46](auto const& ip){ 
                return ip[0] == n || ip[1] == n || ip[2] == n || ip[3] == n;
            ;});
        print_pool(ip_pool_any);
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

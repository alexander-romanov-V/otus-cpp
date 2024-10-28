#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <array>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main()
{
    // std::cout << "debug 1\n";

    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // DONE Convert into int sub arrays
        std::vector<std::vector<int>> n_pool;
        std::transform(ip_pool.begin(), ip_pool.end(), back_inserter(n_pool), [](auto const& l) { 
                std::vector<int> v;
                for (auto &&i : l) {
                    v.push_back(std::stoi(i));
                }
                return v;
            });

        // DONE print function
        auto print_pool = [](auto const& title, auto const& p) { 
                std::cout <<std::endl << title << std::endl;
                for (auto &&i : p) { 
                    std::cout << "IP: " << i[0] << "." << i[1] << "." << i[2] << "." << i[3] << std::endl;
                };
            };
        
        // DONE reverse lexicographically sort
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        std::vector<std::vector<int>> n_reverse = n_pool;
        std::sort(n_reverse.begin(), n_reverse.end(), [](auto &a, auto &b){
                for (size_t i = 0; i < 4; i++) {
                    if (a[i] < b[i]) return false;
                    if (a[i] > b[i]) return true;
                }
                return true;
                // return ((a[0]<<24) + 
                //         (a[1]<<16) +
                //         (a[2]<<8) + 
                //         a[3]) 
                //        <
                //        ((b[0]<<24) +
                //         (b[1]<<16) + 
                //         (b[2]<<8) + 
                //         b[3]);
            });
        print_pool("Reverse lexicographically sort", n_reverse);

        // for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        // {
        //     for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        //     {
        //         if (ip_part != ip->cbegin())
        //         {
        //             std::cout << ".";

        //         }
        //         std::cout << *ip_part;
        //     }
        //     std::cout << std::endl;
        // }


        // DONE filter by first byte and output
        // ip = filter(1)
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        std::vector<std::vector<int>> n_pool_1;
        std::copy_if(n_pool.begin(), n_pool.end(), std::back_inserter(n_pool_1), [n=1](auto const& ip){ 
                return ip[0] == n;
            ;});
        print_pool("Filter by first byte and output, ip = filter(1)", n_pool_1);


        // DONE filter by first and second bytes and output
        // ip = filter(46, 70)
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        std::vector<std::vector<int>> n_pool_1_2;
        std::copy_if(n_pool.begin(), n_pool.end(), std::back_inserter(n_pool_1_2), [n1=46,n2=70](auto const& ip){ 
                return ip[0] == n1 && ip[1] == n2;
            ;});
        print_pool("Filter by first and second bytes and output, ip = filter(46, 70)", n_pool_1_2);


        // DONE filter by any byte and output
        // ip = filter_any(46)
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
        std::vector<std::vector<int>> n_pool_any;
        std::copy_if(n_reverse.begin(), n_reverse.end(), std::back_inserter(n_pool_any), [n=46](auto const& ip){ 
                return ip[0] == n || ip[1] == n || ip[2] == n || ip[3] == n;
            ;});
        print_pool("Filter by any byte and output, ip = filter_any(46)", n_pool_any);
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

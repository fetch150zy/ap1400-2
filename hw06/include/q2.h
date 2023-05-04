#ifndef Q2_H
#define Q2_H

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

namespace q2
{
    struct Patient
    {
        Patient(std::string line)
        {
            std::string delimiter = ",";
            size_t pos_start = 0, pos_end, delim_len = delimiter.length();
            std::string token;
            std::vector<std::string> res;

            while ((pos_end = line.find(delimiter, pos_start)) != std::string::npos) {
                token = line.substr (pos_start, pos_end - pos_start);
                pos_start = pos_end + delim_len;
                res.push_back (token);
            }

            res.push_back (line.substr (pos_start));

            if (res[0].back() != ' ')
                res[0].push_back(' ');
            name = res[0] + res[1];
            age = std::stoi(res[2]);
            smokes = std::stoi(res[3]);
            area_q = std::stoi(res[4]);
            alkhol = std::stoi(res[5]);

            this->risk = 3 * age + 5 * smokes + 2 * area_q + 4 * alkhol;
        }
        
        std::string name;
        std::size_t age;
        std::size_t smokes;
        std::size_t area_q;
        std::size_t alkhol;

        std::size_t risk;
    };

    inline std::vector<Patient> read_file(std::string file_name)
    {
        std::ifstream fin(file_name, std::ios::in);
        if (!fin)
            throw std::runtime_error("Open file failed");
        std::vector<Patient> patients;
        std::string line;
        for (int i = 0; i < 2; ++i)
            getline(fin, line);
        while (getline(fin, line))
            patients.push_back(Patient(line));
        fin.close();
        return patients;
    }

    inline void sort(std::vector<Patient>& patients)
    {
        std::sort(patients.begin(), patients.end(), 
                [](const Patient& p1, const Patient& p2) {
                    return p1.risk > p2.risk;
                });
    }
}

#endif //Q2_H

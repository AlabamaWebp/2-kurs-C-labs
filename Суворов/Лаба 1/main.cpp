#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <bitset>

using namespace std;

string summ_binary(string& bin1, string& bin2) {
    bitset<32> b1(bin1);
    bitset<32> b2(bin2);
    bitset<32> result = b1.to_ulong() + b2.to_ulong();
    return result.to_string();
}

vector<vector<string>> read_csv(string& filename) {
    ifstream file(filename);
    string line;
    vector<vector<string>> data;
    while (getline(file, line)) {
        stringstream line_stream(line);
        string cell;
        vector<string> row;
        while (getline(line_stream, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}

void write_csv(string& filename, vector<vector<string>>& data) {
    ofstream file(filename);
    for (auto& row : data) {
        for (int i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i != row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }
}

int main() {
    string input_file = "task1.csv";
    string output_file = "result2_ivanov_variant.csv";

    auto data = read_csv(input_file);

    for (auto& row : data) {
        try {
            string bin1 = row[0];
            string bin2 = row[1];
            string result = summ_binary(bin1, bin2);
            row.push_back(result);
        } catch (const exception& e) {
            row.push_back("Error: " + string(e.what()));
        }
    }

    write_csv(output_file, data);
    return 0;
}

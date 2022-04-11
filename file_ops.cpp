#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream ifs("./binary_file", ifstream::in|ifstream::binary);
    if (!ifs) {
        cout << "Couldn't open ./binary_file\n";
        return 1;
    }
    int count = 0;
    int target = 0;
    if (argc == 2) {
        target = atoi(argv[1]);
        if (errno || target < 0 || target > 255) {
            cout << "Character must be between 0..255.\n";
            return 1;
        }
    }

    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    cout << "File length is :" << length << "\n";
    char buffer[4096];
    while (true) {
        ifs.read(buffer, sizeof(buffer));
        int read_bytes = ifs.gcount();
        if (read_bytes != sizeof(buffer)) {
            cout << "(Last buffer had " << read_bytes << " bytes.)\n";
        }
        for (int i = 0; i < read_bytes; ++i) {
            if (buffer[i] == (char)target) {
                ++count;
            }
        }
        if (!ifs) {
            cout << boolalpha << "GOOD : " << ifs.good() << "\nBAD : " << ifs.bad() << "\nFAIL : " << ifs.fail() << "\nEOF : " << ifs.eof() << "\nOP() : false\n";
            break;
        }
    }

    cout << target << " character was found " << count << " time(s) in the file.\n";
    return 0;
}
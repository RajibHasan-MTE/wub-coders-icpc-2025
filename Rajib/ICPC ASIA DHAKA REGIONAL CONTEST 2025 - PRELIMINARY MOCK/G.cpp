#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    cin >> N;
    cin.ignore();

    for (int i = 0; i < N; ++i) {
        string input;
        getline(cin, input);


        int sizeof_line = 0;
        int strlen_line = 0;
        bool first_null_found = false;

        for (size_t j = 0; j < input.size(); ++j) {
            if (input[j] == '\\' && j + 1 < input.size() && input[j+1] == '0') {
                sizeof_line++;
                if (!first_null_found) {
                    first_null_found = true;
                    strlen_line = sizeof_line - 1;
                }
                j++;
            } else {
                sizeof_line++;
            }
        }


        sizeof_line++;
        if (!first_null_found) {
            strlen_line = sizeof_line - 1;
        }

        cout << sizeof_line << " " << strlen_line << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include "omp.h"

#pragma comment(linker, "/STACK:10000000000")

using namespace std;

struct Prod {
    long long a = 0, b = 0, c = 0, d = 0;

    Prod(long long a, long long b, long long c, long long d) : a(a), b(b), c(c), d(d) {}

    Prod() {}

    friend ostream &operator<<(std::ostream &out, const Prod &prod);
};

std::ostream &operator<<(std::ostream &out, const Prod &prod) {
    out << "Prod(" << prod.a << ", " << prod.b << ", " << prod.c << ", " << prod.d << ")";

    return out;
}

time_t t;


int main(int argc, char *args[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long threadNum = (int) *args[1];
    omp_set_num_threads(threadNum);
    long long sz1, sz2, sz3, sz4;
    cin >> sz1 >> sz2 >> sz3 >> sz4;
    vector<long long> a1(sz1), a2(sz2), a3(sz3), a4(sz4);
    t = time(nullptr);

    for (long long &elem: a1) elem = rand();
    for (long long &elem: a2) elem = rand();
    for (long long &elem: a3) elem = rand();
    for (long long &elem: a4) elem = rand();

    vector<Prod> res(sz1 * sz2 * sz3 * sz4);
    cout << "array created, time: " << time(nullptr) - t << endl;

#pragma omp parallel for
    for (int i = 0; i < sz1; i++)
        for (int j = 0; j < sz2; j++)
            for (int k = 0; k < sz3; k++)
                for (int s = 0; s < sz4; s++)
                    res[i * sz2 * sz3 * sz4 + j * sz3 * sz4 + k * sz4 + s] = (Prod(a1[i], a2[j], a3[k],
                                                                                               a4[s]));

    for (int i = 0; i < res.size(); i++) cout << res[i] << endl;
    cout << "summary time: " << time(nullptr) - t;
}

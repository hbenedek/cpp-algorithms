//Benedek Harsanyi 343966, Antoine Escoyez 335564
#include <bits/stdc++.h>
using namespace std;

std::random_device rd;
std::mt19937 gen(rd());

int get_sign(int idx, int replication)
{
    return gen() % 2 ? 1 : -1;
}

int get_partition(int idx, int replication, int buckets)
{
    return gen() % buckets;
}

int main(){
    //competitive programming magic making cin cout faster
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int s;
    cin >> s;

    int n, t, b;
    cin >> n >> t >> b;

    int replication = 18;
    int buckets =  8 * (b + 1);
    int size = replication * buckets;

    if (s == 1)
    {
        //construct good sketch
        map<int, long int> results;
        for (long int i = 0; i < n; i++)
        {   
            int id;
            long int score;
            cin >> id >> score;
            gen.seed(id);
            for (int r = 0; r < replication; r++)
            {
                int partition = get_partition(id ,r, buckets);
                results[buckets * r + partition] -= get_sign(id, r) * score;
            }
        }
 
        //write results
        cout << size << '\n';
        for (int i = 0; i < size; i++)
        {
            long int v = results[i];
            cout << v << " ";
        }
        cout << '\n';
        fflush(stdout);
    }
    else if (s == 2)
    {
        long double threshold = 3 * t / 4;
        int m;
        cin >> m;
 
        //read good sketch
        map<int, long int> sketch;
        for (int i=0; i<m; ++i)
        {
            long int v;
            cin >> v;
            sketch[i] = v;
        }
 
        //construct bad sketch
        for (int i = 0; i < n; i++)
        {
            int id;
            long int score;
            cin >> id >> score;
            gen.seed(id);
            for (int r = 0; r < replication; r++)
            {
                int partition = get_partition(id ,r, buckets);
                sketch[buckets * r + partition] += get_sign(id, r) * score;
            }        
        } 
        
        // read queries
        int k;
        cin >> k;
 
        for (int j = 0; j < k; j++)
        {
            int q;
            cin >> q;
            gen.seed(q);
 
            double results[replication];  
            for (int r = 0; r < replication; r++)
            {
                int partition = get_partition(q,  r, buckets);
                results[r] = (sketch[buckets * r + partition] * get_sign(q, r));
            }
            nth_element(results, results + replication / 2, results + replication);
            long int pred = results[replication/2];
            if (pred > threshold)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }   
    }  
}
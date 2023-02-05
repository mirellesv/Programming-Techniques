#include <bits/stdc++.h>

using namespace std;

using iPair = pair<int, int>;

class DisjointSets{
    private:
        int *parent, *rnk;
        int n;

    public:
        DisjointSets(int new_n){ // Constructor
            int i;
            n = new_n;
            parent = new int[n + 1];
            rnk = new int[n + 1];

            for(i = 0; i <= n; i++){
                rnk[i] = 0;
                parent[i] = i;
            }
        }

        int find(int u){
            if(u != parent[u])
                parent[u] = find(parent[u]);
            return parent[u];
        }

        void merge(int x, int y){
            x = find(x);
            y = find(y);

            if(rnk[x] > rnk[y])
                parent[y] = x;
            else
                parent[x] = y;

            if(rnk[x] == rnk[y])
                rnk[y]++;
        }
};

class Graph{
    private:
        int V;
        int E;
        vector < pair<int, iPair> > edges;
    public:
        Graph(int new_V, int new_E){ // Constructor
            V = new_V;
            E = new_E;
        }
        // Acessors and mutators
        int getV() const{
            return V;
        }
        void setV(int new_V){
            V = new_V;
        }
        int getE() const{
            return E;
        }
        void setE(int new_E){
            E = new_E;
        }
        void setEdge(int u, int v, int w){
            edges.push_back({w, {u, v}});
        }
        int kruskalMST(){
            int mst_wt = 0;

            sort(edges.begin(), edges.end());

            DisjointSets ds(V);

            vector< pair<int, iPair> >::iterator it;

            for(it = edges.begin(); it != edges.end(); it++){
                int u = it->second.first;
                int v = it->second.second;

                int set_u = ds.find(u);
                int set_v = ds.find(v);

                if(set_u != set_v){
                    cout << u << " - " << v << endl;

                    mst_wt += it->first;

                    ds.merge(set_u, set_v);
                }
            }

            return mst_wt;
        }
};

int main(){
    int V = 9, E = 14;
    Graph g(V, E);

    g.setEdge(0, 1, 4);
    g.setEdge(0, 7, 8);
    g.setEdge(1, 2, 8);
    g.setEdge(1, 7, 11);
    g.setEdge(2, 3, 7);
    g.setEdge(2, 8, 2);
    g.setEdge(2, 5, 4);
    g.setEdge(3, 4, 9);
    g.setEdge(3, 5, 14);
    g.setEdge(4, 5, 10);
    g.setEdge(5, 6, 2);
    g.setEdge(6, 7, 1);
    g.setEdge(6, 8, 6);
    g.setEdge(7, 8, 7);

    cout << "Edges of MST are \n";
    int mst_wt = g.kruskalMST();

    cout << "\nWeight of MST is " << mst_wt;

    return 0;
}

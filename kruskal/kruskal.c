#include "kruskal.h"

EdgeList* kruskal(EdgeList* edges, int n) {
    UF* uf = UF_init(n);
    EdgeList* mst_list = edge_list_create(n - 1);

    for(int i = 0; i < edge_list_get_size(edges); i++) {
        unsigned short int src;
        unsigned short int dest;
        edge_list_get_vw(edges, i, &src, &dest);

        unsigned short int u = UF_find(uf, src);
        unsigned short int v = UF_find(uf, dest);

        if(!UF_connected(uf, u, v)) {
            UF_union(uf, u, v);
            float weight = edge_list_get_weight(edges, i);
            edge_list_add(mst_list, src, dest, weight);
        }
    }

    UF_free(uf);
    return mst_list;
}

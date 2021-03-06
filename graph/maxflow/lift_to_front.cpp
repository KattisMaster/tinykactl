/* KTH ACM Contest Template Library
 *
 * Graph/Max flow/Preflow-Push lift-to-front
 *
 * Credit:
 *   Karzanov, Goldberg (, Tarjan?)
 *   From [Intro to Algs ed. 8, pp.605-625,629]
 *   By Mattias de Zalenski
 *   tinyKACTLised by Per Austrin
 */

#include "flow_graph.cpp"

void add_flow(adj_list *g, flow_edge &e, Flow f, Flow *exc) {
  flow_edge &back = g[e.dest][e.back];
  e.f += f; e.c -= f; exc[e.dest] += f;
  back.f -= f; back.c += f; exc[back.dest] -= f;
}

Flow lift_to_front(adj_list *g, int v, int s, int t) {
  int l[MAXNODES], hgt[MAXNODES]; // l == list, hgt == height
  Flow exc[MAXNODES]; // exc == excess
  adj_iter cur[MAXNODES];

  memset(hgt, 0, sizeof(int)*v);
  memset(exc, 0, sizeof(Flow)*v);
  hgt[s] = v - 2;
  for (adj_iter it = g[s].begin(); it != g[s].end(); it++)
    add_flow(g, *it, it->c, exc);
  int p = t; // make l a linked list from p to t (sink)
  for (int i = 0; i < v; i++) {
    if (i != s && i != t) l[i] = p, p = i; 
    else l[i] = t; 
    cur[i] = g[i].begin();
  }

  int r = 0, u = p; // lift-to-front loop
  while (u != t) {
    int oldheight = hgt[u];
    while (exc[u] > 0)  // discharge u
      if (cur[u] == g[u].end()) {
	hgt[u] = 2 * v - 1; // lift u, find admissible edge
	for (adj_iter it = g[u].begin(); it!=g[u].end(); ++it)
	  if (it->c > 0 && hgt[it->dest] + 1 < hgt[u])
	    hgt[u] = hgt[it->dest]+1, cur[u] = it;
      } else if (cur[u]->c>0 && hgt[u] == hgt[cur[u]->dest]+1)
	add_flow(g, *cur[u], min(exc[u], (*cur[u]).c), exc);
      else ++cur[u];
    if (hgt[u] > oldheight && p != u)    // lift-to-front!
      l[r] = l[u], l[u] = p, p = u;      // u to front of list
    r = u, u = l[r];
  }
  return exc[t];
}

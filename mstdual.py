import sys

lines = [[int(x) for x in line.strip().split()] for line in sys.stdin]
n, m = lines[0]
edges = lines[1:]


class Graph:
    def __init__(self, n):
        self.n = n
        self.graph = []
        self.MST = None
        self.KTree = None

    def addEdge(self, u, v, w):
        self.graph.append([u, v, w])

    def find(self, parent, i):
        if parent[i - 1] == i:
            return i
        return self.find(parent, parent[i - 1])

    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)
        if rank[xroot - 1] < rank[yroot - 1]:
            parent[xroot - 1] = yroot
        elif rank[xroot - 1] > rank[yroot - 1]:
            parent[yroot - 1] = xroot
        else:
            parent[yroot - 1] = xroot
            rank[xroot - 1] += 1

    def Kruskal(self):
        result = []
        edge_idx = 0
        nb_edges = 0

        self.graph = sorted(self.graph, key=lambda item: item[2])

        parent = []
        rank = []

        for node in range(self.n):
            parent.append(node + 1)
            rank.append(0)

        while nb_edges < self.n - 1:

            u, v, w = self.graph[edge_idx]
            edge_idx += 1
            x = self.find(parent, u)
            y = self.find(parent, v)

            if x != y:
                nb_edges += 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)

        minCost = 0
        for u, v, weight in result:
            minCost += weight
        
        self.MST = result

    def KruskalTree(self):
        assert self.MST is not None, 'Compute MST first'
        result = []
        visited_nodes = set()

        for u, v, w in self.MST:
            new_node = set([u, v])
            if len(set(new_node).intersection(visited_nodes)) > 0:
                new_result = []
                for node, w_node, w_node_parent in result:
                    common = node.intersection(new_node)
                    if (w_node_parent == 0) and (len(common) > 0):
                        new_result.append([node, w_node, w])
                        new_node = new_node.union(node)
                    else:
                        new_result.append([node, w_node, w_node_parent])
                result = new_result
                result.append([new_node, w, 0])
            else:
                result.append([new_node, w, 0])
            visited_nodes = visited_nodes.union(new_node)
        self.KTree = result
    
    def dual_solution(self):
        assert self.KTree is not None, 'Compute Kruskal Tree first.'
        k = 0
        result = []
        
        for s, w, w_parent in self.KTree:
            size = len(s)
            if size == self.n:
                y = w - w_parent
            else:
                y = w_parent - w
            if y !=0:
                k += 1
                result.append([size, y])
                result.append(list(s))
        
        result = [[k]] + result
        return result


g = Graph(n)
for u, v, w in edges:
    g.addEdge(u, v, w)
g.Kruskal()
g.KruskalTree()
res = g.dual_solution()

for line in res:
    sys.stdout.write(" ".join(str(c) for c in line) + "\n")
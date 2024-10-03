import sys, os
sys.setrecursionlimit(1<<30)
from io import BytesIO, IOBase
from types import GeneratorType

# input = sys.stdin.readline

def search(v, x):
    l, h = 0, len(v) - 1
    ans = len(v)
    while l <= h:
        m = (l + h) // 2
        if v[m] >= x:
            ans = m
            h = m - 1
        else:
            l = m + 1
    return ans

def dfs(par, root, flat):
    global timer
    stack = [(root, par)]  # Initialize stack with root and its parent
    
    while stack:
        node, parent = stack.pop()
        if vis[node]==0:  # Check if the node has been visited
            tin[node] = timer
            timer += 1
            flat.append(node)
            stack.append((node,par))
            vis[node] = 1
            for neighbor in Tree[node]:
                if neighbor != parent:
                    stack.append((neighbor, node))
        else:  
            flat.append(node)
            tout[node] = timer
            timer += 1
    #print(flat)

class MST:
    def __init__(self, v):
        self.n = len(v)
        self.v = v
        self.tree = [[] for _ in range(4 * self.n)]
        self.build(0, self.n - 1, 0)

    def build(self, low, high, ind):
        if low == high:
            self.tree[ind].append(self.v[low])
            return

        mid = (low + high) // 2
        self.build(low, mid, 2 * ind + 1)
        self.build(mid + 1, high, 2 * ind + 2)
        self.tree[ind] = sorted(self.tree[2 * ind + 1] + self.tree[2 * ind + 2])

    def query(self, low, high, l, r, ind, x):
        if low >= l and high <= r:
            return search(self.tree[ind], x)

        elif r < low or l > high:
            return 0

        mid = (low + high) // 2
        left = self.query(low, mid, l, r, 2 * ind + 1, x)
        right = self.query(mid + 1, high, l, r, 2 * ind + 2, x)

        return left + right

    def query_range(self, l, r, x):
        return self.query(0, self.n - 1, l, r, 0, x)
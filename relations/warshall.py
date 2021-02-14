# R -- adjecency matrix of the relation
# T -- adjecency matrix of the transitive closure of R

def transitive_closure(R):
    n = len(R)
    T = R.copy()
    for k in range(0, n):
        t = []
        for i in range(0, n):
            t.append([])
            for j in range(0, n):
                t[i].append(T[i][j] or (T[i][k] and T[k][j]))
        del T
        T = t
    return T


# drive

R = [
    [0, 1, 0],
    [0, 1, 1],
    [0, 0, 0]
]

print(transitive_closure(R))

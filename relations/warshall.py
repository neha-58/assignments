# R -- adjecency matrix of the relation
# T -- adjecency matrix of the transitive closure of R

def transitive_closure(R):
    n = len(R)
    T = R.copy()
    for k in range(1, n):
        for i in range(1, n):
            for j in range(1, n):
                T[k][i][j] = T[k-1][i][j] or (T[k-1][i][k] and T[k-1][k][j])
    return T

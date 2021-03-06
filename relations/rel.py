def is_reflexive(X, R):
    for i in range(len(X)):
        if R[i][i] == 0:
            return False
    return True


def is_irreflexive(X, R):
    for i in range(len(X)):
        if R[i][i] == 1:
            return False
    return True


def is_not_reflexive(X, R):
    for i in range(len(X)):
        if R[i][i] == 0:
            return True
    return False


def is_symmetric(X, R):
    n = len(X)
    for i in range(1, n):
        for j in range(0, i):
            if R[i][j] != R[j][i]:
                return False
    return True


def is_antisymmetric(X, R):
    n = len(X)
    for i in range(1, n):
        for j in range(0, i):
            if R[i][j] == R[j][i]:
                return False
    return True


def is_not_symmetric(X, R):
    n = len(X)
    for i in range(1, n):
        for j in range(0, i):
            if R[i][j] != R[j][i]:
                return True
    return False


def is_transitive(X, R):
    n = len(X)
    for i in range(0, n):
        for j in range(0, n):
            if R[i][j] == 1:
                for k in range(0, n):
                    if R[j][k] == 1 and R[i][k] == 0:
                        return False
    return True


def is_not_transitive(X, R):
    n = len(X)
    for i in range(0, n):
        for j in range(0, n):
            if R[i][j] == 1:
                for k in range(0, n):
                    if R[j][k] == 1 and R[i][k] == 1:
                        return False
    return True


def is_equivalence(X, R):
    if is_reflexive(X, R) and is_symmetric(X, R) and is_transitive(X, R):
        return True
    return False


def is_partial_order(X, R):
    if is_reflexive(X, R) and is_antisymmetric(X, R) and is_transitive(X, R):
        return True
    return False


X = {1, 2, 3}

R = [
    [0, 1, 0],
    [1, 1, 1],
    [0, 1, 0]
]

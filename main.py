from collections import deque, defaultdict

def min_transfers(n, continent):
    continent_graph = defaultdict(list)
    for i in range(n):
        continent_graph[continent[i]].append(i)

    queue = deque([(0, 0)])
    visited = [False] * n
    visited[0] = True

    while queue:
        current, steps = queue.popleft()

        if current == n - 1:
            return steps

        for next_island in [current - 1, current + 1]:
            if 0 <= next_island < n and not visited[next_island]:
                visited[next_island] = True
                queue.append((next_island, steps + 1))

        continent_number = continent[current]
        for next_island in continent_graph[continent_number]:
            if not visited[next_island]:
                visited[next_island] = True
                queue.append((next_island, steps + 1))

        continent_graph[continent_number] = []

    return -1

# измените эту строку чтобы установить другие входные данные
string_data = '11 -86 -86 -86 201 11 86 86 86 3 201'

array_data = list(map(int, string_data.split()))
n = len(array_data)
print(min_transfers(n, array_data))
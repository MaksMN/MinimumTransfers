#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int min_transfers(int n, vector<int> continent) {
    // Создаем граф для материков
    unordered_map<int, vector<int>> continent_graph;
    for (int i = 0; i < n; ++i) {
        continent_graph[continent[i]].push_back(i);
    }

    // Очередь для BFS и массив посещенных островов
    queue<pair<int, int>> q;  // (остров, количество шагов)
    vector<bool> visited(n, false);
    q.push({ 0, 0 });
    visited[0] = true;

    while (!q.empty()) {
        auto [current, steps] = q.front();
        q.pop();

        // Если мы достигли последнего острова
        if (current == n - 1) {
            return steps;
        }

        // Проверка соседних островов
        vector<int> neighbors = { current - 1, current + 1 };
        for (int next_island : neighbors) {
            if (next_island >= 0 && next_island < n && !visited[next_island]) {
                visited[next_island] = true;
                q.push({ next_island, steps + 1 });
            }
        }

        // Переходы через портал
        int continent_number = continent[current];
        for (int next_island : continent_graph[continent_number]) {
            if (!visited[next_island]) {
                visited[next_island] = true;
                q.push({ next_island, steps + 1 });
            }
        }

        // После использования порталов для данного материка, очищаем список, чтобы не использовать его повторно
        continent_graph[continent_number].clear();
    }

    return -1;  // Если путь не найден, что не должно произойти при правильных данных
}

int main() {

    // для измнения входных данных измените этот вектор
    vector<int> continent = { 11, -86, -86, -86, 201, 11, 86, 86, 86,  3, 201 };
    int n = continent.size();
    cout << min_transfers(n, continent) << endl;  // Ожидаемый результат: 3
    return 0;
}

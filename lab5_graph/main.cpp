#include <iostream>
#include<vector>
#include <ctime>
#include<queue>
#include<algorithm>

using namespace std;

const int max_vert_count = 20;

bool operator < (pair<int,int> left, pair<int,int> right) {
    if (left.second<right.second) {return true;}
    return false;
}

struct graph_matrix {
    int adjacent[max_vert_count][max_vert_count];
    int vertex_count;
    bool is_oriented = false;

    graph_matrix(int vertices) {
        vertex_count = vertices;
        for (int i = 0; i < vertex_count; i++) {
            for(int j = 0; j < vertex_count; j++) {
                adjacent[i][j] = 0;
            }
        }
    }
};

struct graph_struct {
    vector<vector<pair<int,int>>> adjacent;
    int vertex_count;
    bool is_oriented = false;

    graph_struct(int vertices) {
        vertex_count = vertices;
        adjacent.resize(vertices);
    }
};

void add_to_matr (graph_matrix& graph, int vert1, int vert2, int weight = 1) {
    graph.adjacent[vert1][vert2] = weight;
    if (!graph.is_oriented) {
        graph.adjacent[vert2][vert1] = weight;
    }
};

void add_to_struct (graph_struct& graph, int vert1, int vert2, int weight = 1) {
    graph.adjacent[vert1].push_back(make_pair(vert2, weight));
    if (!graph.is_oriented) {
        graph.adjacent[vert2].push_back(make_pair(vert1, weight));
    }
};

void output_matrix_graph (graph_matrix& graph) {
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            cout<<graph.adjacent[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void output_struct_graph (graph_struct& graph) {
    for (int i = 0; i < graph.vertex_count; i++) {
        cout<<i<<": ";
        for (auto item : graph.adjacent[i]) {
            cout<<'('<<item.first<<", "<<item.second<<") ";
        }
        cout<<endl;
    }
}

graph_matrix* create_random_matrg(int vertix_count, int edge_count, bool is_oriented = false, bool is_weighed = false) {
    graph_matrix* graph = new graph_matrix(vertix_count);
    (*graph).is_oriented = is_oriented;
    int vert1, vert2, weight = 1;
    for (int i = 0; i < edge_count; i++) {
        do {
            vert1 = rand() % vertix_count;
            vert2 = rand() % vertix_count;
        } while ((*graph).adjacent[vert1][vert2]!=0);

        if (is_weighed) {weight = rand()%9+1;}
        (*graph).adjacent[vert1][vert2] = weight;
        if (!is_oriented) {
            (*graph).adjacent[vert2][vert1] = weight;
        }
    }
    return graph;
}

graph_struct* create_random_structg(int vertix_count, int edge_count, bool is_oriented = false, bool is_weighed = false) {
    graph_struct* graph = new graph_struct(vertix_count);
    (*graph).is_oriented = is_oriented;
    int vert1, vert2, weight = 1;
    bool used = false;
    for (int i = 0; i < edge_count; i++) {
        do {
            vert1 = rand() % vertix_count;
            vert2 = rand() % vertix_count;
            for (int i = 0; i < (*graph).adjacent[vert1].size(); i++) {
                if (((*graph).adjacent[vert1])[i].first == vert2) {
                    used = true;
                }
            }
        } while (used);

        if (is_weighed) {weight = rand()%9+1;}
        (*graph).adjacent[vert1].push_back(make_pair(vert2, weight));
        if (!is_oriented) {
            (*graph).adjacent[vert2].push_back(make_pair(vert1, weight));
        }
    }
    return graph;
}

graph_matrix* struct_to_matr (graph_struct& graph) {
    graph_matrix* new_graph = new graph_matrix(graph.vertex_count);
    (*new_graph).is_oriented = graph.is_oriented;
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.adjacent[i].size(); j++) {
            (*new_graph).adjacent[i][graph.adjacent[i][j].first] = graph.adjacent[i][j].second;
        }
    }
    return new_graph;
}

graph_struct* matr_to_struct (graph_matrix& graph) {
    graph_struct* new_graph = new graph_struct(graph.vertex_count);
    (*new_graph).is_oriented = graph.is_oriented;
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            if (graph.adjacent[i][j]!=0) {
                (*new_graph).adjacent[i].push_back(make_pair(j,graph.adjacent[i][j]));
            }
        }
    }
    return new_graph;
}

bool is_cyclic_matr_rec(int curr_vertex, bool* visited, bool *recStack, graph_matrix& graph) {
    if (!visited[curr_vertex]) {

        visited[curr_vertex] = true;
        recStack[curr_vertex] = true;

        for (int i = 0; i < graph.vertex_count; i++) {
            if (graph.adjacent[curr_vertex][i] > 0) {
                if (!visited[i] && is_cyclic_matr_rec(i, visited, recStack, graph)) { return true; }
                else if (recStack[i]) { return true; }
            }
        }

    }
    recStack[curr_vertex] = false;
    return false;
}

bool is_cyclic_matr (graph_matrix& graph) {
    bool visited[max_vert_count];
    bool stack[max_vert_count];

    for (int i = 0; i < graph.vertex_count; i++) {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        if (is_cyclic_matr_rec(i,visited,stack,graph)) {return true;}
        return false;
    }
}

bool is_cyclic_struct_rec(int curr_vertex, bool* visited, bool *recStack, graph_struct& graph) {
    if(!visited[curr_vertex]) {

        visited[curr_vertex] = true;
        recStack[curr_vertex] = true;

        for(int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            if (!visited[i] && is_cyclic_struct_rec(i, visited, recStack, graph)) {return true;}
            else if (recStack[i]) {return true;}
        }

    }
    recStack[curr_vertex] = false;
    return false;
}

bool is_cyclic_str (graph_struct& graph) {
    bool visited[max_vert_count];
    bool stack[max_vert_count];

    for (int i = 0; i < graph.vertex_count; i++) {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        if (is_cyclic_struct_rec(i,visited,stack,graph)) {return true;}
        return false;
    }
}

void bfs_matr_rec(int curr_vertex, vector<bool>& visited, graph_matrix& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;

    visited[curr_vertex] = true;
    q.push(curr_vertex);

    while(!q.empty()) {
        curr_vertex = q.front();
        cout << curr_vertex << " ";
        q.pop();

        for (int i = 0; i < graph.vertex_count; i++) {
            if (graph.adjacent[curr_vertex][i] > 0) {
                edges_weight.push_back(make_pair(i,graph.adjacent[curr_vertex][i]));
            }
        }
        if (by_weight) {sort(edges_weight.begin(), edges_weight.end());}

        for (int i = 0; i < edges_weight.size(); i++) {
            if (!visited[edges_weight[i].first]) {
                visited[edges_weight[i].first] = true;
                q.push(edges_weight[i].first);
            }
        }

    }
}

void bfs_matr(graph_matrix& graph, bool by_weight) {
    vector<bool> visited(max_vert_count, false);
    for (int curr_vertex = 0; curr_vertex < graph.vertex_count; curr_vertex++) {
        if (visited[curr_vertex] == false) {bfs_matr_rec(curr_vertex, visited, graph, by_weight);}
    }
}

void bfs_struct_rec(int curr_vertex, vector<bool>& visited, graph_struct& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int,int>> edges_weight;

    visited[curr_vertex] = true;
    q.push(curr_vertex);

    while(!q.empty()) {
        curr_vertex = q.front();
        cout << curr_vertex << " ";
        q.pop();

        for (int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            edges_weight.push_back(graph.adjacent[curr_vertex][i]);
        }
        if (by_weight) {sort(edges_weight.begin(), edges_weight.end());}

        for (int i = 0; i < edges_weight.size(); i++) {
            if (!visited[edges_weight[i].first]) {
                visited[edges_weight[i].first] = true;
                q.push(edges_weight[i].first);
            }
        }
    }
}

void bfs_struct(graph_struct& graph, bool by_weight) {
    vector<bool> visited(max_vert_count, false);
    for (int curr_vertex = 0; curr_vertex < graph.vertex_count; curr_vertex++) {
        if (visited[curr_vertex] == false) {bfs_struct_rec(curr_vertex, visited, graph, by_weight);}
    }
}

vector<vector<int>> Floyd_matr (graph_matrix& graph) {
    vector<vector<int>> distance[max_vert_count];

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            distance[i][j].push_back(graph.adjacent[i][j]);
        }
    }

    for (int k = 0; k < graph.vertex_count; k++) {
        for (int i = 0; i < graph.vertex_count; i++) {
            for (int j = 0; j < graph.vertex_count; j++) {
                if ((*distance)[i][k] + (*distance)[k][j] < (*distance)[i][j]) {
                    (*distance)[i][j] = (*distance)[i][k] + (*distance)[k][j];
                }
            }
        }
    }
    return *distance;
}

vector<int> Floyd_matr_all_for_one (graph_matrix& graph, int vertex) {
    vector<vector<int>> distance;
    vector<int> result;
    distance = Floyd_matr(graph);
    for (int i = 0; i < graph.vertex_count; i++) {
        result.push_back(distance[vertex][i]);
    }
    return result;
}

int Floyd_matr_between_two (graph_matrix& graph, int vertex1, int vertex2) {
    vector<vector<int>> distance = Floyd_matr(graph);
    return (distance[vertex1][vertex2]);
}

vector<vector<int>> Floyd_struct (graph_struct& graph) {
    vector<vector<int>> distance[graph.vertex_count];

    double matrix[graph.vertex_count][graph.vertex_count];
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            matrix[i][j] = INT32_MAX;
        }
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.adjacent[i].size(); j++) {
            matrix[i][graph.adjacent[i][j].first] = graph.adjacent[i][j].second;
            matrix[graph.adjacent[i][j].first][i] = graph.adjacent[i][j].second;
        }
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            for (int k = 0; k < graph.vertex_count; k++) {
                if (matrix[j][k] > matrix[j][i] + matrix[i][k]) {
                    matrix[j][k] = matrix[j][i] + matrix[i][k];
                }
            }
        }
    }
    return *distance;
}

vector<int> Floyd_struct_all_for_one (graph_struct& graph, int vertex) {
    vector<vector<int>> distance;
    vector<int> result;
    distance = Floyd_struct(graph);
    for (int i = 0; i < graph.vertex_count; i++) {
        result.push_back(distance[vertex][i]);
    }
    return result;
}

int Floyd_struct_between_two (graph_struct& graph, int vertex1, int vertex2) {
    vector<vector<int>> distance = Floyd_struct(graph);
    return (distance[vertex1][vertex2]);
}

void dfs_for_topological_matr (graph_matrix& graph, int vertex, vector<bool>& visited, vector<int>& result) {

    visited[vertex] = true;
    for (int i = 0; i < graph.vertex_count; i++) {
        if (graph.adjacent[vertex][i] != 0 && !visited[i])  {
            dfs_for_topological_matr(graph, i, visited, result);
        }
    }

    result.push_back(vertex);
}

vector<int> topological_sort_matr(graph_matrix& graph) {
    vector<bool> visited;
    vector<int> result;

    if (is_cyclic_matr(graph) || !graph.is_oriented) {
        result.push_back(0);
        return result;
    }

    for (int i = 0; i < graph.vertex_count; i++) {visited.push_back(false);}
    for (int i = 0; i < graph.vertex_count; i++) {
        if (!visited[i])
            dfs_for_topological_matr (graph, i, visited, result);
    }
    reverse(result.begin(), result.end());
    return result;
}

void dfs_for_topological_struct(graph_struct& graph, int vertex, vector<bool>& visited, vector<int>& result) {

    visited[vertex] = true;
    for (int i = 0; i < graph.adjacent[vertex].size(); i++) {
            dfs_for_topological_struct(graph, i, visited, result);
    }

    result.push_back(vertex);
}

vector<int> topological_sort_struct(graph_struct& graph) {
    vector<bool> visited;
    vector<int> result;

    if (is_cyclic_str(graph) || !graph.is_oriented) {
        result.push_back(0);
        return result;
    }

    for (int i = 0; i < graph.vertex_count; i++) {visited.push_back(false);}
    for (int i = 0; i < graph.vertex_count; i++) {
        if (!visited[i])
            dfs_for_topological_struct(graph, i, visited, result);
    }
    reverse(result.begin(), result.end());
    return result;
}

graph_matrix* bfs_matr_for_span(vector<bool>& visited, graph_matrix& graph, int curr_vertex = 0, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;
    vector<bool> already_connected;
    graph_matrix* result = new graph_matrix(graph.vertex_count);

    for (int i = 0; i < graph.vertex_count; i++) {
        already_connected[i] = false;
    }

    visited[curr_vertex] = true;
    q.push(curr_vertex);
    already_connected[curr_vertex] = true;

    while(!q.empty()) {
        curr_vertex = q.front();
        q.pop();

        for (int i = 0; i < graph.vertex_count; i++) {
            if (graph.adjacent[curr_vertex][i] != 0 && !already_connected[i]) {
                (*result).adjacent[curr_vertex][i] = graph.adjacent[curr_vertex][i];
                already_connected[i] = true;
            }
        }

        for (int i = 0; i < graph.vertex_count; i++) {
            if (graph.adjacent[curr_vertex][i] > 0) {
                edges_weight.push_back(make_pair(i,graph.adjacent[curr_vertex][i]));
            }
        }
        if (by_weight) {sort(edges_weight.begin(), edges_weight.end());}

        for (int i = 0; i < edges_weight.size(); i++) {
            if (!visited[edges_weight[i].first]) {
                visited[edges_weight[i].first] = true;
                q.push(edges_weight[i].first);
            }
        }
    }
    return result;
}

graph_struct* bfs_struct_for_span(vector<bool>& visited, graph_struct& graph, int curr_vertex = 0, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;
    vector<bool> already_connected;
    graph_struct* result = new graph_struct(graph.vertex_count);

    for (int i = 0; i < graph.vertex_count; i++) {
        already_connected[i] = false;
    }

    visited[curr_vertex] = true;
    q.push(curr_vertex);
    already_connected[curr_vertex] = true;

    while(!q.empty()) {
        curr_vertex = q.front();
        q.pop();

        for (int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            if (!already_connected[graph.adjacent[curr_vertex][i].first]) {
                (*result).adjacent[curr_vertex].push_back(graph.adjacent[curr_vertex][i]);

                already_connected[graph.adjacent[curr_vertex][i].first] = true;
            }
        }

        for (int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            edges_weight.push_back(graph.adjacent[curr_vertex][i]);
        }
        if (by_weight) {sort(edges_weight.begin(), edges_weight.end());}

        for (int i = 0; i < edges_weight.size(); i++) {
            if (!visited[edges_weight[i].first]) {
                visited[edges_weight[i].first] = true;
                q.push(edges_weight[i].first);
            }
        }
    }
    return result;
}

struct boruvka_subset {
    vector<int> vertexes;
};

pair<int,int> lowest_in_subset (boruvka_subset* sub, vector<pair<int,int>>& lows) {
    int min = lows[sub->vertexes[0]].second;
    pair<int,int> vert_with_min = make_pair(sub->vertexes[0], lows[sub->vertexes[0]].first);
    for (int i = 1; i < sub->vertexes.size(); i++) {
        if (lows[sub->vertexes[i]].second < min) {
            min = lows[sub->vertexes[i]].second;
            vert_with_min = make_pair(sub->vertexes[i], lows[sub->vertexes[i]].first);
        }
    }
    return vert_with_min;
}

int find_subset_by_vert (vector<boruvka_subset>& subs, int vert, int amount_of_component) {
    for (int i = 0; i < amount_of_component; i++) {
        for (int j = 0; j < subs[i].vertexes.size(); j++) {
            if (subs[i].vertexes[j] == vert) { return i; }
        }
    }
}

void union_subsets (vector<boruvka_subset>& subs, int vert1, int vert2, int* amount_of_component) {
    int subset_of_vert1, subset_of_vert2;
    subset_of_vert1 = find_subset_by_vert(subs, vert1, *amount_of_component);
    subset_of_vert2 = find_subset_by_vert(subs, vert2, *amount_of_component);
    if (subset_of_vert1 != subset_of_vert2) {
        for (int i = 0; i < subs[subset_of_vert2].vertexes.size(); i++) {
            subs[subset_of_vert1].vertexes.push_back(subs[subset_of_vert2].vertexes[i]);
        }
        subs.erase(subs.begin() + subset_of_vert2);
        (*amount_of_component)--;
    }
}

graph_matrix* boruvka_matr(graph_matrix& graph) {

    graph_matrix* result = new graph_matrix(graph.vertex_count);
    vector<boruvka_subset> subsets;
    vector<pair<int, int>> lowest;

    for (int vert = 0; vert < graph.vertex_count; vert++){
        boruvka_subset new_sub = *new boruvka_subset;
        pair<int,int> new_pair = *new pair<int,int>;
        subsets.push_back(new_sub);
        lowest.push_back(new_pair);
        subsets[vert].vertexes.push_back(vert);
    }

    int amount_of_component = graph.vertex_count;

    while (amount_of_component > 1) {
        for (int vert = 0; vert < graph.vertex_count; vert++) {
            int min_edge = INT32_MAX;
            for (int i = 0; i < graph.vertex_count; i++) {
                if (graph.adjacent[vert][i] < min_edge
                    && find_subset_by_vert(subsets, vert, amount_of_component) !=
                    find_subset_by_vert(subsets, i, amount_of_component) && graph.adjacent[vert][i]!=0) {
                    min_edge = graph.adjacent[vert][i];
                    lowest[vert] = make_pair(i, graph.adjacent[vert][i]);
                }
            }
        }

        for (int i = 0; i < amount_of_component; i++) {
            pair<int, int> verts_for_union = lowest_in_subset(&subsets[i], lowest);
            (*result).adjacent[verts_for_union.first][verts_for_union.second] = graph.adjacent[verts_for_union.first][verts_for_union.second];
            (*result).adjacent[verts_for_union.second][verts_for_union.first] = graph.adjacent[verts_for_union.second][verts_for_union.first];
            union_subsets(subsets, verts_for_union.first, verts_for_union.second, &amount_of_component);
        }

    }
    return result;
}

graph_struct* boruvka_struct(graph_struct& graph) {
    graph_struct* result = new graph_struct(graph.vertex_count);
    vector<boruvka_subset> subsets;
    vector<pair<int, int>> lowest;

    for (int vert = 0; vert < graph.vertex_count; vert++){
        boruvka_subset new_sub = *new boruvka_subset;
        pair<int,int> new_pair = *new pair<int,int>;
        subsets.push_back(new_sub);
        lowest.push_back(new_pair);
        subsets[vert].vertexes.push_back(vert);
    }

    int amount_of_component = graph.vertex_count;

    while (amount_of_component > 1) {
        for (int vert = 0; vert < graph.vertex_count; vert++) {
            int min_edge = INT32_MAX;
            for (int i = 0; i < graph.adjacent[vert].size(); i++) {
                if (graph.adjacent[vert][i].second < min_edge
                    && find_subset_by_vert(subsets, vert, amount_of_component) !=
                       find_subset_by_vert(subsets, graph.adjacent[vert][i].first, amount_of_component)) {
                    min_edge = graph.adjacent[vert][i].second;
                    lowest[vert] = make_pair(graph.adjacent[vert][i].first, graph.adjacent[vert][i].second);
                }
            }
        }

        for (int i = 0; i < amount_of_component; i++) {
            pair<int, int> verts_for_union = lowest_in_subset(&subsets[i], lowest);
            int new_edge_weight = 0;
            for (int j = 0; j < graph.adjacent[verts_for_union.first].size(); j++) {
                if (graph.adjacent[verts_for_union.first][j].first == verts_for_union.second) {
                    new_edge_weight = graph.adjacent[verts_for_union.first][j].second;
                }
            }
            bool already_in_graph = false;
            for (int edge = 0; edge < (*result).adjacent[verts_for_union.first].size(); edge++) {
                if ((*result).adjacent[verts_for_union.first][edge].first == verts_for_union.second) {
                    already_in_graph = true;
                }
            }
            if (!already_in_graph) {
                (*result).adjacent[verts_for_union.first].push_back(make_pair(verts_for_union.second, new_edge_weight));
                (*result).adjacent[verts_for_union.second].push_back(make_pair(verts_for_union.first, new_edge_weight));
                union_subsets(subsets, verts_for_union.first, verts_for_union.second, &amount_of_component);
            }
        }
    }
    return result;
}

int weight_of_matr_graph (graph_matrix& graph) {
  int weight = 0;

  for (int i = 0; i < graph.vertex_count; i++) {
      for (int j = i+1; j < graph.vertex_count; j++){
          weight += graph.adjacent[i][j];
      }
  }
  return weight;
}

int weight_of_struct_graph (graph_struct& graph) {
    int weight = 0;

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.adjacent[i].size(); j++){
            weight += graph.adjacent[i][j].second;
        }
    }
    return weight/2;
}

int main() {
    srand(time(0));

    return 0;
}
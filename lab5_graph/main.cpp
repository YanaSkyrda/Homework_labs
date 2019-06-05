#include <iostream>
#include<vector>
#include <ctime>
#include<queue>
#include<algorithm>

using namespace std;

const int max_vert_count = 20;

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
    bool already_in_graph = false;
    for (int edge = 0; edge < (graph).adjacent[vert1].size(); edge++) {
        if ((graph).adjacent[vert1][edge].first == vert2) {
            already_in_graph = true;
            (graph).adjacent[vert1][edge].second = weight;
            if (!graph.is_oriented) {
                for (int i = 0; i < graph.adjacent[vert2].size(); i++) {
                    if (graph.adjacent[vert2][i].first == vert1) {
                        (graph).adjacent[vert2][i].second = weight;
                    }
                }
            }
        }
    }
    if (!already_in_graph) {
        graph.adjacent[vert1].push_back(make_pair(vert2, weight));
        if (!graph.is_oriented) {
            graph.adjacent[vert2].push_back(make_pair(vert1, weight));
        }
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

graph_matrix* create_random_matrg(int vertex_count, int edge_count, bool is_oriented = false, bool is_weighed = false) {
    graph_matrix* graph = new graph_matrix(vertex_count);
    (*graph).is_oriented = is_oriented;
    int vert1, vert2, weight = 1;
    for (int i = 0; i < edge_count; i++) {
        do {
            vert1 = rand() % vertex_count;
            vert2 = rand() % vertex_count;
            while (vert1 == vert2) {vert2 = rand()%vertex_count;}
        } while ((*graph).adjacent[vert1][vert2]!=0);

        if (is_weighed) {weight = rand()%9+1;}
        (*graph).adjacent[vert1][vert2] = weight;
        if (!is_oriented) {
            (*graph).adjacent[vert2][vert1] = weight;
        }
    }
    return graph;
}

graph_struct* create_random_structg(int vertex_count, int edge_count, bool is_oriented = false, bool is_weighed = false) {
    graph_struct* graph = new graph_struct(vertex_count);
    (*graph).is_oriented = is_oriented;

    int vert1, vert2, weight = 1;
    bool used;
    for (int i = 0; i < edge_count; i++) {
        do {
            used = false;
            vert1 = rand() % vertex_count;
            vert2 = rand() % vertex_count;
            while (vert1 == vert2) {vert2 = rand()%vertex_count;}
            for (int j = 0; j < (*graph).adjacent[vert1].size(); j++) {
                if (((*graph).adjacent[vert1])[j].first == vert2) {
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
    }
    return false;
}

bool is_cyclic_struct_rec(int curr_vertex, bool* visited, bool *recStack, graph_struct& graph) {
    if(!visited[curr_vertex]) {

        visited[curr_vertex] = true;
        recStack[curr_vertex] = true;

        for(int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            if (!visited[graph.adjacent[curr_vertex][i].first]
            && is_cyclic_struct_rec(graph.adjacent[curr_vertex][i].first, visited, recStack, graph)) {return true;}
            else if (recStack[graph.adjacent[curr_vertex][i].first]) {return true;}
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
    }
    return false;
}

bool compare_weight (pair<int,int> left, pair<int,int> right) {
    if (left.second<right.second) {return true;}
    return false;
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
        if (by_weight) {sort(edges_weight.begin(), edges_weight.end(),compare_weight);}

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
    cout<<endl;
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
        if (by_weight) {sort(edges_weight.begin(), edges_weight.end(),compare_weight);}

        for (int i = 0; i < edges_weight.size(); i++) {
            if (!visited[edges_weight[i].first]) {
                visited[edges_weight[i].first] = true;
                q.push(edges_weight[i].first);
            }
        }
    }
}

void bfs_struct(graph_struct& graph, bool by_weight = false) {
    vector<bool> visited(max_vert_count, false);
    for (int curr_vertex = 0; curr_vertex < graph.vertex_count; curr_vertex++) {
        if (visited[curr_vertex] == false) {bfs_struct_rec(curr_vertex, visited, graph, by_weight);}
    }
    cout<<endl;
}

vector<vector<int>> Floyd_matr (graph_matrix& graph) {
    vector<vector<int>> distance;

    int matrix[graph.vertex_count][graph.vertex_count];
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            matrix[i][j] = graph.adjacent[i][j];
        }
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            for (int k = 0; k < graph.vertex_count; k++) {
                if (matrix[j][k] > matrix[j][i] + matrix[i][k] && (matrix[j][i]!=0) && matrix[i][k]!=0) {
                    matrix[j][k] = matrix[j][i] + matrix[i][k];
                }
            }
        }
    }
    for (int i = 0; i < graph.vertex_count; i++) {
        vector<int> row;
        for (int j = 0; j < graph.vertex_count; j++) {
            row.push_back(matrix[i][j]);
        }
        distance.push_back(row);
    }
    return distance;
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
    vector<vector<int>> distance;

    int matrix[graph.vertex_count][graph.vertex_count];
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.adjacent[i].size(); j++) {
            matrix[i][graph.adjacent[i][j].first] = graph.adjacent[i][j].second;
        }
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            for (int k = 0; k < graph.vertex_count; k++) {
                if (matrix[j][k] > matrix[j][i] + matrix[i][k] && (matrix[j][i]!=0) && matrix[i][k]!=0) {
                    matrix[j][k] = matrix[j][i] + matrix[i][k];
                }
            }
        }
    }
    for (int i = 0; i < graph.vertex_count; i++) {
        vector<int> row;
        for (int j = 0; j < graph.vertex_count; j++) {
            row.push_back(matrix[i][j]);
        }
        distance.push_back(row);
    }
    return distance;
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

    if (!graph.is_oriented || is_cyclic_matr(graph)) {
        cout<<"This graph is not acyclic and directed"<<endl;
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
            dfs_for_topological_struct(graph, graph.adjacent[vertex][i].first, visited, result);
    }

    result.push_back(vertex);
}

vector<int> topological_sort_struct(graph_struct& graph) {
    vector<bool> visited;
    vector<int> result;

    if (!graph.is_oriented || is_cyclic_str(graph)) {
        cout<<"This graph is not acyclic and directed"<<endl;
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

graph_matrix* bfs_matr_for_span(graph_matrix& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;
    vector<bool> already_connected;
    vector<bool> visited;
    graph_matrix* result = new graph_matrix(graph.vertex_count);
    int curr_vertex = 0;

    for (int i = 0; i < graph.vertex_count; i++) {
        already_connected.push_back(false);
        visited.push_back(false);
    }

    q.push(curr_vertex);
    already_connected[curr_vertex] = true;

    while(!q.empty()) {
        curr_vertex = q.front();
        q.pop();

        for (int i = 0; i < graph.vertex_count; i++) {
            if (graph.adjacent[curr_vertex][i] != 0 && !already_connected[i]) {
                (*result).adjacent[curr_vertex][i] = graph.adjacent[curr_vertex][i];
                if (!graph.is_oriented) {(*result).adjacent[i][curr_vertex] = graph.adjacent[curr_vertex][i];}
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

graph_struct* bfs_struct_for_span(graph_struct& graph, bool by_weight = false) {
    queue<int> q;
    vector<pair<int, int>> edges_weight;
    vector<bool> already_connected;
    graph_struct* result = new graph_struct(graph.vertex_count);
    vector<bool> visited;

    for (int i = 0; i < graph.vertex_count; i++) {
        already_connected.push_back(false);
        visited.push_back(false);
    }

    int curr_vertex = 0;
    visited[curr_vertex] = true;
    q.push(curr_vertex);
    already_connected[curr_vertex] = true;

    while(!q.empty()) {
        curr_vertex = q.front();
        q.pop();

        for (int i = 0; i < graph.adjacent[curr_vertex].size(); i++) {
            if (!already_connected[graph.adjacent[curr_vertex][i].first]) {
                (*result).adjacent[curr_vertex].push_back(graph.adjacent[curr_vertex][i]);
                if (!graph.is_oriented) {(*result).adjacent[graph.adjacent[curr_vertex][i].first].push_back(make_pair(curr_vertex,graph.adjacent[curr_vertex][i].second));}
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

void demonstration_add_to_matr (graph_matrix& graph, int verts) {
    int vert1 = rand()%verts;
    int vert2 = rand()%verts;
    while (vert1 == vert2) {vert2 = rand()%verts;}
    int weight = rand()%9+1;
    cout<<"adding new edge between "<<vert1<<" and "<<vert2<<" with weight "<<weight<<": "<<endl;
    add_to_matr(graph, vert1, vert2, weight);
    output_matrix_graph(graph);
}

void demonstration_add_to_struct (graph_struct& graph, int verts) {
    int vert1 = rand()%verts;
    int vert2 = rand()%verts;
    while (vert1 == vert2) {vert2 = rand()%verts;}
    int weight = rand()%9+1;
    cout<<"adding new edge between "<<vert1<<" and "<<vert2<<" with weight "<<weight<<": "<<endl;
    add_to_struct(graph, vert1, vert2, weight);
    output_struct_graph(graph);
}

void demonstration() {
    cout<<"1. Graph represented as matrix."<<endl;
    cout<<"Unit 0:"<<endl;
    int verts = rand()%5+5;
    int edges = rand()%10;
    cout<<"created random oriented weighed graph with "<<verts<<" vertices and "<<edges<<" egdes:"<<endl;
    graph_matrix* mgraph = create_random_matrg(verts, edges, true, true);
    output_matrix_graph(*mgraph);

    demonstration_add_to_matr(*mgraph, verts);
    demonstration_add_to_matr(*mgraph, verts);
    demonstration_add_to_matr(*mgraph, verts);
    demonstration_add_to_matr(*mgraph, verts);

    cout<<"transform matrix to structure representation: "<<endl;
    graph_struct* sgraph = matr_to_struct(*mgraph);
    output_struct_graph(*sgraph);

    cout<<"Unit 1:"<<endl;
    output_matrix_graph(*mgraph);
    cout<<"Is this graph acyclic? ";
    if (is_cyclic_matr(*mgraph)) {cout<<"no, it has cycle."<<endl;}
    else {cout<<"yes. "<<endl;}
    cout<<"Adding cycle to graph 1-2-3-1:"<<endl;
    add_to_matr(*mgraph, 1, 2, rand()%9+1);
    add_to_matr(*mgraph, 2, 3, rand()%9+1);
    add_to_matr(*mgraph, 3, 1, rand()%9+1);
    output_matrix_graph(*mgraph);
    cout<<"Is this graph acyclic? ";
    if (is_cyclic_matr(*mgraph)) {cout<<"no, it has cycle."<<endl;}
    else {cout<<"yes. "<<endl;}

    cout<<"Unit 2:"<<endl;
    output_matrix_graph(*mgraph);
    cout<<"BFS by number of vertex: ";
    bfs_matr(*mgraph, false);
    cout<<"BFS by weight: ";
    bfs_matr(*mgraph, true);

    cout<<"Unit 3:"<<endl;
    output_matrix_graph(*mgraph);
    cout<<"Floyd's algorithm."<<endl;
    cout<<"Minimal distance between all vertices in graph: "<<endl;
    vector<vector<int>> result = Floyd_matr(*mgraph);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.size(); j++) {
            cout<<result[i][j]<<"  ";
        }
        cout<<endl;
    }
    int vert1 = rand()%((*mgraph).vertex_count);
    cout<<"Minimal distance between vertex "<<vert1<<" and all other vertices:"<<endl;
    result[0] = Floyd_matr_all_for_one(*mgraph, vert1);
    for (int i = 0; i < (*mgraph).vertex_count; i++) {
        cout<<result[0][i]<<"  ";
    }
    cout<<endl;
    int vert2 = rand()%((*mgraph).vertex_count);
    vert1 =  rand()%((*mgraph).vertex_count);
    cout<<"Minimal distance between vertex "<<vert1<<" and vertex "<<vert2<<" : "
        <<Floyd_matr_between_two(*mgraph, vert1,vert2)<<endl;

    cout<<"Unit 4: "<<endl;
    while (is_cyclic_matr(*mgraph)) {mgraph = create_random_matrg(6,6,true);}
    output_matrix_graph(*mgraph);
    cout<<"Topological sort by dfs."<<endl;
    result[0] = topological_sort_matr(*mgraph);
    if (!result[0].empty()) {
        for (int i = 0; i < (*mgraph).vertex_count; i++) {
            cout << result[0][i] << "  ";
        }
        cout << endl;
    }

    cout<<"Unit 5: "<<endl;
    mgraph = create_random_matrg(6,10,false,true);
    output_matrix_graph(*mgraph);
    graph_matrix* matr_result = bfs_matr_for_span(*mgraph);
    cout<<"Spanning tree bfs by number."<<endl;
    output_matrix_graph(*matr_result);
    cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;
    matr_result = bfs_matr_for_span(*mgraph, true);
    cout<<"Spanning tree bfs by weight."<<endl;
    output_matrix_graph(*matr_result);
    cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;

    cout<<"Unit 6: "<<endl;
    cout<<"Minimal spanning tree by Boruvka's algorithm:"<<endl;
    matr_result = boruvka_matr(*mgraph);
    output_matrix_graph(*matr_result);
    cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;

    cout<<"2. Graph represented as structure."<<endl;
    cout<<"Unit 0:"<<endl;
    verts = rand()%5+5;
    edges = rand()%10;
    cout<<"created random oriented weighed graph with "<<verts<<" vertices and "<<edges<<" egdes:"<<endl;
    sgraph = create_random_structg(verts, edges, true, true);
    output_struct_graph(*sgraph);

    demonstration_add_to_struct(*sgraph, verts);
    demonstration_add_to_struct(*sgraph, verts);
    demonstration_add_to_struct(*sgraph, verts);
    demonstration_add_to_struct(*sgraph, verts);

    cout<<"transform structure to matrix representation: "<<endl;
    mgraph = struct_to_matr(*sgraph);
    output_matrix_graph(*mgraph);

    cout<<"Unit 1:"<<endl;
    output_struct_graph(*sgraph);
    cout<<"Is this graph acyclic? ";
    if (is_cyclic_str(*sgraph)) {cout<<"no, it has cycle."<<endl;}
    else {cout<<"yes. "<<endl;}
    cout<<"Adding cycle to graph 1-2-3-1:"<<endl;
    add_to_struct(*sgraph, 1, 2, rand()%9+1);
    add_to_struct(*sgraph, 2, 3, rand()%9+1);
    add_to_struct(*sgraph, 3, 1, rand()%9+1);
    output_struct_graph(*sgraph);
    cout<<"Is this graph acyclic? ";
    if (is_cyclic_str(*sgraph)) {cout<<"no, it has cycle."<<endl;}
    else {cout<<"yes. "<<endl;}

    cout<<"Unit 2:"<<endl;
    output_struct_graph(*sgraph);
    cout<<"BFS by number of vertex: ";
    bfs_struct(*sgraph, false);
    cout<<"BFS by weight: ";
    bfs_struct(*sgraph, true);

    cout<<"Unit 3:"<<endl;
    output_struct_graph(*sgraph);
    cout<<"Floyd's algorithm."<<endl;
    cout<<"Minimal distance between all vertices in graph: "<<endl;
    result = Floyd_struct(*sgraph);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.size(); j++) {
            cout<<result[i][j]<<"  ";
        }
        cout<<endl;
    }
    vert1 = rand()%((*sgraph).vertex_count);
    cout<<"Minimal distance between vertex "<<vert1<<" and all other vertices:"<<endl;
    result[0] = Floyd_struct_all_for_one(*sgraph, vert1);
    for (int i = 0; i < (*sgraph).vertex_count; i++) {
        cout<<result[0][i]<<"  ";
    }
    cout<<endl;
    vert2 = rand()%((*sgraph).vertex_count);
    vert1 =  rand()%((*sgraph).vertex_count);
    cout<<"Minimal distance between vertex "<<vert1<<" and vertex "<<vert2<<" : "
    <<Floyd_struct_between_two(*sgraph, vert1,vert2)<<endl;

    cout<<"Unit 4: "<<endl;
    while (is_cyclic_str(*sgraph)) {sgraph = create_random_structg(6,6,true);}
    output_struct_graph(*sgraph);
    cout<<"Topological sort by dfs."<<endl;
    result[0] = topological_sort_struct(*sgraph);
    if (!result[0].empty()) {
        for (int i = 0; i < (*sgraph).vertex_count; i++) {
            cout << result[0][i] << "  ";
        }
        cout << endl;
    }

    cout<<"Unit 5: "<<endl;
    sgraph = create_random_structg(6,10,false,true);
    output_struct_graph(*sgraph);
    graph_struct* struct_result = bfs_struct_for_span(*sgraph);
    cout<<"Spanning tree bfs by number."<<endl;
    output_struct_graph(*struct_result);
    cout<<"Weight of tree: "<<weight_of_struct_graph(*struct_result)<<endl;
    struct_result = bfs_struct_for_span(*sgraph, true);
    cout<<"Spanning tree bfs by weight."<<endl;
    output_struct_graph(*struct_result);
    cout<<"Weight of tree: "<<weight_of_struct_graph(*struct_result)<<endl;

    cout<<"Unit 6: "<<endl;
    cout<<"Minimal spanning tree by Boruvka's algorithm:"<<endl;
    struct_result = boruvka_struct(*sgraph);
    output_struct_graph(*struct_result);
    cout<<"Weight of tree: "<<weight_of_struct_graph(*struct_result)<<endl;

}

void interactive();
void interactive_matrix(graph_matrix**);
void interactive_struct(graph_struct**);

void interactive_matrix (graph_matrix** graph) {
    int mode = 0;

    string name;
    cout<<"Create new graph - enter 1"<<endl;
    cout<<"Add edge to the graph - enter 2"<<endl;
    cout<<"Output graph - enter 3"<<endl;
    cout<<"Create random graph - enter 4"<<endl;
    cout<<"Transform graph to struct representation - enter 5"<<endl;
    cout<<"Check if graph is acyclic - enter 6"<<endl;
    cout<<"Travel through the graph - enter 7"<<endl;
    cout<<"Find minimal distances (Floyd's algorithm) - enter 8"<<endl;
    cout<<"Topological sort (by dfs)) - enter 9"<<endl;
    cout<<"Create spanning tree (by bfs)) - enter 10"<<endl;
    cout<<"Create minimal spanning tree (Boruvka's algorithm)) - enter 11"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            cout<<"Enter number of vertices"<<endl;
            int amount;
            cin>>amount;
            *graph = new graph_matrix(amount);
            cout<<"Is graph oriented?"<<endl;
            string properties;
            cin>>properties;
            if (properties == "yes") {(*graph)->is_oriented = true;}
            else {(*graph)->is_oriented = false;}
            break;
        }
        case 2: {
            cout<<"Enter vertices to connect and weight of edge"<<endl;
            int vert1, vert2, weight;
            cin>>vert1>>vert2>>weight;
            add_to_matr(**graph, vert1, vert2, weight);
            break;
        }
        case 3: {
            output_matrix_graph(**graph);
            break;
        }
        case 4: {
            cout<<"Enter number of vertices and edges"<<endl;
            int vertices, edges;
            cin>>vertices>>edges;
            bool oriented = false;
            cout<<"Is graph oriented?"<<endl;
            string answer;
            cin>>answer;
            if (answer == "yes") {oriented = true;}
            cout<<"Is graph weighted?"<<endl;
            cin>>answer;
            if (answer == "yes") {*graph = create_random_matrg(vertices, edges, oriented,true);}
            else {*graph = create_random_matrg(vertices, edges, oriented);}
            break;
        }
        case 5: {
            graph_struct* graph_str = matr_to_struct(**graph);
            output_struct_graph(*graph_str);
            cout<<"Would you like to work with the struct graph now?"<<endl;
            string answer;
            cin>>answer;
            if (answer == "yes") {
                interactive_struct(&graph_str);
                return;
            }
            break;
        }
        case 6: {
            cout<<"Is graph acyclic?"<<endl;
            if (is_cyclic_matr(**graph)) {cout<<"no";}
            else {cout<<"yes";}
            break;
        }
        case 7: {
            int option;
            cout<<"For travel by number enter 1"<<endl;
            cout<<"For travel by weight enter 2"<<endl;
            cin>>option;
            if (option == 1) {bfs_matr(**graph, false);}
            if (option == 2) {bfs_matr(**graph, true);}
            break;
        }
        case 8: {
            int option;
            cout<<"For finding all the minimum distance enter 1"<<endl;
            cout<<"For finding all minimum distances for one vertex enter 2"<<endl;
            cout<<"For finding minimum distance between two vertices enter 3"<<endl;
            cin>>option;
            if (option == 1) {
                vector<vector<int>> result = Floyd_matr(**graph);
                for (int i = 0; i < result.size(); i++) {
                    for (int j = 0; j < result.size(); j++) {
                        cout<<result[i][j]<<"  ";
                    }
                    cout<<endl;
                }
            }
            if (option == 2) {
                int vert;
                cout << "Enter vertex" << endl;
                cin>>vert;
                vector<int> result = Floyd_matr_all_for_one(**graph, vert);
                for (int i = 0; i < (**graph).vertex_count; i++) {
                    cout << result[i] << "  ";
                }
                cout << endl;
            }
            if (option == 3) {
                int vert1, vert2;
                cout<<"Enter two vertices"<<endl;
                cin>>vert1>>vert2;
                cout <<Floyd_matr_between_two(**graph, vert1,vert2)<<endl;
            }
            break;
        }
        case 9: {
            vector<int> result = topological_sort_matr(**graph);
            if (!result.empty()) {
                for (int i = 0; i < (**graph).vertex_count; i++) {
                    cout << result[i] << "  ";
                }
                cout << endl;
            }
            break;
        }
        case 10: {
            int option;
            cout<<"For finding spanning tree by number enter 1"<<endl;
            cout<<"For finding spanning tree by weight enter 2"<<endl;
            cin>>option;
            if (option == 1) {
                graph_matrix* matr_result = bfs_matr_for_span(**graph);
                output_matrix_graph(*matr_result);
                cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;
            }
            if (option == 2) {
                graph_matrix* matr_result = bfs_matr_for_span(**graph, true);
                output_matrix_graph(*matr_result);
                cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;
            }
            break;
        }
        case 11: {
            graph_matrix* matr_result = boruvka_matr(**graph);
            output_matrix_graph(*matr_result);
            cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_matrix(graph);
}
void interactive_struct (graph_struct** graph) {
    int mode = 0;

    string name;
    cout<<"Create new graph - enter 1"<<endl;
    cout<<"Add edge to the graph - enter 2"<<endl;
    cout<<"Output graph - enter 3"<<endl;
    cout<<"Create random graph - enter 4"<<endl;
    cout<<"Transform graph to matrix representation - enter 5"<<endl;
    cout<<"Check if graph is acyclic - enter 6"<<endl;
    cout<<"Travel through the graph - enter 7"<<endl;
    cout<<"Find minimal distances (Floyd's algorithm) - enter 8"<<endl;
    cout<<"Topological sort (by dfs)) - enter 9"<<endl;
    cout<<"Create spanning tree (by bfs)) - enter 10"<<endl;
    cout<<"Create minimal spanning tree (Boruvka's algorithm)) - enter 11"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            cout<<"Enter number of vertices"<<endl;
            int amount;
            cin>>amount;
            *graph = new graph_struct(amount);
            cout<<"Is graph oriented?"<<endl;
            string properties;
            cin>>properties;
            if (properties == "yes") {(*graph)->is_oriented = true;}
            else {(*graph)->is_oriented = false;}
            break;
        }
        case 2: {
            cout<<"Enter vertices to connect and weight of edge"<<endl;
            int vert1, vert2, weight;
            cin>>vert1>>vert2>>weight;
            add_to_struct(**graph, vert1, vert2, weight);
            break;
        }
        case 3: {
            output_struct_graph(**graph);
            break;
        }
        case 4: {
            cout<<"Enter number of vertices and edges"<<endl;
            int vertices, edges;
            cin>>vertices>>edges;
            bool oriented = false;
            cout<<"Is graph oriented?"<<endl;
            string answer;
            cin>>answer;
            if (answer == "yes") {oriented = true;}
            cout<<"Is graph weighted?"<<endl;
            cin>>answer;
            if (answer == "yes") {*graph = create_random_structg(vertices, edges, oriented,true);}
            else {*graph = create_random_structg(vertices, edges, oriented);}
            break;
        }
        case 5: {
            graph_matrix* graph_matr = struct_to_matr(**graph);
            output_matrix_graph(*graph_matr);
            cout<<"Would you like to work with the matrix graph now?"<<endl;
            string answer;
            cin>>answer;
            if (answer == "yes") {
                interactive_matrix(&graph_matr);
                return;
            }
            break;
        }
        case 6: {
            cout<<"Is graph acyclic?"<<endl;
            if (is_cyclic_str(**graph)) {cout<<"no";}
            else {cout<<"yes";}
            break;
        }
        case 7: {
            int option;
            cout<<"For travel by number enter 1"<<endl;
            cout<<"For travel by weight enter 2"<<endl;
            cin>>option;
            if (option == 1) {bfs_struct(**graph, false);}
            if (option == 2) {bfs_struct(**graph, true);}
            break;
        }
        case 8: {
            int option;
            cout<<"For finding all the minimum distance enter 1"<<endl;
            cout<<"For finding all minimum distances for one vertex enter 2"<<endl;
            cout<<"For finding minimum distance between two vertices enter 3"<<endl;
            cin>>option;
            if (option == 1) {
                vector<vector<int>> result = Floyd_struct(**graph);
                for (int i = 0; i < result.size(); i++) {
                    for (int j = 0; j < result.size(); j++) {
                        cout<<result[i][j]<<"  ";
                    }
                    cout<<endl;
                }
            }
            if (option == 2) {
                int vert;
                cout << "Enter vertex" << endl;
                cin>>vert;
                vector<int> result = Floyd_struct_all_for_one(**graph, vert);
                for (int i = 0; i < (**graph).vertex_count; i++) {
                    cout << result[i] << "  ";
                }
                cout << endl;
            }
            if (option == 3) {
                int vert1, vert2;
                cout<<"Enter two vertices"<<endl;
                cin>>vert1>>vert2;
                cout <<Floyd_struct_between_two(**graph, vert1,vert2)<<endl;
            }
            break;
        }
        case 9: {
            vector<int> result = topological_sort_struct(**graph);
            if (!result.empty()) {
                for (int i = 0; i < (**graph).vertex_count; i++) {
                    cout << result[i] << "  ";
                }
                cout << endl;
            }
            break;
        }
        case 10: {
            int option;
            cout<<"For finding spanning tree by number enter 1"<<endl;
            cout<<"For finding spanning tree by weight enter 2"<<endl;
            cin>>option;
            if (option == 1) {
                graph_struct* result = bfs_struct_for_span(**graph);
                output_struct_graph(*result);
                cout<<"Weight of tree: "<<weight_of_struct_graph(*result)<<endl;
            }
            if (option == 2) {
                graph_struct* result = bfs_struct_for_span(**graph, true);
                output_struct_graph(*result);
                cout<<"Weight of tree: "<<weight_of_struct_graph(*result)<<endl;
            }
            break;
        }
        case 11: {
            graph_struct* result = boruvka_struct(**graph);
            output_struct_graph(*result);
            cout<<"Weight of tree: "<<weight_of_struct_graph(*result)<<endl;
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_struct(graph);
}
int interactive_options() {
    int mode = 0;
    cout<<"Work with matrix representation - enter 1"<<endl;
    cout<<"Work with struct representation - enter 2"<<endl;
    cout<<"Exit - enter 0"<<endl;
    cin>>mode;
    return mode;
}
void interactive() {
    int mode = 0;
    mode = interactive_options();
    switch(mode) {
        case 0: {
            return;
        }
        case 1: {
            graph_matrix* graph = nullptr;
            interactive_matrix(&graph);
            break;
        }
        case 2: {
            graph_struct* graph = nullptr;
            interactive_struct(&graph);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
        }
    }
}

int main() {
    srand(time(0));

    int mode;
    cout << "For interactive mode enter 1" << endl;
    cout << "For demonstration mode enter 2" << endl;
    cin>>mode;
    if (mode == 1) {interactive();}
    if (mode == 2) {demonstration();}

    return 0;
}